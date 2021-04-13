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
    String message;

    if (debug)
        Serial.println("Sending an 'i' to esp...");

    Serial1.write("i");

    if (debug)
        Serial.println("Reading answer...");

    while (Serial1.available())
    {
        message = Serial1.readString();
    }
    if (debug)
        Serial.print("Got: ");
    if (debug)
        Serial.println(message);

    message.trim();
    message.remove(0, 4);

    if (debug)
        Serial.print("After trimming: ");
    if (debug)
        Serial.println(message);

    if (debug)
        Serial.println("Printing to LCD...");

    printToLCD(0, 2, "IP: ");
    printToLCD(4, 2, message);

    for (i = message.length() + 4; i < 20; i++)
    { // fill screen with spaces
        printToLCD(i, 2, " ");
    }
}