#define EEPROM_write(address, p)              \
    {                                         \
        int i = 0;                            \
        byte *pp = (byte *)&(p);              \
        for (; i < sizeof(p); i++)            \
            EEPROM.write(address + i, pp[i]); \
    }

#define EEPROM_read(address, p)               \
    {                                         \
        int i = 0;                            \
        byte *pp = (byte *)&(p);              \
        for (; i < sizeof(p); i++)            \
            pp[i] = EEPROM.read(address + i); \
    }

void useValue(byte address, float value)
{
    Serial.print(varNames[i]);
    Serial.print(" = ");
    switch (address)
    {
    case 0:
        nutrientsPumpTime = value;
        Serial.println(nutrientsPumpTime);
        break;
    case 1:
        pHPlusPumpTime = value;
        Serial.println(pHPlusPumpTime);
        break;
    case 2:
        pHMinusPumpTime = value;
        Serial.println(pHMinusPumpTime);
        break;
    case 3:
        cleanTime = value;
        Serial.println(cleanTime);
        break;
    case 4:
        iterationTime = value;
        Serial.println(iterationTime);
        break;
    case 5:
        pHLow = value;
        Serial.println(pHLow);
        break;
    case 6:
        pHHigh = value;
        Serial.println(pHHigh);
        break;
    case 7:
        tdsLow = value;
        Serial.println(tdsLow);
        break;
    case 8:
        kValue = value;
        Serial.println(kValue);
        break;
    case 9:
        tdsFactor = value;
        Serial.println(tdsFactor);
        break;
    }
}

void setValue(byte address, float value)
{
    Serial.print(varNames[i]);
    Serial.print(" = ");
    switch (address)
    {
    case 0:
        Serial.println(nutrientsPumpTime);
        EEPROM_write(address, value);
        break;
    case 1:
        Serial.println(pHPlusPumpTime);
        EEPROM_write(address, value);
        break;
    case 2:
        Serial.println(pHMinusPumpTime);
        EEPROM_write(address, value);
        break;
    case 3:
        Serial.println(cleanTime);
        EEPROM_write(address, value);
        break;
    case 4:
        Serial.println(iterationTime);
        EEPROM_write(address, value);
        break;
    case 5:
        Serial.println(pHLow);
        EEPROM_write(address, value);
        break;
    case 6:
        Serial.println(pHHigh);
        EEPROM_write(address, value);
        break;
    case 7:
        Serial.println(tdsLow);
        EEPROM_write(address, value);
        break;
    case 8:
        Serial.println(kValue);
        EEPROM_write(address, value);
        break;
    case 9:
        Serial.println(tdsFactor);
        EEPROM_write(address, value);
        break;
    }
}

void initEEPROMCheck()
{
    for (i = 0; i < noOfVars; i++)
    {
        Serial.print("Checking if there's a value stored for ");
        Serial.print(varNames[i]);
        Serial.println("...");

        EEPROM_read(i * 10, tempValue);
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
        EEPROM.write(i, 0xFF);
    }
}