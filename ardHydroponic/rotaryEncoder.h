void maintButtonPush(int pumpNumber)
{
    Serial.print("Cleaning ");

    switch (pumpNumber)
    {
    case 0: // pH+
        Serial.println("pH+");
            if (digitalRead(pHPlusPump))
            {
                stoppHPlus();
            }
            else
            {
                startpHPlus();
                pHPlusStartMillis = currentMillis;
            }
        break;
    case 1: // pH-
        Serial.println("pH-");
            if (digitalRead(pHMinusPump))
            {
                stoppHMinus();
            }
            else
            {
                startpHMinus();
                pHMinusStartMillis = currentMillis;
            }
        break;
    case 2: // Nutr A
        Serial.println("Nutr A");
            if (digitalRead(nutrAPump))
            {
                stopNutrA();
            }
            else
            {
                startNutrA();
                nutrAStartMillis = currentMillis;
            }
        break;
    case 3: // Nutr B
        Serial.println("Nutr B");
            if (digitalRead(nutrBPump))
            {
                stopNutrB();
            }
            else
            {
                startNutrB();
                nutrBStartMillis = currentMillis;
            }
        break;
    }
}

void checkRotary()
{
    if (rotEncPush == 1 && rotEncPushed == 0)
    {
        Serial.println("Rotary encoder push");
        rotEncPushed = 1;
    }

    if (rotEncLongPush == 1)
    {
        Serial.println("Rotary encoder long push");
        if (mode != 4)
        {
            stopPumps();
            mode = 4;
            checkMode(); // check if mode has changed
            //maintStartMillis = currentMillis;
        }
        else
        {
            stopPumps();
            mode = 0;
            checkMode(); // check if mode has changed
        }
        rotEncPushed = 0;
    }

    if (rotEncRot != 0)
    {
        Serial.print("Encoder rotated ");
        if (rotEncRot == 1)
        {
            Serial.println("CW");
        }
        else if (rotEncRot == 2)
        {
            Serial.println("CCW");
        }
    }
}

void rotEncMaint()
{
    Serial.println("maintButton");
    if (mode != 3 && mode != 4)
    {
        stopPumps();
        mode = 3;
        checkMode(); // check if mode has changed
        maintStartMillis = currentMillis;
    }
    else
    {
        stopPumps();
        mode = 0;
        checkMode(); // check if mode has changed
    }
    rotEncPushed = 0;
}

void handleRotary()
{
    if (rotEncRot == 1 || rotEncRot == 2 || rotEncPush == 1 || rotEncLongPush == 1)
    {
        checkRotary();
    }
    else if (rotEncPush == 0 && rotEncPushed == 1 && mode != 4)
    {
        rotEncMaint();
    }
}
