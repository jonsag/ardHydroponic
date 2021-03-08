int intLength(int value) {
  int length;

  if (value > 9999)
    length = 5;
  else if (value > 999)
    length = 4;
  else if (value > 99)
    length = 3;
  else if (value > 9)
    length = 2;
  else
    length = 1;

  return length;
}

int intToStringToLength(int val) { // returns how many numbers in integer
  valString = String(val); // convert to string
  valLength = valString.length(); // count number of characters in string

  return valLength;
}

/*
dtostrf(floatvar, StringLengthIncDecimalPoint, numVarsAfterDecimal, charbuf);
where
floatvar	float variable
StringLengthIncDecimalPoint	This is the length of the string that will be created
numVarsAfterDecimal	The number of digits after the deimal point to print
charbuf	the array to store the results

char dtostrfbuffer[5];
dtostrf(temp, 1, 1, dtostrfbuffer)
valLength = valLength + strlen(dtostrfbuffer);
*/