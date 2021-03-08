
/**********
 * Include files
 **********/
#include "config.h"
#include "read.h"
#include "LCD.h"
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
  pinMode(PhPlusPump, OUTPUT);
  pinMode(PhMinusPump, OUTPUT);
  pinMode(nutrAPump, OUTPUT);
  pinMode(nutrBPump, OUTPUT);

  pinMode(ECPin, INPUT);     // EC sensor probe
  pinMode(ECPower, OUTPUT);  // sourcing current
  pinMode(ECGround, OUTPUT); // sinking current

  /*******************************
    Setup FTDebouncer pins
  *******************************/
  pinDebouncer.addPin(maintButton, LOW); // pin has external pull-down resistor
  pinDebouncer.addPin(cleanPhMinusButton, LOW);
  pinDebouncer.addPin(cleanPhPlusButton, LOW);
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
}

void loop()
{
  currentMillis = millis();

  if (mode != oldMode)
  {
    switch (mode)
    {
    case 0:
      printHeaders();
      break;
    case 1:
      printMode();
      break;
    case 2:
      printMode();
      break;
    case 3:
      printMaintenance();
      break;
    }
    oldMode = mode;
  }
  /**********
     Read buttons
   **********/
  pinDebouncer.update();
  /*
  maintenance = digitalRead(maintButton);
  cleanPhMinus = digitalRead(cleanPhMinusButton);
  cleanPhPlus = digitalRead(cleanPhPlusButton);
  cleanNutrA = digitalRead(cleanNutrAButton);
  cleanNutrB = digitalRead(cleanNutrBButton);
*/

  if (mode != 3)
  { // normal mode

    /**********
       Water temperature
     **********/
    if (currentMillis - readMillis > iterationTime)
    { // read mode
      oldMode = mode;
      mode = 1;
      printMode();

      TemperatureSum = readWaterTemp();

      Serial.println("TankTemp: " + String(TemperatureSum));
      if (TemperatureSum != oldTemperatureSum)
      {
        printTemp();
      }

      /**********
       Read PH value
     **********/
      phValue = readPhValue();

      Serial.println("PH: " + String(phValue));
      if (phValue != oldPhValue)
      {
        printPhValue();
      }

      /**********
       Read EC level
     **********/
      EC25 = readECLevel();

      Serial.println("EC: " + String(EC25));
      if (EC25 != oldEC25)
      {
        printECValue();
      }

      mode = 2; // entering pump mode

      readMillis = currentMillis;

      /**********
       ThingSpeak
     **********/
      // updateThingSpeak();
    }

    /**********
       Run pumps
     **********/
    //if (EC25<1.4 && phValue>6.6) {} // if the nutrient level unsufficient, and the pH value to high

    if (mode == 2)
    {
      /**********
       Nutrient pumps
     **********/
      if (EC25 < 3.0)
      {                                // if the nutrient level unsufficient
        digitalWrite(nutrAPump, HIGH); // dosing nutrition A
        digitalWrite(nutrBPump, HIGH); // dosing nutrition B

        Serial.println("Nutrientpumps ON");
        printToLCD(1, 3, "Nutrientpumps  ON  ");

        delay(nutrientsPumpTime); // running nutrient pumps

        digitalWrite(nutrAPump, LOW); // cutting power to pump
        digitalWrite(nutrBPump, LOW); // cutting power to pump

        Serial.println("Nutrientpumps OFF");
        printToLCD(1, 3, "Nutrientpumps  OFF  ");
      }

      /**********
       PH pumps
     **********/
      if (phValue < 4.62)
      {                                 // if the pH value to low
        digitalWrite(PhPlusPump, HIGH); // dosing PH+

        Serial.println("Dosingpump PH+ ON");
        printToLCD(1, 1, "Dosingpump PH+ ON   ");

        delay(PhPlusPumpTime); // running pump

        digitalWrite(PhPlusPump, LOW); // cutting power to pump

        Serial.println("Dosingpump PH+ OFF");
        printToLCD(1, 1, "Dosingpump PH+ OFF  ");
      }
      else if (phValue > 4.63)
      {                                  // if the pH is high
        digitalWrite(PhMinusPump, HIGH); // dosing PH-

        Serial.println("Dosingpump PH- ON");
        printToLCD(1, 1, "Dosingpump PH- ON   ");

        delay(PhMinusPumpTime); // running pump

        digitalWrite(PhMinusPump, LOW); // cutting power to pump
        Serial.println("Dosingpump PH- OFF  ");
        printToLCD(1, 1, "Dosingpump PH- OFF");
      }

    mode = 0; // go back to normal mode
    }
  }
  else
  { // maintenance mode
    printMode();

    if (cleanPhMinus)
    {
      flushPhMinus();
    }
    if (cleanPhPlus)
    {
      flushPhPlus();
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
