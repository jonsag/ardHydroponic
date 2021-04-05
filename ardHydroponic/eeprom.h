
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
    if (debug) Serial.print(varNames[varNo]);
    if (debug) Serial.print(" = ");
    vars[varNo] = value;
    //nutrientsPumpTimeNew = vars[address / addressMultiplicator];
    if (debug) Serial.println(vars[varNo]);
}

void writeValue(byte varNo)
{
    if (debug) Serial.print(varNames[varNo]);
    if (debug) Serial.print(" = ");
    if (debug) Serial.println(vars[varNo]);
    //EEPROM_write(address, vars[address / addressMultiplicator]);
    putEEPROM(varNo * addressMultiplicator, vars[varNo]);
}

void initEEPROMCheck()
{
    for (i = 0; i < noOfVars; i++)
    {
        if (debug) Serial.print("Checking if there's a value stored in eeprom for ");
        if (debug) Serial.print(varNames[i]);
        if (debug) Serial.print(" at address ");
        if (debug) Serial.print(i * addressMultiplicator);
        if (debug) Serial.println("...");

        //EEPROM_read(i * addressMultiplicator, tempValue);
        tempValue = getEEPROM(i * addressMultiplicator, tempValue);

        if (tempValue != 0 && tempValue != 32000.00 && !isnan(tempValue))
        {
            if (debug) Serial.println("Had a value: ");
            if (debug) Serial.println(tempValue);
            if (debug) Serial.println("Using it!");
            useValue(i, tempValue);
        }
        else
        {
            if (debug) Serial.print("Had no value: ");
            if (debug) Serial.println(tempValue);
            if (debug) Serial.print("Writing it to eeprom at address ");
            if (debug) Serial.print(i * addressMultiplicator);
            if (debug) Serial.println("...");
            writeValue(i);
        }
        if (debug) Serial.println();
    }
}

void clearEEPROM()
{
    if (debug) Serial.println("Clearing EEPROM...");
    for (i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0xFF);
    }
    if (debug) Serial.println("Finished!");
    if (debug) Serial.println();
}