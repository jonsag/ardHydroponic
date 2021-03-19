
void putEEPROM(byte address, float value)
{
    EEPROM.put(address, value);
}

float getEEPROM(byte address, float value)
{
    EEPROM.get(address, value);
    return value;
}

void useValue(byte address, float value)
{
    Serial.print(varNames[address / addressMultiplicator]);
    Serial.print(" = ");
    vars[address / addressMultiplicator] = value;
    //nutrientsPumpTimeNew = vars[address / addressMultiplicator];
    Serial.println(vars[address / addressMultiplicator]);
}

void writeValue(byte address)
{
    Serial.print(varNames[address / addressMultiplicator]);
    Serial.print(" = ");
    Serial.println(vars[address / addressMultiplicator]);
    //EEPROM_write(address, vars[address / addressMultiplicator]);
    putEEPROM(address, vars[address / addressMultiplicator]);
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
            Serial.println("Had no value: ");
            Serial.println(tempValue);
            Serial.print("Writing it to eeprom at address ");
            Serial.print(i * addressMultiplicator);
            Serial.println("...");
            writeValue(i * addressMultiplicator);
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