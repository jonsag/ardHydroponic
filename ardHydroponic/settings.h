float storedValueToReal(int i, float value)
{
    switch (i)
    {
    case 0:
        return value * 100;
        break;
    case 1:
        return value * 100;
        break;
    case 2:
        return value * 100;
        break;
    case 3:
        return value * 1000;
        break;
    case 4:
        return value * 1000;
        break;
    case 5:
        return value / 100 + 3;
        break;
    case 6:
        return value / 100 + 3;
        break;
    case 7:
        return value / 10;
        break;
    }
}

float realValueToStored(int i, float value)
{
    switch (i)
    {
    case 0:
        return value / 100;
        break;
    case 1:
        return value / 100;
        break;
    case 2:
        return value / 100;
        break;
    case 3:
        return value / 1000;
        break;
    case 4:
        return value / 1000;
        break;
    case 5:
        return value * 100 - 300;
        break;
    case 6:
        return value * 100 - 300;
        break;
    case 7:
        return value * 10;
        break;
    }
}

void printSelectedVariable() {
    
}

void printKValue() {
    
    Serial.print("");
}