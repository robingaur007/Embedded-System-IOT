#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
}

void loop()
{
  lcd.setCursor(3, 0);
  lcd.print("First Code");
  delay(3000);
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print("Incubation");
  lcd.setCursor(5, 1);
  lcd.print("Center");
  delay(3000);
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print("IIT Patna");
  delay(3000);
  lcd.clear();

  
}
