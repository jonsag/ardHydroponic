void onPinActivated(int pinNumber)
{
    Serial.print("Pin activated: ");
    Serial.println(pinNumber);

    switch (pinNumber)
    {
    case maintButton:
        Serial.println("maintButton");
        stopPumps();
        mode = 3;
        checkMode(); // check if mode has changed
        maintStartMillis = currentMillis;
        break;
    case cleanpHPlusButton:
        Serial.println("cleanpHPlusButton");
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
    case cleanpHMinusButton:
        Serial.println("cleanpHMinusButton");
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
    case cleanNutrAButton:
        Serial.println("cleanNutrAButton");
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
    case cleanNutrBButton:
        Serial.println("cleanNutrBButton");
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
    Serial.println(pinNumber);

    switch (pinNumber)
    {
    case maintButton:
        stopPumps();
        mode = 0;
        checkMode(); // check if mode has changed
        break;
    };
}
