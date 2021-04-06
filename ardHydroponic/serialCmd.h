void doSerialCmd()
{
    switch (serialCmdMode)
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