void startStopCleaning()
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
            pumpNumber--;
            if (pumpNumber < 0)
            {
                pumpNumber = 3;
            }
            printSelectedPump();
            break;
        }
        break;
    case button3:
        Serial.println(" <-> button3");
        switch (mode)
        {
        case 3:
            pumpNumber++;
            if (pumpNumber > 3)
            {
                pumpNumber = 0;
            }
            printSelectedPump();
            break;
        }
        break;
    case button4:
        Serial.println(" <-> button4");
        switch (mode)
        {
        case 3:
            break;
        }
        break;
    case button5:
        Serial.println(" <-> button5");
        switch (mode)
        {
        case 3:
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
        stopPumps();
        mode = 3;
        checkMode(); // check if mode has changed
        break;
    case 3:
        stopPumps();
        #ifdef eeprom
        mode = 4;
        #else
        mode = 0;
        #endif
        checkMode(); // check if mode has changed
        break;
    case 4:
        stopPumps();
        mode = 0;
        checkMode(); // check if mode has changed
        break;
    }
}