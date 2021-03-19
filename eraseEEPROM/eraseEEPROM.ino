/*
   EEPROM Write
*/

#include <EEPROM.h>

int address = 0; // the current address in the EEPROM (i.e. which byte we're going to write to next)

const byte value = 0xFF;

void setup()
{
  Serial.begin(9600); // initialize serial and wait for port to open:

  while (!Serial)
  { // wait for serial port to connect. Needed for native USB port only
    ;
  }

  Serial.println();
  Serial.print("Erasing EEPROM at all addresses, from ");
  Serial.print(address);
  Serial.print(" to ");
  Serial.println(EEPROM.length() - 1);

  Serial.print("Setting all to:\tHEX: ");
  Serial.print(value, HEX);
  Serial.print("\tDEC: ");
  Serial.println(value, DEC);
  Serial.println("...");

  erase();
}

void loop()
{
  // empty
}

void erase()
{
  for (address; address < EEPROM.length(); address++)
  {

    EEPROM.write(address, value);

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

    ++addr &= EEPROM.length() - 1;
  ***/

  Serial.println("Finished!");
}
