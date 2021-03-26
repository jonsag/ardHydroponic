String programName = "ardHydroponic";
String date = "20210316";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/**********
* Configurable variables
**********/
char *varNames[] = {
    "Nutr pump time, ms  ", /* 0 */
    "pH+ pump time, ms   ", /* 1 */
    "pH- pump time, ms   ", /* 2 */
    "Clean pumps time, ms", /* 3 */
    "Iteration time, ms  ", /* 4 */
    "Stir time, ms       ", /* 5 */
    "Stir interval, ms   ", /* 6 */
    "pH low, pH          ", /* 7 */
    "pH high, pH         ", /* 8 */
    "TDS low, ppm        ", /* 9 */
    "k value, factor     ", /* 10 */
    "TDS factor, factor  ", /* 11 */
    "Neutral pH, pH      ", /* 12 */
    "Acid pH, pH         ", /* 13 */
    "Neutral voltage, V  ", /* 14 */
    "Acid voltage, V     ", /* 15 */
    "pH voltage offset, V"  /* 16 */
};

float vars[] = {
    500.00,   /* 0, Nutr pump time, ms */
    500.00,   /* 1, pH+ pump time, ms */
    500.00,   /* 2, pH- pump time, ms */
    30000.00, /* 3, Clean pumps time */
    10000.00, /* 4, Iteration time, ms */
    5000.00,  /* 5, Stir time, ms */
    15000.00, /* 6, Stir interval, ms */
    4.62,     /* 7, pH low, pH */
    4.63,     /* 8, pH high, pH */
    800.00,   /* 9, TDS low, ppm */
    1.08,     /* 10, k value, factor */
    1.0,      /* 11, TDS factor, factor */
    4.0,      /* 12, Neutral pH, pH */
    7.0,      /* 13, Acid pH, pH */
    1.50,     /* 14, Neutral voltage, V */
    2.03,     /* 15, Acid voltage, V */
    1.50      /* 16, pH voltage offset, V */
};

float incs[] = {
    100.00,  /* 0, Nutr pump time, ms */
    100.00,  /* 1, pH+ pump time, ms */
    100.00,  /* 2, pH- pump time, ms */
    1000.00, /* 3, Clean pumps time */
    1000.00, /* 4, Iteration time, ms */
    1000.00, /* 5, Stir time, ms */
    1000.00, /* 6, Stir interval, ms */
    0.01,    /* 7, pH low, pH */
    0.01,    /* 8, pH high, pH */
    1.00,    /* 9, TDS low, ppm */
    0.01,    /* 10, k value, factor */
    0.1,     /* 11, TDS factor, factor */
    0.1,     /* 12, Neutral pH, pH */
    0.1,     /* 13, Acid pH, pH */
    0.01,    /* 14, Neutral voltage, V */
    0.01,    /* 15, Acid voltage, V */
    0.01     /* 16, pH voltage offset, V */
};

const int noOfVars = 17;

/**********
 * Pins
 **********/
// LCD pins
//        Uno   Mega
// SDA -> A4    D20
// SCL -> A5    D21

const int pHPlusPump = 2;  // PH+ pump
const int pHMinusPump = 3; // PH- pump
const int nutrAPump = 4;   // nutrition A pump
const int nutrBPump = 5;   // nutrition B pump
const int stirrer = 6;

const int pHSensorPin = A0; // pH-sensor probe
const int ECSensorPin = A1; // ec/EC sensor
const int DS18S20Pin = A2;  // one wire pin

const int button1 = 7; // if you are using buttons, connect these
const int button2 = 8;
const int button3 = 9;
const int button4 = 10;
const int button5 = 11;

/**********
* EEPROM
**********/
#include <EEPROM.h>

byte varNumber = 0;
byte oldVarNumber = 0;

const byte addressMultiplicator = 4;

/***********
* Serial
***********/
const int serialBaudRate = 9600;

/**********
* Debouncing
**********/
#include <FTDebouncer.h> // load library for debouncing buttons
FTDebouncer pinDebouncer(30);

/***********
* One Wire, DS18B20
***********/
#include <OneWire.h>
OneWire ds(DS18S20Pin); // creating a OneWire object

float temperatureSum; // average of all samples taken from one temp test
float oldTemperatureSum = 0;

byte data[12]; // variable to temporary hold readings
byte addr[8];  // variable to temporary hold the memory address of the readings

/**********
* STD
**********/
#include <stdlib.h>

/**********
* LCD
**********/
#include <LiquidCrystal_I2C.h>                          // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // change to (0x27, 20, 4) for 20x4 LCD

/**********
* EC/TDS sensor
**********/
float voltage;
//float ecValue;   //before temperature compensation
float ecValue25; //after temperature compensation
float tdsValue;

const float aref = 5.0;
const float adcRange = 1024.0;

float TDSValue;
float oldTDSValue = 0;

/**********
* pH sensor
**********/
/*
unsigned long int avgValue; // average value of the sensor feedback
int buf[10], temp;          // pH reading samples
*/

float pHVoltage; // the voltage reading from analog pin
float slope;
float intercept;

float pHValue; // calculated pH reading
float oldpHValue = 0;

/**********
* Misc
*********/
int mode = 0; // 0: normal, 1: reading, 2: pumping, 3: maintenance, 4: settings
int oldMode = -1;

char dtostrfBuffer[6];
int strLength;
//String valString;
int valLength;

unsigned long currentMillis;

unsigned long readMillis = 0;

unsigned long pHPlusStartMillis = 0;
unsigned long pHMinusStartMillis = 0;
unsigned long nutrAStartMillis = 0;
unsigned long nutrBStartMillis = 0;

unsigned long button1PushMillis = 0;
const int longPushTime = 1000;
boolean longPush = 0;

unsigned long counter;
unsigned long oldCounter = -1;

byte outputNumber = 0;
char *outputNames[] = {"pH+    ", "pH-    ", "Nutr A ", "Nutr B ", "Stirrer"};
//boolean set = 0;

unsigned long stirStartMillis = 0; // when was the stirrer started
unsigned long stirStopMillis = 0;  // when did the stirrer stop

int i;           // just a counter used sometimes
float tempValue; // holds different bvtes

/**********
* WiFi
**********/
//#define SSID "A WiFi network" // WiFi SSID
//#define PASS "password" // WiFi password

/**********
* ThingSpeak
**********/
//#define IP "184.106.153.149"// ip-address for thingspeak.com
//String msg = "GET /update?key=94IADK04DP5YY184"; // a GET parameter associated with the personal thingspeak channel
