void onPinActivated(int pinNumber)
{
    Serial.print("Pin activated: ");
    Serial.print(pinNumber);

    switch (pinNumber)
    {
    case button1:
        Serial.println(" <-> button1");
        button1PressMillis = currentMillis;
        break;
    case button2:
        Serial.println(" <-> button2");
        if (mode == 3)
        {
            if (digitalRead(pHPlusPump))
            {
                stoppHPlus();
            }
            else
            {
                startpHPlus();
                pHPlusStartMillis = currentMillis;
            }
        }
        break;
    case button3:
        Serial.println(" <-> button3");
        if (mode == 3)
        {
            if (digitalRead(pHMinusPump))
            {
                stoppHMinus();
            }
            else
            {
                startpHMinus();
                pHMinusStartMillis = currentMillis;
            }
        }
        break;
    case button4:
        Serial.println(" <-> button4");
        if (mode == 3)
        {
            if (digitalRead(nutrAPump))
            {
                stopNutrA();
            }
            else
            {
                startNutrA();
                nutrAStartMillis = currentMillis;
            }
        }
        break;
    case button5:
        Serial.println(" <-> button5");
        if (mode == 3)
        {
            if (digitalRead(nutrBPump))
            {
                stopNutrB();
            }
            else
            {
                startNutrB();
                nutrBStartMillis = currentMillis;
            }
        }
        break;
    }
}

void onPinDeactivated(int pinNumber)
{
    Serial.print("Pin deactivated: ");
    Serial.print(pinNumber);

    switch (pinNumber)
    {
    case button1:
        if (currentMillis - button1PressMillis >= longPressTime)
        { // long press
        Serial.println(" <-> button1 - long press");
            if (mode == 0)
            {
                stopPumps();
                mode = 3;
                checkMode(); // check if mode has changed
                break;
            }
            else if (mode == 3)
            {
                stopPumps();
                mode = 4;
                checkMode(); // check if mode has changed
                break;
            }
            else if (mode == 4)
            {
                stopPumps();
                mode = 0;
                checkMode(); // check if mode has changed
            }
        } else {
        Serial.println(" <-> button1");
        }
        break;
    }
}
