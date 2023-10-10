#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define IR_INPUT_PIN A0
#define IR_LED_PIN 2

void setup() {
  Serial.begin(9600);
  servo.attach(4);
  servo.write(0);
  sensors.begin();
  lcd.begin();
  lcd.backlight();
  pinMode(IR_INPUT_PIN, INPUT);
  pinMode(IR_LED_PIN, OUTPUT);
}


void loop() {
  int ambient = 0;
  int lit = 0;
  int value = 0;
  int distance = 0;
  int x = 0;

  sensors.requestTemperatures();
  digitalWrite(IR_LED_PIN, LOW);
  delay(5);                            //To give ADC and LED transition time
  ambient = analogRead(IR_INPUT_PIN);

  digitalWrite(IR_LED_PIN, HIGH);
  delay(5);
  lit = analogRead(IR_INPUT_PIN);

  value = lit - ambient;
  distance =  9000 / (value - 12);
  x = distance - 120;
  Serial.println(distance);
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Temp.: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" *C");
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("Range: ");
  lcd.print(distance);
  lcd.print(" cm");

}