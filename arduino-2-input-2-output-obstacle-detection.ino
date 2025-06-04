#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Pins
const int irSensorPin = 7;
const int lightSensorPin = A0;
const int whiteLED = 9;
const int blueLED = 8;
const int dhtPin = 2;

// DHT Settings
#define DHTTYPE DHT11  
DHT dht(dhtPin, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(whiteLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  dht.begin();  
}

void loop() {
  int irState = digitalRead(irSensorPin);
  int lightLevel = analogRead(lightSensorPin);
  float humidity = dht.readHumidity();

  lcd.clear();
  lcd.setCursor(0, 0);

  if (irState == LOW) {
    // Obstacle detected
    digitalWrite(whiteLED, LOW);
    digitalWrite(blueLED, HIGH);

    lcd.print("Obstacle!");
    lcd.setCursor(0, 1);
    lcd.print("Blocked");
  } else {
    // No obstacle
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, LOW);

    lcd.print("Hum: ");
    lcd.print(humidity, 0); 
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Light:");
    lcd.print(lightLevel);
  }

  delay(2000);  
