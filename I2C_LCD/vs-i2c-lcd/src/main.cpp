#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#include <TimeLib.h>

#define DHTTYPE DHT11
#define RED_LED D6
#define GREEN_LED D5
#define BLUE_LED D4

byte derajat_suhu = B11011111;
time_t t = now();
DHT dht(D3, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  dht.begin();
  Serial.begin(115200);
  setTime(t);
  setTime(7, 50, 00, 13, 7, 22);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.println("Menggunakan DHT11");
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
}

void scrollText(int row, String message, int delayTime, int lcdColumns){
   for (int i = 0; i < lcdColumns; i++)
   {
     message = " " + message;
   }
   message = message + " ";
   for (int pos = 0; pos < message.length(); pos++)
   {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
   }
 }

void printdatanol(int data){
  if (data >= 0 && data < 10){
    lcd.write('0');
  }
  lcd.print(data);
}

void loop(){
delay(2000);

float t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(t) || isnan(f))
{
  Serial.println("Failed to read from DHT sensor!");
  return;
}

Serial.print(F("%  Temperature: "));
Serial.print(t);
Serial.print(F("°C "));
Serial.print(f);
Serial.print(F("°F "));
Serial.print(F(" "));

lcd.clear();
lcd.setCursor(0, 0);
lcd.print(t);
lcd.write(derajat_suhu);
lcd.print(F("C "));
lcd.print(f);
lcd.write(derajat_suhu);
lcd.print(F("F "));

if (t <= 28)
    {
        Serial.println("Suhu Saat Ini Dingin!");
        digitalWrite(BLUE_LED, HIGH);
        delay(1000);
        digitalWrite(BLUE_LED, LOW);
        delay(100);
    }
    if (28 < t && t <= 30)
    {
        Serial.println("Suhu Saat Ini Normal!");
        digitalWrite(GREEN_LED, HIGH);
        delay(1000);
        digitalWrite(GREEN_LED, LOW);
        delay(100);
    }
    if (t > 30)
    {
        Serial.println("Suhu Saat Ini Panas!");
        digitalWrite(RED_LED, HIGH);
        delay(1000);
        digitalWrite(RED_LED, LOW);
        delay(100);
    }

    lcd.setCursor(0, 1);
    printdatanol(day());
    lcd.print("-");
    printdatanol(month());
    lcd.print("-");
    printdatanol(year());
    lcd.print(" ");
    printdatanol(hour());
    lcd.print(":");
    printdatanol(minute());
}
/**
//Praktikum
void setup() {
  // put your setup code here, to run once:
   lcd.init(); // initialize the lcd
   lcd.backlight();
   lcd.clear();
   lcd.home();
}

void scrollText(int row, String message, int delayTime, int lcdColumns)
 {
   for (int i = 0; i < lcdColumns; i++)
   {
     message = " " + message;
   }
   message = message + " ";
   for (int pos = 0; pos < message.length(); pos++)
   {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
   }
 }

void loop() {
  // put your main code here, to run repeatedly:
   lcd.home();
   lcd.print("Polinema");
   scrollText(1, "Kelas IOT", 250, 16);
}**/