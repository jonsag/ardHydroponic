
/*
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
*/

void putEEPROM(byte address, float value) {
     EEPROM.put(address, value);
}

float getEEPROM(byte address, float value) {
    EEPROM.get(address, value );
    return value;
}

void useValue(byte address, float value)
{
    Serial.print(varNames[i]);
    Serial.print(" = ");
    switch (address / 10)
    {
    case 0:
        nutrientsPumpTime = value;
        nutrientsPumpTimeNew = nutrientsPumpTime;
        Serial.println(nutrientsPumpTime);
        break;
    case 1:
        pHPlusPumpTime = value;
        pHPlusPumpTimeNew = pHPlusPumpTime;
        Serial.println(pHPlusPumpTime);
        break;
    case 2:
        pHMinusPumpTime = value;
        pHMinusPumpTimeNew = pHMinusPumpTime;
        Serial.println(pHMinusPumpTime);
        break;
    case 3:
        cleanTime = value;
        cleanTimeNew = cleanTime;
        Serial.println(cleanTime);
        break;
    case 4:
        iterationTime = value;
        iterationTimeNew = iterationTime;
        Serial.println(iterationTime);
        break;
    case 5:
        pHLow = value;
        pHLowNew = pHLow;
        Serial.println(pHLow);
        break;
    case 6:
        pHHigh = value;
        pHHighNew = pHHigh;
        Serial.println(pHHigh);
        break;
    case 7:
        tdsLow = value;
        tdsLowNew = tdsLow;
        Serial.println(tdsLow);
        break;
    case 8:
        kValue = value;
        kValueNew = kValue;
        Serial.println(kValue);
        break;
    case 9:
        tdsFactor = value;
        tdsFactorNew = tdsFactor;
        Serial.println(tdsFactor);
        break;
    }
}

void writeValue(byte address)
{
    Serial.print(varNames[i]);
    Serial.print(" = ");
    switch (address / 10)
    {
    case 0:
        Serial.println(nutrientsPumpTime);
        //EEPROM_write(address, nutrientsPumpTime);
        putEEPROM(address, nutrientsPumpTime);
        break;
    case 1:
        Serial.println(pHPlusPumpTime);
        //EEPROM_write(address, pHPlusPumpTime);
        putEEPROM(address, pHPlusPumpTime);
        break;
    case 2:
        Serial.println(pHMinusPumpTime);
        //EEPROM_write(address, pHMinusPumpTime);
        putEEPROM(address, pHMinusPumpTime);
        break;
    case 3:
        Serial.println(cleanTime);
        //EEPROM_write(address, cleanTime);
        putEEPROM(address, cleanTime);
        break;
    case 4:
        Serial.println(iterationTime);
        //EEPROM_write(address, iterationTime);
        putEEPROM(address, iterationTime);
        break;
    case 5:
        Serial.println(pHLow);
        //EEPROM_write(address, pHLow);
        putEEPROM(address, pHLow);
        break;
    case 6:
        Serial.println(pHHigh);
        //EEPROM_write(address, pHHigh);
        putEEPROM(address, pHHigh);
        break;
    case 7:
        Serial.println(tdsLow);
        //EEPROM_write(address, tdsLow);
        putEEPROM(address, tdsLow);
        break;
    case 8:
        Serial.println(kValue);
        //EEPROM_write(address, kValue);
        putEEPROM(address, kValue);
        break;
    case 9:
        Serial.println(tdsFactor);
        //EEPROM_write(address, tdsFactor);
        putEEPROM(address, tdsFactor);
        break;
    }
}

void initEEPROMCheck()
{
    for (i = 0; i < noOfVars; i++)
    {
        Serial.print("Checking if there's a value stored in eeprom for ");
        Serial.print(varNames[i]);
        Serial.print(" at address ");
        Serial.print(i * 10);
        Serial.println("...");

        //EEPROM_read(i * 10, tempValue);
        tempValue = getEEPROM(i * 10, tempValue);

        if (tempValue != 0 && tempValue != 32000.00 && !isnan(tempValue))
        {
            Serial.println("Had a value: ");
            Serial.println(tempValue);
            Serial.println("Using it!");
            useValue(i, tempValue);
        }
        else
        {
            Serial.println("Had no value: ");
            Serial.println(tempValue);
            Serial.print("Writing it to eeprom at address ");
            Serial.print(i * 10);
            Serial.println("...");
            writeValue(i * 10);
        }
        Serial.println();
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