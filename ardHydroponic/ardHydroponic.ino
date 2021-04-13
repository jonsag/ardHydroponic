
/**********
* Include files
**********/

#include "config.h"
#include "logging.h"
#include "LCD.h"
#include "outputs.h"
#include "read.h"
#include "misc.h"
#include "eeprom.h"
#include "specialMaint.h"
#include "buttons.h"

void setup()
{
  /***********
  * Serial
  ***********/
  Serial.begin(serialBaudRate); // serial baudrate

  /*******************************
  * Print start information
  *******************************/
  if (debug)
    Serial.println();
  if (debug)
    Serial.println(programName);
  if (debug)
    Serial.println(date);
  if (debug)
    Serial.print("by ");
  if (debug)
    Serial.println(author);
  if (debug)
    Serial.println(email);
  if (debug)
    Serial.println();

  /**********
  * LCD
  **********/
  if (debug)
    Serial.println("Starting LCD...");

  lcd.begin();
  if (debug)
    Serial.println();

  bootScreen(programName);
  bootScreen(date);

  /**********
  * EEPROM
  **********/
  //clearEEPROM();
  if (debug)
    Serial.println("Reading EEPROM...");
  bootScreen("Reading EEPROM...   ");

  initEEPROMCheck();
  if (debug)
    Serial.println();

  /**********
  * In/Outputs
  **********/
  if (debug)
    Serial.println("Starting In/Outputs...");
  bootScreen("Starting In/Outputs.");

  pinMode(pHPlusPump, OUTPUT);
  pinMode(pHMinusPump, OUTPUT);
  pinMode(nutrAPump, OUTPUT);
  pinMode(nutrBPump, OUTPUT);
  pinMode(stirrer, OUTPUT);

  pinMode(espHardwareReset, OUTPUT);

  digitalWrite(resetPin, HIGH); // set pin high before it's defined
  pinMode(resetPin, OUTPUT);

  if (debug)
    Serial.println();

  /**********
  * Setup FTDebouncer pins
  **********/
  if (debug)
    Serial.println("Setting up buttons...");
  bootScreen("Setting up buttons..");

  pinDebouncer.addPin(button1, LOW); // pin has external pull-down resistor
  pinDebouncer.addPin(button2, LOW);
  pinDebouncer.addPin(button3, LOW);
  pinDebouncer.addPin(button4, LOW);
  pinDebouncer.addPin(button5, LOW);

  pinDebouncer.init(); // initiate debounce

  if (debug)
    Serial.println();

  /**********
   * ESP-01
   **********/
  if (debug)
    Serial.println("Starting ESP-01...");
  bootScreen("Starting ESP-01...  ");

  digitalWrite(espHardwareReset, HIGH);
  if (debug)
    Serial.println();

  if (debug)
    Serial.println("Starting Serial1 for ESP communication...");
  bootScreen("Starting Serial1... ");

  Serial1.begin(serialBaudRate);
  if (debug)
    Serial.println();

  if (debug)
    Serial.println("Resetting ESP module...");
  bootScreen("Resetting ESP module");

  esp01HardwareReset();
  if (debug)
    Serial.println();

  /**********
  * Initiate screen
  **********/
  clearLCD();
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

  /**********
   * Count down on LCD
   **********/
  if (mode == 0)
  { // normal mode

    counter = (vars[4] - (currentMillis - readMillis)) / 1000;

    if ((counter != oldCounter) && (counter >= 0) && (counter <= readMillis / 1000))
    {
      printToLCD(17, 0, String(counter));
      printToLCD(17 + intLength(counter), 0, " ");

      /*
      if (counter <= 1)
      {
        if (debug) Serial.println("Powering EC sensor...");
        digitalWrite(ECPower, HIGH); // setting the power pin for EC sensor to high
      }
      */

      oldCounter = counter;
    }

    /**********
     * Upload data
     **********/
    if (currentMillis - readMillis > max(vars[0], max(vars[1], vars[2])) && newData)
    { // pumps has stopped
      mode = 2;
      checkMode();
      if (debug)
        Serial.println("Writing to Serial1...");
      writeToSerial1();
      //writeThingSpeak();
      mode = 0;
      checkMode();
      newData = 0;
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

    checkOutputStop(); // check if it's time to stop the pumps or stirrer
  }
  else if (mode == 3)
  {                   // maintenance mode
    checkMaintStop(); // check if pumps are running and if it's time to stop any of them
  }
  else if (mode == 5)
  {
    doSpecialMaint();
  }

  if (button1PushMillis != 0 && currentMillis - button1PushMillis >= longPushTime)
  {
    button1PushMillis = 0;
    longPush = 1;
    longPushButton1();
  }
}
