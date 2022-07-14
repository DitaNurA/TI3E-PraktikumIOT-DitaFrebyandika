 /**#include <Arduino.h>
    #include <SimpleDHT.h>

    #define pinDHT 7 // SD3 pin signal sensor DHT

    byte temperature = 0;
    byte humidity = 0;

    SimpleDHT11 dht11(D7); //instan sensor dht11

    void KelembabanSuhu()
    {
        int err = SimpleDHTErrSuccess;

        if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
        {
            Serial.print("Pembacaan DHT11 gagal, err=");
            Serial.println(err);
            delay(1000);
            return;
        }

        Serial.print("Sample OK: ");
        Serial.print((int)temperature);

        Serial.print(" *C, ");
        Serial.print((int)humidity);
        Serial.println(" H");

        delay(1500);
    }

    void setup()
    {
        Serial.begin(115200);
        Serial.println("Simple DHT");
        delay(1000);
    }

    void loop()
    {
        KelembabanSuhu();
    }**/

/**#include <Arduino.h>
#include <DHT.h>

#define DHTTYPE DHT11

DHT dht(D7, DHTTYPE);

void setup() {
  Serial.begin(115200);
Serial.println("Menggunakan DHT11");
}

void loop() {
  delay(2000);
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
Serial.print(t+273.15);
Serial.print(F("°K "));
Serial.print((4*t)/5);
Serial.print(F("°R "));
Serial.print(f);
Serial.print(F("°F  Heat index: "));
Serial.print(hic);
Serial.print(F("°C "));
Serial.print(hif);
Serial.println(F("°F"));

}**/


#include <Arduino.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define RED_LED D3 //suhu panas
#define GREEN_LED D2 //suhu normal
#define BLUE_LED D5 //suhu dingin


DHT dht(D1, DHTTYPE);
void setup() {
dht.begin();
Serial.begin(115200);
pinMode(RED_LED, OUTPUT);
pinMode(GREEN_LED, OUTPUT);
pinMode(BLUE_LED, OUTPUT);
Serial.println("Menggunakan DHT11");
}

void loop() {
pinMode(RED_LED, OUTPUT);
pinMode(GREEN_LED, OUTPUT);
pinMode(BLUE_LED, OUTPUT);
delay(2000);

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
Serial.print(t+273.15);
Serial.print(F("°K "));
Serial.print((4*t)/5);
Serial.print(F("°R "));
Serial.print(f);
Serial.print(F("°F  Heat index: "));
Serial.print(hic);
Serial.print(F("°C "));
Serial.print(hif);
Serial.println(F("°F"));

if (t <= 29){
  Serial.println("Suhu saat ini Dingin");
  digitalWrite(BLUE_LED, HIGH);
}

if (29 <= t && t <= 30){
  Serial.println("Suhu saat ini Normal");
  digitalWrite(GREEN_LED, HIGH);
  delay(2000);
}

if (t >= 29){
  Serial.println("Suhu saat ini Panas");
  digitalWrite(RED_LED, HIGH);
}

}