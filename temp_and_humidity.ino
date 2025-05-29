#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// #include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define the DHT sensor type and pin
#define DHTPIN 15      // Pin connected to the DHT11 data pin
#define DHTTYPE DHT11  // DHT 11

// // Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// // Initialize LCD display (Set I2C address: usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address 0x27, 16 chars, 2 lines

void setup() {
  Serial.begin(9600);  // Start serial communication
  dht.begin();         // Initialize the DHT sensor
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on the LCD backlight

  lcd.setCursor(0, 0);  // Set cursor to first row, first column
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();  // Clear the LCD
}

void loop() {
  // Wait 2 seconds between readings
  delay(1000);

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  // Default: Celsius

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Display readings on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  // Print readings to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}

