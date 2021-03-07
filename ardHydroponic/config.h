String programName = "ardHydroponic";
String date = "20210307";
String author = "Jon Sagebrand";
String email = "jonsagebrand@gmail.com";

/***********
   Serial
 ***********/
const int serialBaudRate = 9600;

/***********
   One Wire, DS18B20
 ***********/
#include <OneWire.h>
const int DS18S20_Pin = A15; // one wire pin
OneWire ds(DS18S20_Pin);     // creating a OneWire object

float TemperatureSum; // average of all samples taken from one temp test
byte data[12];        // variable to temporary hold readings
byte addr[8];         // variable to temporary hold the memory address of the readings

/**********
   STD
 **********/
#include <stdlib.h>

/**********
   LCD
 **********/
#include <LiquidCrystal_I2C.h>                          // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // change to (0x27, 20, 4) for 20x4 LCD

/**********
   Pumps
 **********/
const int PhPlusPump = A11;  // PH+ pump
const int PhMinusPump = A12; // PH- pump
const int nutrAPump = A13;   // nutrition A pump
const int nutrBPump = A14;   // nutrition B pump

const int nutrientsPumpTime = 500; // pump time for nutrient pumps
const int PhPlusPumpTime = 500;       // pump time for PH+ pump
const int PhMinusPumpTime = 500;       // pump time for PH- pump

const int cleanTime = 30000; // hoses clean time

/**********
   EC sensor
 **********/
const int ECPin = A1;    // reference pin
const int ECGround = A2; // ground level
const int ECPower = A3;  // power pin

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

/**********
   PH sensor
 **********/
const int pHpin = A0; // pH-sensor probe

unsigned long int avgValue; // average value of the sensor feedback
float phValue;              // calculated pH reading
int buf[10], temp;          // pH reading samples

/**********
   Buttons
 **********/
const int maintButton = 00; // ersätt alla 00 med ingångsnummer *************************************************************************************************************************
const int cleanPhMinusButton = 00;
const int cleanPhPlusButton = 00;
const int cleanNutrAButton = 00;
const int cleanNutrBButton = 00;

int maintenance;
int cleanPhMinus;
int cleanPhPlus;
int cleanNutrA;
int cleanNutrB;

/**********
   Misc
 **********/
const int iterationTime = 10000; // reading

/**********
   WiFi
 **********/
//#define SSID "A WiFi network" // WiFi SSID
//#define PASS "password" // WiFi password

/**********
   ThingSpeak
 **********/
//#define IP "184.106.153.149"// ip-address for thingspeak.com
//String msg = "GET /update?key=94IADK04DP5YY184"; // A GET parameter associated with the personal thingspeak channel
