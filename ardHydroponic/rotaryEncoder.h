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