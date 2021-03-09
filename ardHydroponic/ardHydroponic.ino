
/**********
 * Include files
 **********/
#include "config.h"
#include "LCD.h"
#include "pumps.h"
#include "read.h"
#include "misc.h"
#include "buttons.h"
//#include "thingSpeak.h"

void setup()
{
  /***********
   Serial
 ***********/
  Serial.begin(serialBaudRate); // serial baudrate

  /*******************************
      Print start information
    *******************************/
  Serial.println(programName); // print information
  Serial.println(date);
  Serial.print("by ");
  Serial.println(author);
  Serial.println(email);
  Serial.println();

  /**********
     LCD
   **********/
  lcd.init();
  lcd.backlight();

  /**********
     In/Outputs
   **********/
  pinMode(pHPlusPump, OUTPUT);
  pinMode(pHMinusPump, OUTPUT);
  pinMode(nutrAPump, OUTPUT);
  pinMode(nutrBPump, OUTPUT);

  pinMode(ECPin, INPUT);     // EC sensor probe
  pinMode(ECPower, OUTPUT);  // sourcing current
  pinMode(ECGround, OUTPUT); // sinking current

  /**********
    Setup FTDebouncer pins

  **********/
  pinDebouncer.addPin(maintButton, LOW); // pin has external pull-down resistor
  pinDebouncer.addPin(cleanpHMinusButton, LOW);
  pinDebouncer.addPin(cleanpHPlusButton, LOW);
  pinDebouncer.addPin(cleanNutrAButton, LOW);
  pinDebouncer.addPin(cleanNutrBButton, LOW);

  pinDebouncer.init(); // initiate debounce

  /**********
     EC sensor
   **********/
  digitalWrite(ECGround, LOW); // ground level for the EC sensor probe
  R1 = (R1 + Ra);              // taking into account powering pin resistance

  /***********
     WiFi
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
     Read buttons
   **********/
  pinDebouncer.update();

  checkMode(); // check if mode has changed

  if (mode != 3)
  { // normal mode

    counter = (iterationTime - (currentMillis - readMillis)) / 1000;

    if (counter != oldCounter)
    {
      printToLCD(17, 0, String(counter));
      printToLCD(17 + intLength(counter), 0, " ");
      oldCounter = counter;
    }

    /**********
       Water temperature
     **********/
    if (currentMillis - readMillis > iterationTime)
    { // read mode
      mode = 1;
      checkMode(); // check if mode has changed

      readSensors();

      mode = 0;    // go back to normal mode
      checkMode(); // check if mode has changed

      /**********
       ThingSpeak
     **********/
      // updateThingSpeak();

      readMillis = millis();
    }

    /**********
       Run pumps
     **********/
    //if (EC25<1.4 && phValue>6.6) {} // if the nutrient level unsufficient, and the pH value to high

    checkPumpStop(); // check if it's time to stop the pumps
  }
  else
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
}
