void startpHPlus()
{
    Serial.println("Dosingpump PH+ ON");
    printToLCD(8, 2, "PH+");
    digitalWrite(pHPlusPump, HIGH); // dosing PH+
}

void stoppHPlus()
{
    digitalWrite(pHPlusPump, LOW); // cutting power to pump
    Serial.println("Dosingpump PH+ OFF");
    printToLCD(8, 2, "   ");
}

void startpHMinus()
{
    Serial.println("Dosingpump PH- ON");
    printToLCD(14, 2, "PH-");
    digitalWrite(pHMinusPump, HIGH); // dosing PH-
}

void stoppHMinus()
{
    digitalWrite(pHMinusPump, LOW); // cutting power to pump
    Serial.println("Dosingpump PH- OFF");
    printToLCD(14, 2, "   ");
}

void startNutrA()
{
    Serial.println("Nutrientpump A ON");
    printToLCD(8, 3, "NutrA");
    digitalWrite(nutrAPump, HIGH); // dosing nutrition A
}

void stopNutrA()
{
    digitalWrite(nutrAPump, LOW); // cutting power to pump
    Serial.println("Nutrient A OFF");
    printToLCD(8, 3, "     ");
}

void startNutrB()
{
    Serial.println("Nutrientpump B ON");
    printToLCD(14, 3, "NutrB");
    digitalWrite(nutrBPump, HIGH); // dosing nutrition B
}

void stopNutrB()
{
    digitalWrite(nutrBPump, LOW); // cutting power to pump
    Serial.println("Nutrient B OFF");
    printToLCD(14, 3, "     ");
}

void startStirrer()
{
    Serial.println("Stirrer ON");
    //printToLCD(14, 3, "NutrB");
    digitalWrite(stirrer, HIGH); // dosing nutrition B
}

void stopStirrer()
{
    digitalWrite(stirrer, LOW); // cutting power to pump
    Serial.println("Stirrer OFF");
    //printToLCD(14, 3, "     ");
    stirStopMillis = currentMillis;
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
    if ((digitalRead(nutrAPump)) && (currentMillis - nutrAStartMillis > nutrientsPumpTime))
    { // time to stop the pumps
        stopNutrA();
        stopNutrB();
    }

    /**********
       PH pumps
     **********/
    if ((digitalRead(pHPlusPump)) && (currentMillis - pHPlusStartMillis > pHPlusPumpTime))
    { // time to stop the pump
        stoppHPlus();
    }

    if ((digitalRead(pHMinusPump)) && (currentMillis - pHMinusStartMillis > pHMinusPumpTime))
    { // time to stop the pump
        stoppHMinus();
    }

    /**********
       Stirrer
     **********/
    if ((digitalRead(stirrer)) && (currentMillis - stirStartMillis > stirTime))
    { // time to stop the pump
        stopStirrer();
    }
}

void checkMaintStop()
{
    /**********
    * Nutrient pump A
    **********/
    if ((digitalRead(nutrAPump)) && (currentMillis - nutrAStartMillis > cleanTime))
    { // time to stop the pump
        stopNutrA();
    }

    /**********
    * Nutrient pump B
    **********/
    if ((digitalRead(nutrBPump)) && (currentMillis - nutrBStartMillis > cleanTime))
    { // time to stop the pump
        stopNutrB();
    }

    /**********
    * PH pumps
    **********/
    if ((digitalRead(pHPlusPump)) && (currentMillis - pHPlusStartMillis > cleanTime))
    { // time to stop the pump
        stoppHPlus();
    }

    if ((digitalRead(pHMinusPump)) && (currentMillis - pHMinusStartMillis > cleanTime))
    { // time to stop the pump
        stoppHMinus();
    }

    /**********
       Stirrer
     **********/
    if ((digitalRead(stirrer)) && (currentMillis - stirStartMillis > cleanTime))
    { // time to stop the pump
        stopStirrer();
    }
}