void startStopCleaning()
{
    if (debug)
        Serial.print("Cleaning ");

    switch (outputNumber)
    {
    case 0: // pH+
        if (debug)
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
        if (debug)
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
        if (debug)
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
        if (debug)
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
    case 4: // stirrer
        if (debug)
            Serial.println("Stir");
        if (digitalRead(stirrer))
        {
            stopStirrer();
        }
        else
        {
            startStirrer();
            stirStartMillis = currentMillis;
        }
        break;
    }
}

void checkSanity()
{
    switch (varNumber)
    {
    case 0: /* 0, Nutr pump time, ms */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 1: /* 1, pH+ pump time, ms */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 2: /* 2, pH- pump time, ms */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 3: /* 3, Clean pumps time */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 4: /* 4, Iteration time, ms */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 5: /* 5, Stir time, ms */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 6: /* 6, Stir interval, ms */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 7: /* 7, pH low, pH */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        else if (tempValue >= vars[8])
        {
            if (debug)
                Serial.println("Can't increase more. Conflicting with pH high");
            tempValue -= incs[7];
        }
        break;
    case 8: /* 8, pH high, pH */
        if (tempValue <= vars[7])
        {
            if (debug)
                Serial.println("Can't decrease more. Conflicting with pH low");
            tempValue += incs[8];
        }
        else if (tempValue > 15)
        {
            if (debug)
                Serial.println("Can't increase more. Not sane value");
            tempValue = 15;
        }
        break;
    case 9: /* 9, TDS low, ppm */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 10: /* 10, k value, factor */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 11: /* 11, TDS factor, factor */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        break;
    case 12: /* 12, Neutral pH, pH */
        if (tempValue < vars[13])
        {
            if (debug)
                Serial.println("Can't decrease more. Conflicting with acid pH");
            tempValue += incs[13];
        }
        else if (tempValue > 15)
        {
            if (debug)
                Serial.println("Can't increase more. Not sane value");
            tempValue = 15;
        }
        break;
    case 13: /* 13, Acid pH, pH */
        if (tempValue < 0)
        {
            if (debug)
                Serial.println("Can't decrease more. Not sane value");
            tempValue = 0;
        }
        else if (tempValue >= vars[12])
        {
            if (debug)
                Serial.println("Can't increase more. Conflicting with neutral pH");
            tempValue -= incs[13];
            break;
        case 15: /* 15, Acid voltage, V */
            break;
        case 16: /* 16, pH voltage offset, V */
            break;
        }
    }
}

void onPinActivated(int pinNumber)
{
    if (debug)
        Serial.println();
    if (debug)
        Serial.print("Pin activated: ");
    if (debug)
        Serial.print(pinNumber);

    switch (pinNumber)
    {             // outer switch start
    case button1: // this button acts on release
        if (debug)
            Serial.println(" <-> button1");
        button1PushMillis = currentMillis;
        break;
    case button2:
        if (debug)
            Serial.println(" <-> button2");
        switch (mode)
        {
        case 3:
            outputNumber--;
            if (outputNumber < 0 || outputNumber == 255)
            {
                outputNumber = 4;
            }
            printSelectedOutput();
            break;
        case 4:
            varNumber--;
            if (varNumber < 0 || varNumber == 255)
            {
                varNumber = noOfVars - 1;
            }
            tempValue = vars[varNumber];
            settingsCheckIfRead();
            printSelectedVar();
            break;
        case 5:
            specialMaintMode--;
            if (specialMaintMode < 0 || specialMaintMode == 255)
            {
                specialMaintMode = 3;
            }
            printSpecialMaintMode();
            break;
        }
        break;
    case button3:
        if (debug)
            Serial.println(" <-> button3");
        switch (mode)
        {
        case 3:
            outputNumber++;
            if (outputNumber > 4)
            {
                outputNumber = 0;
            }
            printSelectedOutput();
            break;
        case 4:
            varNumber++;
            if (varNumber > noOfVars - 1)
            {
                varNumber = 0;
            }
            tempValue = vars[varNumber];
            settingsCheckIfRead();
            printSelectedVar();
            break;
        case 5:
            specialMaintMode++;
            if (specialMaintMode > 3)
            {
                specialMaintMode = 0;
            }
            printSpecialMaintMode();
            break;
        }
        break;
    case button4:
        if (debug)
            Serial.println(" <-> button4");
        switch (mode)
        {
        case 4:
            tempValue -= incs[varNumber];
            checkSanity();
            settingsCheckIfRead();
            printSelectedVar();
            break;
        }
        break;
    case button5:
        if (debug)
            Serial.println(" <-> button5");
        switch (mode)
        {
        case 4:
            tempValue += incs[varNumber];
            checkSanity();
            settingsCheckIfRead();
            printSelectedVar();
            break;
        }
        break;
    } // outer switch stop
}

void onPinDeactivated(int pinNumber)
{
    if (debug)
        Serial.println();
    if (debug)
        Serial.print("Pin deactivated: ");
    if (debug)
        Serial.print(pinNumber);

    switch (pinNumber)
    {
    case button1:
        if (longPush)
        {
            if (debug)
                Serial.println(" <-> button1 - was a long push");
        }
        else
        {
            if (debug)
                Serial.println(" <-> button1 - short push");
            switch (mode)
            {
            case 3:
                startStopCleaning();
                break;
            case 4:
                if (debug)
                    Serial.print("Saving value ");
                if (debug)
                    Serial.print(tempValue);
                if (debug)
                    Serial.print(" to EEPROM at address ");
                if (debug)
                    Serial.print(varNumber * addressMultiplicator);
                if (debug)
                    Serial.println(", ");
                if (debug)
                    Serial.print("and setting ");
                if (debug)
                    Serial.print(varNames[varNumber]);
                if (debug)
                    Serial.print(" = ");
                if (debug)
                    Serial.println(tempValue);

                putEEPROM(varNumber * addressMultiplicator, tempValue);
                vars[varNumber] = tempValue;

                printSelectedVar();
                break;
            case 5:
                switch (specialMaintMode)
                {
                case 1:
                    printToLCD(0, 2, "Clearing...         ");
                    clearEEPROM();
                    printToLCD(0, 2, "Cleared             ");
                    break;
                case 2:
#ifdef esp01
                    printToLCD(0, 2, "Resetting...        ");
                    esp01HardwareReset();
                    printToLCD(0, 2, "Reset               ");
#endif
                    break;
                case 3:
                    printToLCD(0, 2, "Resetting...        ");
                    resetSystem();
                    printToLCD(0, 2, "Reset               ");
                }
                break;
            }
        }
        button1PushMillis = 0;
        longPush = 0;
        break;
    default:
        if (debug)
            Serial.println();
        break;
    }
}

void longPushButton1()
{
    if (debug)
        Serial.println("button1 long push, switching mode");
    if (debug)
        Serial.println();

    switch (mode)
    {
    case 0:
        stopOutputs();
        mode = 3;
        checkMode(); // check if mode has changed
        break;
    case 3:
        stopOutputs();
        mode = 4;
        checkMode();
        tempValue = vars[varNumber];
        printSelectedVar();
        settingsCheckIfRead();
        break;
    case 4:
        stopOutputs();
        mode = 5;
        checkMode(); // check if mode has changed
        break;
    case 5:
        stopOutputs();
        mode = 0;
        checkMode(); // check if mode has changed
        break;
    }
}