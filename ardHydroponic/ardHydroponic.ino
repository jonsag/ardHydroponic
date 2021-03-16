
//#define rotaryEncoder ; // comment out this line if you are going to use buttons instead of a rotary encoder
//#define eeprom // store values to EEPROM
#define LCD // use a 20x4 I2C LCD

/**********
* Include files
**********/
#include "config.h"
#include "LCD.h"
#include "pumps.h"
#include "read.h"
#include "misc.h"
#include "settings.h"

#ifndef rotaryEncoder
#include "buttons.h"
#else
#include "rotaryEncoder.h"
#endif

#ifdef eeprom
#include "eeprom.h"
#endif

//#include "thingSpeak.h"

void setup()
{
  /***********
  * Serial
  ***********/
  Serial.begin(serialBaudRate); // serial baudrate

  /*******************************
  * Print start information
  *******************************/
  Serial.println();
  Serial.println(programName); // print information
  Serial.println(date);
  Serial.print("by ");
  Serial.println(author);
  Serial.println(email);
  Serial.println();

#ifdef eeprom
  /**********
  * EEPROM
  **********/
  //clearEEPROM();
  Serial.println("Reading EEPROM...");
  initEEPROMCheck();
  Serial.println();
#endif

#ifdef LCD
  /**********
  * LCD
  **********/
  Serial.println("Starting LCD...");

  lcd.begin();
  Serial.println();
#endif

  /**********
  * In/Outputs
  **********/
  Serial.println("Starting In/Out puts...");

  pinMode(pHPlusPump, OUTPUT);
  pinMode(pHMinusPump, OUTPUT);
  pinMode(nutrAPump, OUTPUT);
  pinMode(nutrBPump, OUTPUT);

  /*
  pinMode(ECPin, INPUT);     // EC sensor probe
  pinMode(ECPower, OUTPUT);  // sourcing current
  pinMode(ECGround, OUTPUT); // sinking current
  */

  Serial.println();

#ifndef rotaryEncoder
  /**********
  * Setup FTDebouncer pins
  **********/
  Serial.println("Setting up buttons...");

  pinDebouncer.addPin(button1, LOW); // pin has external pull-down resistor
  pinDebouncer.addPin(button2, LOW);
  pinDebouncer.addPin(button3, LOW);
  pinDebouncer.addPin(button4, LOW);
  pinDebouncer.addPin(button5, LOW);

  pinDebouncer.init(); // initiate debounce
#else
  /**********
  * Setup rotary encoder
  **********/
  Serial.println("Setting up rotary encoder...");
  rotary.setDebounceDelay(rotEncDebounceTime);
  //rotary.setTrigger(LOW);
#endif
  Serial.println();

  /**********
  * EC/TDS sensor
  **********/
  Serial.println("Starting EC/TDS sensor...");

  /*
  digitalWrite(ECGround, LOW); // ground level for the EC sensor probe
  R1 = (R1 + Ra);              // taking into account powering pin resistance
  */
  gravityTds.setPin(ECSensorPin);
  gravityTds.setAref(5.0);      //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024); //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();           //initialization
  Serial.println();

  /***********
  * WiFi
  ***********/
  //Serial.println("AT"); // Hayes command call for attention    }

  /**********
  * Initiate screen
  **********/
  printNormal();
  readSensors();
}

void loop()
{
  currentMillis = millis();

  /**********
  * Read buttons
  **********/
#ifndef rotaryEncoder;
  pinDebouncer.update();
#else
  rotEncRot = rotary.rotate();
  rotEncPush = rotary.push();
  rotEncLongPush = rotary.pushLong(longPushTime);
  handleRotaryEncoder();
#endif

  checkMode(); // check if mode has changed

  if (mode != 3 && mode != 4)
  { // normal mode

    counter = (iterationTime - (currentMillis - readMillis)) / 1000;

    if ((counter != oldCounter) && (counter >= 0) && (counter <= readMillis / 1000))
    {
      printToLCD(17, 0, String(counter));
      printToLCD(17 + intLength(counter), 0, " ");

      /*
      if (counter <= 1)
      {
        Serial.println("Powering EC sensor...");
        digitalWrite(ECPower, HIGH); // setting the power pin for EC sensor to high
      }
      */

      oldCounter = counter;
    }

    /**********
    * Water temperature
    **********/
    if (currentMillis - readMillis > iterationTime)
    { // read mode
      mode = 1;
      checkMode(); // check if mode has changed

      readSensors();

      mode = 0;    // go back to normal mode
      checkMode(); // check if mode has changed

      /**********
      * ThingSpeak
      **********/
      // updateThingSpeak();

      readMillis = millis();
    }

    /**********
    * Run pumps
    **********/
    //if (EC25<1.4 && phValue>6.6) {} // if the nutrient level unsufficient, and the pH value to high

    checkPumpStop(); // check if it's time to stop the pumps
  }
  else if (mode == 3)
  { // maintenance mode

    checkCleanStop(); // check if pumps are running and if it's time to stop any of them
  }

  if (button1PushMillis != 0 && currentMillis - button1PushMillis >= longPushTime)
  {
    button1PushMillis = 0;
    longPush = 1;
    longPushButton1();
  }
}
