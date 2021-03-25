String programName = "ardHydroponic";
String date = "20210316";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/**********
* Configurable variables
**********/
char *varNames[] = {
    "Nutr pump time, ms  ",
    "pH+ pump time, ms   ",
    "pH- pump time, ms   ",
    "Clean pumps time, ms",
    "Iteration time, ms  ",
    "Stir time, ms       ",
    "Stir interval, ms   ",
    "pH low, pH          ",
    "pH high, pH         ",
    "TDS low, ppm        ",
    "k value, factor     ",
    "TDS factor, factor  ",
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
    1.0       /* 11, TDS factor, factor */
};

float incs[] = {100.00,
                100.00,
                100.00,
                1000.00,
                1000.00,
                1000.00,
                1000.00,
                0.01,
                0.01,
                1.00,
                0.01,
                0.1};

const int noOfVars = 12;

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

/*
float nutrientsPumpTimeNew = vars[0]; // pump time for nutrient pumps
float pHPlusPumpTimeNew = vars[1];       // pump time for PH+ pump
float pHMinusPumpTimeNew = vars[2];     // pump time for PH- pump

float cleanTimeNew = vars[3]; // hoses clean time

float iterationTimeNew = vars[4]; // reading

float pHLowNew = vars[7];   //  lowest allowed pH value
float pHHighNew = vars[8]; // lowest allowed pH value
float tdsLowNew = vars[9]; // lowest allowed EC value

float kValueNew = vars[10];
float tdsFactorNew = tdsFactorNew;
*/

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
/*
int R1 = 1000;                 // internal resistance
int Ra = 25;                   // powering pin resistance
float EC = 0;                  // EC-value
float EC25 = 0;                // equivalent EC-value at temp 25 celcius
float K = 1.44;                // trail measured coefficient
float TemperatureCoef = 0.019; // temperature coefficient for water that is estimated by trials.
float ECRaw = 0;               // raw data from a EC-sensor reading
float Vin = 5;                 // internal voltage supply from Arduino to an analog pin
float Vdrop = 0;               // voltage drop measured from an EC-reading
float Rc = 0;                  // The voltage of the water solvent

float oldEC25 = 0;
*/

float voltage;
//float ecValue;   //before temperature compensation
float ecValue25; //after temperature compensation
float tdsValue;

const float aref = 5.0;
const float adcRange = 1024.0;

float TDSValue;
float oldTDSValue = 0;

/**********
* PH sensor
**********/
unsigned long int avgValue; // average value of the sensor feedback
float phValue;              // calculated pH reading
int buf[10], temp;          // pH reading samples

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
