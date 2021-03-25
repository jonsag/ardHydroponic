
/**********
* Include files
**********/
#include "config.h"
#include "LCD.h"
#include "outputs.h"
#include "read.h"
#include "misc.h"
#include "settings.h"
#include "eeprom.h"
#include "buttons.h"

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

  /**********
  * EEPROM
  **********/
  //clearEEPROM();
  Serial.println("Reading EEPROM...");
  initEEPROMCheck();
  Serial.println();

  /**********
  * LCD
  **********/
  Serial.println("Starting LCD...");

  lcd.begin();
  Serial.println();

  /**********
  * In/Outputs
  **********/
  Serial.println("Starting In/Out puts...");

  pinMode(pHPlusPump, OUTPUT);
  pinMode(pHMinusPump, OUTPUT);
  pinMode(nutrAPump, OUTPUT);
  pinMode(nutrBPump, OUTPUT);
  pinMode(stirrer, OUTPUT);

  /*
  pinMode(ECPin, INPUT);     // EC sensor probe
  pinMode(ECPower, OUTPUT);  // sourcing current
  pinMode(ECGround, OUTPUT); // sinking current
  */

  Serial.println();

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
  pinDebouncer.update();

  checkMode(); // check if mode has changed

  if (mode != 3 && mode != 4)
  { // normal mode

    counter = (vars[4] - (currentMillis - readMillis)) / 1000;

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
    * Read loop
    **********/
    if (currentMillis - readMillis >= vars[4])
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
    * Stirrer
    **********/
    if (currentMillis - stirStopMillis >= vars[6] && !digitalRead(stirrer))
    { // time to stir
      startStirrer();
      stirStartMillis = currentMillis;
    }

    /**********
    * Run pumps
    **********/
    //if (EC25<1.4 && phValue>6.6) {} // if the nutrient level unsufficient, and the pH value to high

    checkOutputStop(); // check if it's time to stop the pumps or stirrer
  }
  else if (mode == 3)
  { // maintenance mode

    checkMaintStop(); // check if pumps are running and if it's time to stop any of them
  }

  if (button1PushMillis != 0 && currentMillis - button1PushMillis >= longPushTime)
  {
    button1PushMillis = 0;
    longPush = 1;
    longPushButton1();
  }
}
