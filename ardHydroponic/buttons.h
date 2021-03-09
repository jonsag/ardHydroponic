void onPinActivated(int pinNumber)
{
    Serial.print("Pin activated: ");
    Serial.println(pinNumber);

    switch (pinNumber)
    {
    case maintButton:
        Serial.println("maintButton");
        break;
    case cleanpHMinusButton:
        Serial.println("cleanpHMinusButton");
        cleanpHMinus = 1;
        break;
    case cleanpHPlusButton:
        Serial.println("cleanpHMinusButton");
        cleanpHPlus = 1;
        break;
    case cleanNutrAButton:
        Serial.println("cleanNutrAButton");
        cleanNutrA = 1;
        break;
    case cleanNutrBButton:
        Serial.println("cleanNutrBButton");
        cleanNutrB = 1;
        break;
    }
}

void onPinDeactivated(int pinNumber)
{
    Serial.print("Pin deactivated: ");
    Serial.println(pinNumber);
}
