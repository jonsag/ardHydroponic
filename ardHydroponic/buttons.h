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
        }
        break;
    case button3:
        Serial.println(" <-> button3");
        switch (mode)
        {
        case 3:
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
        }
        break;
    case button4:
        Serial.println(" <-> button4");
        switch (mode)
        {
        case 3:
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
        }
        break;
    case button5:
        Serial.println(" <-> button5");
        switch (mode)
        {
        case 3:
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
            button1PushMillis = 0;
            longPush = 0;
            Serial.println(" <-> button1 - short push");
        }
    default:
        Serial.println();
        break;
    }
}

void longPushButton1()
{
    Serial.println("button1 long push, switching mode");
    switch (mode)
    {
    case 0:
        stopPumps();
        mode = 3;
        checkMode(); // check if mode has changed
        break;
    case 3:
        stopPumps();
        mode = 4;
        checkMode(); // check if mode has changed
        break;
    case 4:
        stopPumps();
        mode = 0;
        checkMode(); // check if mode has changed
        break;
    }
}