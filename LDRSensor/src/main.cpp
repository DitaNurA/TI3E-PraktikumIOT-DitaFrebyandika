//sensor ldr
/**#include <Arduino.h>
 #define sensorLDR A0
 int nilaiSensor;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println("Contoh Penggunaan Sensor LDR");
delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
nilaiSensor = analogRead(sensorLDR);
Serial.print("Nilai Sensor :");
Serial.println(nilaiSensor);
delay(1000);
}**/

// sensor HC-SR dan tugas 2
#include <Arduino.h>
#define triggerPin D6
#define echoPin D5
#define RED_LED D1 
#define GREEN_LED D2
#define BLUE_LED D3


void setup() {
   Serial.begin (115200);
   pinMode(triggerPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(RED_LED, OUTPUT);
   pinMode(GREEN_LED, OUTPUT);
   pinMode(BLUE_LED, OUTPUT);
   //pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
   long duration, jarak;
   digitalWrite(triggerPin, LOW);
   delayMicroseconds(2);
   digitalWrite(triggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(triggerPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   jarak = duration * 0.034 / 2;
   Serial.print(jarak);
   Serial.println(" cm");
   delay(2000);

   if (jarak <= 1){
    Serial.println("Jarak Benda ada pada 1cm");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }

  if (2<= jarak && jarak < 3){
    Serial.println("Jarak Benda ada pada 2cm");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
  }

  if (3 <= jarak && jarak < 4){
    Serial.println("Jarak Benda ada pada 3cm");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }

  if (jarak > 3){
    Serial.println("Jarak Benda Lebih dari 3cm");
    digitalWrite(RED_LED,HIGH);
    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(BLUE_LED,HIGH);
    delay(2000);
  }
}
/**
//Tugas 1
#include <Arduino.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define RED_LED D2
#define GREEN_LED D3
#define BLUE_LED D4

DHT dht(D5, DHTTYPE);

void setup(){
  dht.begin();
  Serial.begin(115200);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.println("Penerapan Sensor LDR dan DHT11");
  delay(2000);
}

void loop(){
  int sensorLDR = analogRead(A0);
Serial.print("Nilai Sensor :");
Serial.println(sensorLDR);
delay(1000);

float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f))
{
  Serial.println("Failed to read from DHT sensor!");
  return;
}

float hif = dht.computeHeatIndex(f, h);
float hic = dht.computeHeatIndex(t, h, false);

Serial.print(F("Humidity: "));
Serial.print(h);
Serial.print(F("%  Temperature: "));
Serial.print(t);
Serial.print(F("°C "));

if (t <= 30 && sensorLDR <= 20){
  Serial.println("Suhu saat ini Dingin dan Cahaya Tidak Terang");
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
  delay(2000);
}

if (t>= 29 && sensorLDR >= 15){
  Serial.println("Suhu saat ini Tinggi dan Cahaya Terang");
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(2000);
}
}**/

//Tugas 2
