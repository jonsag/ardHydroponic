void button1Push()
{
    Serial.print("Cleaning ");

    switch (outputNumber)
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
            button1Push(); // check if mode has change
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
            stopOutputs();
            mode = 3;
            checkMode(); // check if mode has change
            break;
        case 1:
            stopOutputs();
            mode = 3;
            checkMode(); // check if mode has change
            break;
        case 2:
            stopOutputs();
            mode = 3;
            checkMode(); // check if mode has change
            break;
        case 3:
            stopOutputs();
            mode = 4;
            checkMode(); // check if mode has change
            break;
        case 4:
            stopOutputs();
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
                outputNumber++;
                if (outputNumber > 3)
                {
                    outputNumber = 3;
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
                outputNumber--;
                if (outputNumber < 0)
                {
                    outputNumber = 0;
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
