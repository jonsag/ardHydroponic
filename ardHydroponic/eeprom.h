
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
        vars[0] = value;
        //nutrientsPumpTimeNew = vars[0];
        Serial.println(vars[0]);
        break;
    case 1:
        vars[1] = value;
        //pHPlusPumpTimeNew = vars[1];
        Serial.println(vars[1]);
        break;
    case 2:
        vars[2] = value;
        //pHMinusPumpTimeNew = vars[2];
        Serial.println(vars[2]);
        break;
    case 3:
        vars[3] = value;
        //cleanTimeNew = vars[3];
        Serial.println(vars[3]);
        break;
    case 4:
        vars[4] = value;
        //iterationTimeNew = vars[4];
        Serial.println(vars[4]);
        break;
    case 5:
        vars[7] = value;
        //pHLowNew = vars[7];
        Serial.println(vars[7]);
        break;
    case 6:
        vars[8] = value;
        //pHHighNew = vars[8];
        Serial.println(vars[8]);
        break;
    case 7:
        vars[9] = value;
        //tdsLowNew = vars[9];
        Serial.println(vars[9]);
        break;
    case 8:
        vars[10] = value;
        //kValueNew = vars[10];
        Serial.println(vars[10]);
        break;
    case 9:
        vars[11] = value;
        //tdsFactorNew = vars[11];
        Serial.println(vars[11]);
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
        Serial.println(vars[0]);
        //EEPROM_write(address, vars[0]);
        putEEPROM(address, vars[0]);
        break;
    case 1:
        Serial.println(vars[1]);
        //EEPROM_write(address, vars[1]);
        putEEPROM(address, vars[1]);
        break;
    case 2:
        Serial.println(vars[2]);
        //EEPROM_write(address, vars[2]);
        putEEPROM(address, vars[2]);
        break;
    case 3:
        Serial.println(vars[3]);
        //EEPROM_write(address, vars[3]);
        putEEPROM(address, vars[3]);
        break;
    case 4:
        Serial.println(vars[4]);
        //EEPROM_write(address, vars[4]);
        putEEPROM(address, vars[4]);
        break;
    case 5:
        Serial.println(vars[7]);
        //EEPROM_write(address, vars[7]);
        putEEPROM(address, vars[7]);
        break;
    case 6:
        Serial.println(vars[8]);
        //EEPROM_write(address, vars[8]);
        putEEPROM(address, vars[8]);
        break;
    case 7:
        Serial.println(vars[9]);
        //EEPROM_write(address, vars[9]);
        putEEPROM(address, vars[9]);
        break;
    case 8:
        Serial.println(vars[10]);
        //EEPROM_write(address, vars[10]);
        putEEPROM(address, vars[10]);
        break;
    case 9:
        Serial.println(vars[11]);
        //EEPROM_write(address, vars[11]);
        putEEPROM(address, vars[11]);
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