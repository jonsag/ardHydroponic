void maintButtonPush()
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

void checkRotaryEncoder()
{
    if (rotEncPush == 1)
    { // button pushed
        Serial.println("Rotary encoder pushed");

        switch (mode)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            maintButtonPush(); // check if mode has change
            break;
        case 4:
            break;
        }
    }

    if (rotEncLongPush == 1)
    { // nutton pushed a long time
        Serial.println("Rotary encoder long push");

        switch (mode)
        {
        case 0:
            stopPumps();
            mode = 3;
            checkMode(); // check if mode has change
            break;
        case 1:
            stopPumps();
            mode = 3;
            checkMode(); // check if mode has change
            break;
        case 2:
            stopPumps();
            mode = 3;
            checkMode(); // check if mode has change
            break;
        case 3:
            stopPumps();
            mode = 4;
            checkMode(); // check if mode has change
            break;
        case 4:
            stopPumps();
            mode = 0;
            checkMode();
            break;
        }
    }

    if (rotEncRot != 0)
    { // button rotated
        Serial.print("Encoder rotated ");
        if (rotEncRot == 2)
        {
            Serial.println("CW");

            switch (mode)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                pumpNumber++;
                if (pumpNumber > 3)
                {
                    pumpNumber = 3;
                }
                printSelectedPump();
                break;
            case 4:
                break;
            }
        }
        else if (rotEncRot == 1)
        {
            Serial.println("CCW");

            switch (mode)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                pumpNumber--;
                if (pumpNumber < 0)
                {
                    pumpNumber = 0;
                }
                printSelectedPump();
                break;
            case 4:
                break;
            }
        }
    }
}

void handleRotaryEncoder()
{
    if (rotEncRot == 1 || rotEncRot == 2 || rotEncPush == 1 || rotEncLongPush == 1)
    {
        checkRotaryEncoder();
    }
}
