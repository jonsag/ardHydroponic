
/**********
 * Include files
 **********/
#include "config.h"
#include "LCD.h"
#include "read.h"
#include "clean.h"
#include "misc.h"
#include "buttons.h"
#include "thingSpeak.h"

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

  /*******************************
    Setup FTDebouncer pins
  *******************************/
  pinDebouncer.addPin(maintButton, LOW); // pin has external pull-down resistor
  pinDebouncer.addPin(cleanpHMinusButton, LOW);
  pinDebouncer.addPin(cleanpHPlusButton, LOW);
  pinDebouncer.addPin(cleanNutrAButton, LOW);
  pinDebouncer.addPin(cleanNutrBButton, LOW);

  pinDebouncer.init(); // initiate debouncer

  /**********
     EC sensor
   **********/
  digitalWrite(ECGround, LOW); // ground level for the EC sensor probe
  R1 = (R1 + Ra);              // taking into account powering pin resistance

  /***********
     WiFi
   ***********/
  //Serial.println("AT"); // Hayes command call for attention
  //delay(5000); // 5000 ms delay
  // connectWiFi(); // Calling on function to connect to WiFI

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

    /**********
       Water temperature
     **********/
    if (currentMillis - readMillis > iterationTime)
    { // read mode
      mode = 1;
      checkMode(); // check if mode has changed

      readSensors();

      mode = 2;    // enabling pump mode
      checkMode(); // check if mode has changed

      /**********
       ThingSpeak
     **********/
      // updateThingSpeak();
    }

    if (mode == 2)
    {
      /**********
       Run pumps
     **********/
      //if (EC25<1.4 && phValue>6.6) {} // if the nutrient level unsufficient, and the pH value to high

      /**********
       Nutrient pumps
     **********/
      if (EC25 < 3.0)
      { // if the nutrient level is unsufficient
        Serial.println("Nutrientpumps ON");
        //printToLCD(1, 3, "Nutrientpumps  ON  ");

        digitalWrite(nutrAPump, HIGH); // dosing nutrition A
        digitalWrite(nutrBPump, HIGH); // dosing nutrition B

        delay(nutrientsPumpTime); // running nutrient pumps

        digitalWrite(nutrAPump, LOW); // cutting power to pump
        digitalWrite(nutrBPump, LOW); // cutting power to pump

        Serial.println("Nutrientpumps OFF");
        //printToLCD(1, 3, "Nutrientpumps  OFF  ");
      }

      /**********
       PH pumps
     **********/
      if (phValue < 4.62)
      { // if the pH value to low
        Serial.println("Dosingpump PH+ ON");
        //printToLCD(1, 1, "Dosingpump PH+ ON   ");

        digitalWrite(pHPlusPump, HIGH); // dosing PH+

        delay(pHPlusPumpTime); // running pump

        digitalWrite(pHPlusPump, LOW); // cutting power to pump

        Serial.println("Dosingpump PH+ OFF");
        //printToLCD(1, 1, "Dosingpump PH+ OFF  ");
      }
      else if (phValue > 4.63)
      { // if the pH is too high
        Serial.println("Dosingpump PH- ON");
        //printToLCD(1, 1, "Dosingpump PH- ON   ");

        digitalWrite(pHMinusPump, HIGH); // dosing PH-

        delay(pHMinusPumpTime); // running pump

        digitalWrite(pHMinusPump, LOW); // cutting power to pump
        Serial.println("Dosingpump PH- OFF  ");
        //printToLCD(1, 1, "Dosingpump PH- OFF");
      }

      readMillis = millis();
      mode = 0;    // go back to normal mode
      checkMode(); // check if mode has changed
    }
  }
  else
  { // maintenance mode
    printMode();

    if (cleanpHMinus)
    {
      flushpHMinus();
    }
    if (cleanpHPlus)
    {
      flushpHPlus();
    }
    if (cleanNutrA)
    {
      flushNutrA();
    }
    if (cleanNutrB)
    {
      flushNutrB();
    }
  }
}
