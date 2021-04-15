void doSpecialMaint()
{
    switch (specialMaintMode)
    {
    case 0:
        while (Serial1.available())
        {
            Serial.write(Serial1.read());
        }
        while (Serial.available())
        {
            Serial1.write(Serial.read());
        }
        break;
    }
}

void getIP()
{
    String messageIP;
    i = 0;

    printToLCD(0, 2, "Obtaining IP...     ");
    printToLCD(0, 3, "                    ");

    if (debug)
        Serial.println("Clearing buffer...");

    while (Serial1.available())
    {
        Serial1.read(); // clears buffer
    }

    if (debug)
        Serial.println("Sending an 'i' to esp...");

    Serial1.write("i");

    while (true)
    {
        delay(ESPDelay);

        while (Serial1.available())
        {
            messageIP = Serial1.readString();
        }

        if (debug)
            Serial.print("Got: ");
        if (debug)
            Serial.println(messageIP);

        messageIP.trim();
        if (messageIP.length() > 0)
        {
            break;
        }

        i++;
        if (i > maxTries)
        {
            break;
        }
    }

    messageIP.remove(0, 4);

    if (messageIP.length() > 0)
    {
        if (debug)
            Serial.print("After trimming: ");
        if (debug)
            Serial.println(messageIP);
        if (debug)
            Serial.print("Length: ");
        if (debug)
            Serial.println(messageIP.length());

        if (debug)
            Serial.println("Printing to LCD...");

        printToLCD(0, 2, "IP:                 ");
        printToLCD(0, 3, messageIP);

        for (i = messageIP.length(); i < 20; i++)
        { // fill screen with spaces
            printToLCD(i, 3, " ");
        }
    }
    else
    {
        if (debug)
            Serial.print("Could not get info in ");
        if (debug)
            Serial.print(maxTries);
        if (debug)
            Serial.println(" tries");
                printToLCD(0, 2, "Couldn't get IP     ");
    }
}

void getMAC()
{
    String messageMAC;
    i = 0;

    printToLCD(0, 2, "Obtaining MAC...    ");
    printToLCD(0, 3, "                    ");

    if (debug)
        Serial.println("Clearing buffer...");

    while (Serial1.available())
    {
        Serial1.read(); // clears buffer
    }

    if (debug)
        Serial.println("Sending an 'm' to esp...");

    Serial1.write("m");

    while (true)
    {
        delay(ESPDelay);

        while (Serial1.available())
        {
            messageMAC = Serial1.readString();
        }

        if (debug)
            Serial.print("Got: ");
        if (debug)
            Serial.println(messageMAC);
        
        messageMAC.trim();
        if (messageMAC.length() > 0)
        {
            break;
        }

        i++;
        if (i > maxTries)
        {
            break;
        }
    }
    messageMAC.remove(0, 5);
    if (messageMAC.length() > 0)
    {
        if (debug)
            Serial.print("After trimming: ");
        if (debug)
            Serial.println(messageMAC);

        if (debug)
            Serial.println("Printing to LCD...");

        printToLCD(0, 2, "MAC:                ");
        printToLCD(0, 3, messageMAC);

        for (i = messageMAC.length(); i < 20; i++)
        { // fill screen with spaces
            printToLCD(i, 3, " ");
        }
    }
    else
    {
        if (debug)
            Serial.print("Could not get info in ");
        if (debug)
            Serial.print(maxTries);
        if (debug)
            Serial.println(" tries");
                printToLCD(0, 2, "Couldn't get MAC    ");
    }
}