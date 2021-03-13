
#define rotaryEncoder ; // comment out this line if you are going to use buttons instead of a rotary encoder

/**********
* Include files
**********/
#include "config.h"
#include "LCD.h"
#include "pumps.h"
#include "read.h"
#include "misc.h"

#ifndef rotaryEncoder
#include "buttons.h"
#else
#include "rotaryEncoder.h"
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
  Serial.println(programName); // print information
  Serial.println(date);
  Serial.print("by ");
  Serial.println(author);
  Serial.println(email);
  Serial.println();

  /**********
  * LCD
  **********/
  Serial.println("Starting LCD...");

  lcd.begin();

  /**********
  * In/Outputs
  **********/
  Serial.println("Starting In/Out puts...");

  pinMode(pHPlusPump, OUTPUT);
  pinMode(pHMinusPump, OUTPUT);
  pinMode(nutrAPump, OUTPUT);
  pinMode(nutrBPump, OUTPUT);

  pinMode(ECPin, INPUT);     // EC sensor probe
  pinMode(ECPower, OUTPUT);  // sourcing current
  pinMode(ECGround, OUTPUT); // sinking current

#ifndef rotaryEncoder
  /**********
  * Setup FTDebouncer pins
  **********/
  Serial.println("Setting up buttons...");

  pinDebouncer.addPin(maintButton, LOW); // pin has external pull-down resistor
  pinDebouncer.addPin(cleanpHMinusButton, LOW);
  pinDebouncer.addPin(cleanpHPlusButton, LOW);
  pinDebouncer.addPin(cleanNutrAButton, LOW);
  pinDebouncer.addPin(cleanNutrBButton, LOW);

  pinDebouncer.init(); // initiate debounce
#else
  /**********
  * Setup rotary encoder
  **********/
  Serial.println("Setting up rotary encoder...");
  rotary.setDebounceDelay(rotEncDebounceTime);
#endif

  /**********
  * EC sensor
  **********/
  Serial.println("Starting EC sensor...");

  digitalWrite(ECGround, LOW); // ground level for the EC sensor probe
  R1 = (R1 + Ra);              // taking into account powering pin resistance

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
  handleRotary();
#endif

  checkMode(); // check if mode has changed

  if (mode != 3 && mode != 4)
  { // normal mode

    counter = (iterationTime - (currentMillis - readMillis)) / 1000;

    if ((counter != oldCounter) && (counter >= 0) && (counter <= readMillis / 1000))
    {
      printToLCD(17, 0, String(counter));
      printToLCD(17 + intLength(counter), 0, " ");

      if (counter <= 1)
      {
        Serial.println("Powering EC sensor...");
        digitalWrite(ECPower, HIGH); // setting the power pin for EC sensor to high
      }
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

    counter = (maintTimeOut - (currentMillis - maintStartMillis)) / 1000;

    if (counter != oldCounter)
    {
      printToLCD(0, 1, "Time out in:");
      printToLCD(13, 1, String(counter));
      printToLCD(13 + intLength(counter), 1, "s ");
      oldCounter = counter;
    }

    if (currentMillis - maintStartMillis > maintTimeOut)
    { // leaving maintenance mode
      Serial.println("Maintenance mode time out");
      stopPumps();
      mode = 0;
      checkMode();
    }
  }
  else
  {
    Serial.println("We're in settings mode");
  }
}
