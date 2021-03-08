void onPinActivated(int pinNumber)
{
    Serial.print("Pin activated: ");
    Serial.println(pinNumber);

    switch (pinNumber)
    {
    case maintButton:
        Serial.println("maintButton");
        break;
    case cleanPhMinusButton:
        Serial.println("cleanPhMinusButton");
        cleanPhMinus = 1;
        break;
    case cleanPhPlusButton:
        Serial.println("cleanPhMinusButton");
        cleanPhPlus = 1;
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
