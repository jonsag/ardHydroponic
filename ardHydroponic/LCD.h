void printToLCD(int col, int row, String text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
}
