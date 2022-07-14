/**#include <Arduino.h>
#include <ESP8266WiFi.h>

const char *ssid = "D'House";
const char *password = "ditana220101";
const uint16_t port = 2004;
const char *host = "192.168.1.99";

WiFiClient client;

void connect_wifi()
{
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  delay(250);
}

void connect_server()
{
  while (!client.connect(host, port))
  {
    Serial.printf("\n[Connecting to %s ... ", host);
    delay(1000);
    return;
  }
  Serial.println("connected]");
  delay(1000);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Contoh penggunaan socket client");
  connect_wifi();
  connect_server();
}

void loop()
{
  if (client.connected())
  {
    Serial.print("[Response:]");
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line.equalsIgnoreCase("led-on"))
    {
      pinMode(LED_BUILTIN, HIGH);
      delay(3000);
      pinMode(LED_BUILTIN, LOW);
    }
  }else{
    connect_server();
  }
  delay(250);
}**/

//Tugas
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Time.h>


#define DHTTYPE DHT11
DHT dht(D1, DHTTYPE);
#define RED_LED D4 
#define GREEN_LED D3 
#define BLUE_LED D2 


int zonawaktu = 7 * 3600;   //zona waktu
int dsw = 0;                //date swing

const char *ssid = "D'House"; // nama SSID untuk koneksi Anda
const char *password = "ditana220101"; // password akses point WIFI Anda
const uint16_t port = 2004; // diganti dengan port serve Anda
const char *host = "192.168.1.99";//diganti dengan host server Anda, bisa ip ataupun domain

WiFiClient client;

void connect_wifi()
{
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  delay(250);
}

void connect_server(){

  Serial.printf("\n[Connecting to %s ... ", host);
  while (client.connect(host, port)){
    delay(2000);
    Serial.print(".");
    return;
  }
    Serial.println("connected]");
    delay(1000);
}

void setup(){
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  dht.begin();
  Serial.begin(115200);
  Serial.println("Contoh penggunaan socket client");
  connect_wifi();
  connect_server();

  configTime(zonawaktu, dsw, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for NTP");

  while (!time(nullptr)){
    Serial.print("*");
    delay(2000);
  }
  Serial.println("Time Response OK");
}

void loop (){
  delay(2000);
  time_t now = time(nullptr);
  struct tm * p_tm = localtime(&now);

  float h = dht.readHumidity();
  float c = dht.readTemperature();
  float f = dht.readTemperature(true);

  if(client.connected()){
    Serial.println("[getting request]");
    client.print(String("Temperature = ") + String(c) + String("C | ") + String(f) + String("F | Humidity = ") + String(h) + String("% Time=") + String(p_tm->tm_hour) + String(":") + String(p_tm->tm_min));
    Serial.print("[Response:]");
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line.equalsIgnoreCase("led-on"))
    {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
    }
    else if (line.equalsIgnoreCase("led-off"))
    {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
    }
  }
  else
  {
    connect_server();
  }
  delay(250);
}