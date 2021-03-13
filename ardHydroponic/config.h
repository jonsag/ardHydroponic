String programName = "ardHydroponic";
String date = "20210313";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/**********
* Times
**********/
const int nutrientsPumpTime = 500; // pump time for nutrient pumps
const int pHPlusPumpTime = 500;    // pump time for PH+ pump
const int pHMinusPumpTime = 500;   // pump time for PH- pump

const int cleanTime = 30000; // hoses clean time

const int iterationTime = 10000; // reading

const unsigned long maintTimeOut = 36000000; // 36000000 millis = 10 minutes

/**********
* Accepted values
**********/
const float pHLow = 4.62;  //  lowest allowed pH value
const float pHHigh = 4.63; // lowest allowed pH value
const float eCLow = 3.0;   // lowest allowed EC value

/**********
 * Pins
 **********/
// LCD pins
//        Uno   Mega
// SDA -> A4    D20
// SCL -> A5    D21

const int DS18S20Pin = A1; // one wire pin

const int pHPlusPump = 2;  // PH+ pump
const int pHMinusPump = 3; // PH- pump
const int nutrAPump = 4;   // nutrition A pump
const int nutrBPump = 5;   // nutrition B pump

const int ECPin = 11;    // EC sensor reference pin
const int ECGround = A2; // EC sensor ground level
const int ECPower = 12;  // EC sensor power pin

const int pHpin = A0; // pH-sensor probe

#ifndef rotaryEncoder
const int maintButton = 6;        // if you are using buttons, connect these
const int cleanpHMinusButton = 7; // you will loose many functions:
const int cleanpHPlusButton = 8;
const int cleanNutrAButton = 9;
const int cleanNutrBButton = 10;
#else
const int rotEncCLK = 8;
const int rotEncDT = 7;
const int rotEncSW = 6; // if you are using a rotary encoder, connect these
#endif

/***********
* Serial
***********/
const int serialBaudRate = 9600;

/**********
* Debouncing
**********/
#ifndef rotaryEncoder
#include <FTDebouncer.h> // load library for debouncing buttons
FTDebouncer pinDebouncer(30);
#endif

/**********
 * Rotary encoder
 **********/
#ifdef rotaryEncoder
#include <SimpleRotary.h>
SimpleRotary rotary(rotEncDT, rotEncCLK, rotEncSW);

byte rotEncRot;
byte rotEncPush;
byte rotEncLongPush;

//boolean rotEncPushed = 0;

const int longPushTime = 1000; // how long is a long push of the button
const int rotEncDebounceTime = 30;
#endif

/***********
* One Wire, DS18B20
***********/
#include <OneWire.h>
OneWire ds(DS18S20Pin); // creating a OneWire object

float TemperatureSum; // average of all samples taken from one temp test
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
* EC sensor
**********/
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
String valString;
int valLength;

unsigned long currentMillis;

unsigned long readMillis = 0;

unsigned long pHPlusStartMillis = 0;
unsigned long pHMinusStartMillis = 0;
unsigned long nutrAStartMillis = 0;
unsigned long nutrBStartMillis = 0;

unsigned long maintStartMillis = 0;

unsigned long counter;
unsigned long oldCounter = -1;

int pumpNumber = 0;
char *pumpNames[] = {"pH+   ", "pH-   ", "NutrA", "Nutr B"};
boolean set = 0;

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
