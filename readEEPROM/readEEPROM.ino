/*
   EEPROM Read
   jonsagebrand@gmail.com
*/

#include <EEPROM.h>

int address = 0; // start reading from the first byte (address 0) of the EEPROM
byte value;

void setup()
{
  Serial.begin(9600); // initialize serial and wait for port to open:

  while (!Serial)
  { // wait for serial port to connect. Needed for native USB port only
    ;
  }

  Serial.println();
  Serial.print("Reading all EEPROM addresses, from ");
  Serial.print(address);
  Serial.print(" to ");
  Serial.println(EEPROM.length() - 1);
  Serial.println("----------");

  read();
}

void loop()
{
  // empty
}

void read()
{

  for (address; address < EEPROM.length(); address++)
  {

    value = EEPROM.read(address); // read a byte from the current address of the EEPROM

    Serial.print(address);
    Serial.print(":\tHEX: ");
    Serial.print(value, HEX);
    Serial.print("\tDEC: ");
    Serial.print(value, DEC);
    Serial.println();

    /***
      Advance to the next address

      Larger AVR processors have larger EEPROM sizes, E.g:
      - Arduino Duemilanove: 512b EEPROM storage.
      - Arduino Uno:        1kb EEPROM storage.
      - Arduino Mega:       4kb EEPROM storage.

      Rather than hard-coding the length, you should use the pre-provided length function.
      This will make your code portable to all AVR processors.
    ***/
  }

  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/

  Serial.println("Finished!");
}
