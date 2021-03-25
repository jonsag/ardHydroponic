
void putEEPROM(byte address, float value)
{
    EEPROM.put(address, value);
}

float getEEPROM(byte address, float value)
{
    EEPROM.get(address, value);
    return value;
}

void useValue(byte varNo, float value)
{
    Serial.print(varNames[varNo]);
    Serial.print(" = ");
    vars[varNo] = value;
    //nutrientsPumpTimeNew = vars[address / addressMultiplicator];
    Serial.println(vars[varNo]);
}

void writeValue(byte varNo)
{
    Serial.print(varNames[varNo]);
    Serial.print(" = ");
    Serial.println(vars[varNo]);
    //EEPROM_write(address, vars[address / addressMultiplicator]);
    putEEPROM(varNo * addressMultiplicator, vars[varNo]);
}

void initEEPROMCheck()
{
    for (i = 0; i < noOfVars; i++)
    {
        Serial.print("Checking if there's a value stored in eeprom for ");
        Serial.print(varNames[i]);
        Serial.print(" at address ");
        Serial.print(i * addressMultiplicator);
        Serial.println("...");

        //EEPROM_read(i * addressMultiplicator, tempValue);
        tempValue = getEEPROM(i * addressMultiplicator, tempValue);

        if (tempValue != 0 && tempValue != 32000.00 && !isnan(tempValue))
        {
            Serial.println("Had a value: ");
            Serial.println(tempValue);
            Serial.println("Using it!");
            useValue(i, tempValue);
        }
        else
        {
            Serial.print("Had no value: ");
            Serial.println(tempValue);
            Serial.print("Writing it to eeprom at address ");
            Serial.print(i * addressMultiplicator);
            Serial.println("...");
            writeValue(i);
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
    Serial.println("Finished!");
    Serial.println();
}