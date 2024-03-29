
void startpHPlus()
{
    if (debug)
        Serial.println("Dosingpump PH+ ON");
    digitalWrite(pHPlusPump, HIGH); // dosing PH+
    if (mode == 3)
        maintPrintOutputStatus();
}

void stoppHPlus()
{
    digitalWrite(pHPlusPump, LOW); // cutting power to pump
    if (debug)
        Serial.println("Dosingpump PH+ OFF");
    if (mode == 3)
        maintPrintOutputStatus(); // printToLCD(14, 2, "PH-");
}

void startpHMinus()
{
    if (debug)
        Serial.println("Dosingpump PH- ON");
    digitalWrite(pHMinusPump, HIGH); // dosing PH-
    if (mode == 3)
        maintPrintOutputStatus();
}

void stoppHMinus()
{
    digitalWrite(pHMinusPump, LOW); // cutting power to pump
    if (debug)
        Serial.println("Dosingpump PH- OFF");
    if (mode == 3)
        maintPrintOutputStatus();
}

void startNutrA()
{
    if (debug)
        Serial.println("Nutrientpump A ON");
    digitalWrite(nutrAPump, HIGH); // dosing nutrition A
    if (mode == 3)
        maintPrintOutputStatus();
}

void stopNutrA()
{
    digitalWrite(nutrAPump, LOW); // cutting power to pump
    if (debug)
        Serial.println("Nutrient A OFF");
    if (mode == 3)
        maintPrintOutputStatus();
}

void startNutrB()
{
    if (debug)
        Serial.println("Nutrientpump B ON");
    digitalWrite(nutrBPump, HIGH); // dosing nutrition B
    if (mode == 3)
        maintPrintOutputStatus();
}

void stopNutrB()
{
    digitalWrite(nutrBPump, LOW); // cutting power to pump
    if (debug)
        Serial.println("Nutrient B OFF");
    if (mode == 3)
        maintPrintOutputStatus();
}

void startStirrer()
{
    if (debug)
        Serial.println("Stirrer ON");
    digitalWrite(stirrer, HIGH); // dosing nutrition B
    if (debug)
        Serial.println("Stirrer OFF");
    if (mode == 3)
        maintPrintOutputStatus();
}

void stopStirrer()
{
    digitalWrite(stirrer, LOW); // cutting power to pump
    if (debug)
        Serial.println("Stirrer OFF");
    if (mode == 3)
        maintPrintOutputStatus();
}

void stopOutputs()
{
    stoppHPlus();
    stoppHMinus();
    stopNutrA();
    stopNutrB();
    stopStirrer();
}

void checkOutputStop()
{
    /**********
       Nutrient pumps
     **********/
    if ((digitalRead(nutrAPump)) && (currentMillis - nutrAStartMillis >= vars[0]))
    { // time to stop the pumps
        stopNutrA();
        stopNutrB();
    }

    /**********
       PH pumps
     **********/
    if ((digitalRead(pHPlusPump)) && (currentMillis - pHPlusStartMillis >= vars[1]))
    { // time to stop the pump
        stoppHPlus();
    }

    if ((digitalRead(pHMinusPump)) && (currentMillis - pHMinusStartMillis >= vars[2]))
    { // time to stop the pump
        stoppHMinus();
    }

    /**********
       Stirrer
     **********/
    if ((digitalRead(stirrer)) && (currentMillis - stirStartMillis >= vars[5]))
    { // time to stop the pump
        stopStirrer();
        stirStopMillis = currentMillis;
    }
}

void checkMaintStop()
{
    /**********
     * Nutrient pump A
     **********/
    if ((digitalRead(nutrAPump)) && (currentMillis - nutrAStartMillis >= vars[3]))
    { // time to stop the pump
        stopNutrA();
    }

    /**********
     * Nutrient pump B
     **********/
    if ((digitalRead(nutrBPump)) && (currentMillis - nutrBStartMillis >= vars[3]))
    { // time to stop the pump
        stopNutrB();
    }

    /**********
     * PH pumps
     **********/
    if ((digitalRead(pHPlusPump)) && (currentMillis - pHPlusStartMillis >= vars[3]))
    { // time to stop the pump
        stoppHPlus();
    }

    if ((digitalRead(pHMinusPump)) && (currentMillis - pHMinusStartMillis >= vars[3]))
    { // time to stop the pump
        stoppHMinus();
    }

    /**********
       Stirrer
     **********/
    if ((digitalRead(stirrer)) && (currentMillis - stirStartMillis >= vars[3]))
    { // time to stop the pump
        stopStirrer();
    }
}

void esp01HardwareReset(void)
{ // reset ESP
    if (debug)
        Serial.println("Resetting...");
    digitalWrite(espHardwareReset, LOW);
    delay(500);
    digitalWrite(espHardwareReset, HIGH);
    delay(8000); // time needed to start reading
    if (debug)
        Serial.println("RESET!");
}
