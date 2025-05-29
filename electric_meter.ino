#define BLYNK_TEMPLATE_ID "TMPL3TFVQqnYd"
#define BLYNK_TEMPLATE_NAME "Robin123"
#define BLYNK_AUTH_TOKEN "lsanUFzIqaAG9qwrS1PB-wKa5MV6HZPU"  // Your new token

#define BLYNK_PRINT Serial

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "EmonLib.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2); // If 0x27 doesn't work, try 0x3F
EnergyMonitor emon;

#define vCalibration 83.3
#define currCalibration 0.50

BlynkTimer timer;

char ssid[] = "IC_IITP";
char pass[] = "iciitp@9911";

float kWh = 0;
unsigned long lastmillis = millis();
bool toggleDisplay = false;

void myTimerEvent() {
  emon.calcVI(20, 2000);
  kWh += emon.apparentPower * (millis() - lastmillis) / 3600000000.0;
  lastmillis = millis();

  // Serial Output
  Serial.print("Vrms: "); Serial.print(emon.Vrms, 2); Serial.print(" V\t");
  Serial.print("Irms: "); Serial.print(emon.Irms, 4); Serial.print(" A\t");
  Serial.print("Power: "); Serial.print(emon.apparentPower, 4); Serial.print(" W\t");
  Serial.print("kWh: "); Serial.println(kWh, 5);

  // LCD Display
  lcd.clear();
  if (toggleDisplay) {
    lcd.setCursor(0, 0); lcd.print("Vrms:"); lcd.print(emon.Vrms, 2); lcd.print("V");
    lcd.setCursor(0, 1); lcd.print("Irms:"); lcd.print(emon.Irms, 4); lcd.print("A");
  } else {
    lcd.setCursor(0, 0); lcd.print("Power:"); lcd.print(emon.apparentPower, 4); lcd.print("W");
    lcd.setCursor(0, 1); lcd.print("Energy:"); lcd.print(kWh, 4); lcd.print("kWh");
  }
  toggleDisplay = !toggleDisplay;

  // Send data to Blynk
  Blynk.virtualWrite(V0, emon.Vrms);
  Blynk.virtualWrite(V1, emon.Irms);
  Blynk.virtualWrite(V2, emon.apparentPower);
  Blynk.virtualWrite(V3, kWh);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22); // Set I2C SDA and SCL pins for ESP32
  lcd.init();
  lcd.backlight();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  emon.voltage(35, vCalibration, 1.7); // Voltage sensor pin, calibration, phase shift
  emon.current(34, currCalibration);   // Current sensor pin, calibration

  // Splash screen
  lcd.setCursor(3, 0); lcd.print("IoT Energy");
  lcd.setCursor(5, 1); lcd.print("Meter");
  delay(100);
  lcd.clear();

  timer.setInterval(5000L, myTimerEvent); // 5 seconds interval
}

void loop() {
  Blynk.run();
  timer.run();
}
