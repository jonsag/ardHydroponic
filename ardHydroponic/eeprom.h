#define EEPROM_write(address, p)        \
  {                                     \
    int i = 0;                          \
    byte *pp = (byte *)&(p);            \
    for (; i < sizeof(p); i++)          \
      EEPROM.write(address + i, pp[i]); \
  }
  
#define EEPROM_read(address, p)         \
  {                                     \
    int i = 0;                          \
    byte *pp = (byte *)&(p);            \
    for (; i < sizeof(p); i++)          \
      pp[i] = EEPROM.read(address + i); \
  }

byte readEEPROMAddress(byte address)
{
    return EEPROM.read(address);
}

void writeValue(byte address, byte value)
{
    EEPROM.write(address, value);
}

void useValue(byte address, byte value)
{
    Serial.print(varNames[i]);
    Serial.print(" = ");
    switch (address)
    {
    case 0:
        nutrientsPumpTime = storedValueToReal(address, value);
        Serial.println(nutrientsPumpTime);
        break;
    case 1:
        pHPlusPumpTime = storedValueToReal(address, value);
        Serial.println(pHPlusPumpTime);
        break;
    case 2:
        pHMinusPumpTime = storedValueToReal(address, value);
        Serial.println(pHMinusPumpTime);
        break;
    case 3:
        cleanTime = storedValueToReal(address, value);
        Serial.println(cleanTime);
        break;
    case 4:
        iterationTime = storedValueToReal(address, value);
        Serial.println(iterationTime);
        break;
    case 5:
        pHLow = storedValueToReal(address, value);
        Serial.println(pHLow);
        break;
    case 6:
        pHHigh = storedValueToReal(address, value);
        Serial.println(pHHigh);
        break;
    case 7:
        ECLow = storedValueToReal(address, value);
        Serial.println(ECLow);
        break;
    }
}

void setValue(byte address, byte value)
{
    Serial.print(varNames[i]);
    Serial.print(" = ");
    switch (address)
    {
    case 0:
        Serial.println(nutrientsPumpTime);
        writeValue(address, realValueToStored(address, nutrientsPumpTime));
        break;
    case 1:
        Serial.println(pHPlusPumpTime);
        writeValue(address, realValueToStored(address, pHPlusPumpTime));
        break;
    case 2:
        Serial.println(pHMinusPumpTime);
        writeValue(address, realValueToStored(address, pHMinusPumpTime));
        break;
    case 3:
        Serial.println(cleanTime);
        writeValue(address, realValueToStored(address, cleanTime));
        break;
    case 4:
        Serial.println(iterationTime);
        writeValue(address, realValueToStored(address, iterationTime));
        break;
    case 5:
        Serial.println(pHLow);
        writeValue(address, realValueToStored(address, pHLow));
        break;
    case 6:
        Serial.println(pHHigh);
        writeValue(address, realValueToStored(address, pHHigh));
        break;
    case 7:
        Serial.println(ECLow);
        writeValue(address, realValueToStored(address, ECLow));
        break;
    }
}

void readAllEEPROM()
{
    for (i = 0; i < noOfVars; i++)
    {
        Serial.print(varNames[i]);
        Serial.print(": ");
        //Serial.println(storedValueToReal(i, readEEPROMAddress(i)));
        Serial.println(readEEPROMAddress(i));
    }
}

boolean hasValueStored(byte address)
{
    if (readEEPROMAddress(address) == 255 || readEEPROMAddress(address) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void initEEPROMCheck()
{
    for (i = 0; i < noOfVars; i++)
    {
        Serial.print("Checking if there's a value stored for ");
        Serial.print(varNames[i]);
        Serial.println("...");

        EEPROM_read(i * 10, tempValue);;
        Serial.println(tempValue);
        if (tempValue != 0 && tempValue != 255)
        {
            Serial.println("Had a value, using it!");
            useValue(i, tempValue);
        }
        else
        {
            Serial.println("Had no value, writing it...");
            setValue(i, tempValue);
        }
    }
}

void clearEEPROM()
{
    Serial.println("Clearing EEPROM...");
    for (i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0);
    }
}