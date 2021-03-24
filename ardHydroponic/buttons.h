void startStopCleaning()
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
    case 4: // stirrer
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
    case 0:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 1:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 2:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 3:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 4:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 5:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 6:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 7: // pH low
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        else if (tempValue >= vars[8])
        {
            Serial.println("Can't increase more. Conflicting with pH high");
            tempValue -= incs[7];
        }
        break;
    case 8: //pH high
        if (tempValue <= vars[7])
        {
            Serial.println("Can't decrease more. Conflicting with pH low");
            tempValue += incs[8];
        }
        else if (tempValue >= 15)
        {
            Serial.println("Can't increase more. Not sane value");
            tempValue = 15 - incs[8];
        }
        break;
    case 9:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 10:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    case 11:
        if (tempValue < 0)
        {
            Serial.println("Can't decrease more");
            tempValue = 0;
        }
        break;
    }
}

void onPinActivated(int pinNumber)
{
    Serial.println();
    Serial.print("Pin activated: ");
    Serial.print(pinNumber);

    switch (pinNumber)
    { // outer switch start
    case button1:
        Serial.println(" <-> button1");
        button1PushMillis = currentMillis;
        break;
    case button2:
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
            printSelectedVar();
            break;
        }
        break;
    case button3:
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
            printSelectedVar();
            break;
        }
        break;
    case button4:
        Serial.println(" <-> button4");
        switch (mode)
        {
        case 4:
            tempValue -= incs[varNumber];
            checkSanity();
            printSelectedVar();
            break;
        }
        break;
    case button5:
        Serial.println(" <-> button5");
        switch (mode)
        {
        case 4:
            tempValue += incs[varNumber];
            checkSanity();
            printSelectedVar();
            break;
        }
        break;
    } // outer switch stop
}

void onPinDeactivated(int pinNumber)
{
    Serial.println();
    Serial.print("Pin deactivated: ");
    Serial.print(pinNumber);

    switch (pinNumber)
    {
    case button1:
        if (longPush)
        {
            Serial.println(" <-> button1 - was a long push");
        }
        else
        {
            Serial.println(" <-> button1 - short push");
            switch (mode)
            {
            case 3:
                startStopCleaning();
                break;
            case 4:
                Serial.print("Saving value ");
                Serial.print(tempValue);
                Serial.print(" to EEPROM at address ");
                Serial.print(varNumber * addressMultiplicator);
                Serial.println(", ");
                Serial.print("and setting ");
                Serial.print(varNames[varNumber]);
                Serial.print(" = ");
                Serial.println(tempValue);

                putEEPROM(varNumber * addressMultiplicator, tempValue);
                vars[varNumber] = tempValue;
            }
        }
        button1PushMillis = 0;
        longPush = 0;
        break;
    default:
        Serial.println();
        break;
    }
}

void longPushButton1()
{
    Serial.println("button1 long push, switching mode");
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
        break;
    case 4:
        stopOutputs();
        mode = 0;
        checkMode(); // check if mode has changed
        break;
    }
}