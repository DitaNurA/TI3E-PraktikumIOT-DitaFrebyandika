#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SimpleDHT.h>

const char *ssid = "D'House";     // silakan disesuaikan sendiri
const char *password = "ditana220101"; // silakan disesuaikan sendiri
const char *mqtt_server = "broker.hivemq.com";


#define RED_LED D1   
#define GREEN_LED D2 
#define BLUE_LED D3  
#define sensorLDR A0
int sensor;

WiFiClient espClient;
PubSubClient client(espClient);

SimpleDHT11 dht11(D7);

long now = millis();
long lastMeasure = 0;
String macAddress = "";

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
  macAddress = WiFi.macAddress();
  Serial.print(WiFi.macAddress());
}

void ledOff()
{
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void ledRedOn()
{
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void ledGreenOn()
{
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
}

void ledBlueOn()
{
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
}


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message [");
  Serial.print(topic);
  Serial.print("] ");
  String messageTemp;
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }

  Serial.println();

  // Filter by topic
  if (String(topic) == "1941720058/room/lamp-red")
  {
    if (messageTemp == "On")
    {
      Serial.println("Nyala");
      ledRedOn();
    }
    else
    {
      Serial.println("Mati");
      ledOff();
    }
  }
  else if (String(topic) == "1941720058/room/lamp-green")
  {
    if (messageTemp == "On")
    {
      Serial.println("Nyala");
      ledGreenOn();
    }
    else
    {
      Serial.println("Mati");
      ledOff();
    }
  }
  else if (String(topic) == "1941720058/room/lamp-blue")
  {
    if (messageTemp == "On")
    {
      Serial.println("Nyala");
      ledBlueOn();
    }
    else
    {
      Serial.println("Mati");
      ledOff();
    }
  }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(macAddress.c_str()))
    {
      Serial.println("Connected.");
      // Subscribe agar listen ke noderednya
      Serial.println(client.subscribe("1941720058/room/lamp-red"));
      Serial.println(client.subscribe("1941720058/room/lamp-green"));
      Serial.println(client.subscribe("1941720058/room/lamp-blue"));
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Mqtt Node-RED");
  setup_wifi();
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
  {
    client.connect("ESP8266Client");
  }

  now = millis();
  if (now - lastMeasure > 5000)
  {
    lastMeasure = now;
    int err = SimpleDHTErrSuccess;

    sensor = analogRead(sensorLDR);
    byte temperature = 0;
    byte humidity = 0;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
    {
      Serial.print("Pembacaan DHT11 gagal, err=");
      Serial.println(err);
      delay(1000);
      return;
    }
    static char temperatureTemp[7];
    static char humidityHum[7];
    static char light[8];

    dtostrf(humidity, 1, 2, humidityHum);
    dtostrf(temperature, 4, 2, temperatureTemp);
    dtostrf(sensor, 4, 2, light);

    Serial.println(temperatureTemp);
    Serial.println(humidityHum);
    Serial.println(light);

    client.publish("1941720058/room/humidity", humidityHum);
    client.publish("1941720058/room/suhu", temperatureTemp);
    client.publish("1941720058/room/ldr", light);
  }
}