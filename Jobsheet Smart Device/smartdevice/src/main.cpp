#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SimpleDHT.h>

// hp
// const char *ssid = "od3ng";
// const char *password = "0d3n9bro";

// kampus
const char *ssid = "D'House";            // sesuaikan dengan username wifi
const char *password = "ditana220101";        // sesuaikan dengan password wifi
const char *mqtt_server = "broker.hivemq.com"; // isikan server broker

WiFiClient espClient;
PubSubClient client(espClient);

const int lamp = 5;
SimpleDHT11 dht11(D7);

long now = millis();
long lastMeasure = 0;
String macAddr = "";

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
  macAddr = WiFi.macAddress();
  Serial.println(macAddr);
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(macAddr.c_str()))
    {
      Serial.println("connected");
      client.subscribe("1941720058/room/lamp");
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

void callback(String topic, byte *message, unsigned int length){
Serial.print("Pesan yang diterima pada topic: ");
Serial.print(topic);
String messageTemp;

 for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (topic == "1941720058/room/lamp")
  {
    Serial.print("Kondisi Lampu ");
    if (messageTemp == "on")
    {
      digitalWrite(lamp, HIGH);
      Serial.print("Nyala");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(lamp, LOW);
      Serial.print("Mati");
    }
  }
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Mqtt Node-RED");
  setup_wifi();
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
    client.connect(macAddr.c_str());
  }
  now = millis();
  if (now - lastMeasure > 5000)
  {
    lastMeasure = now;
    int err = SimpleDHTErrSuccess;

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

    dtostrf(humidity, 4, 2, humidityHum);
    dtostrf(temperature, 4, 2, temperatureTemp);
    Serial.print("Temperature: ");
    Serial.println(temperatureTemp);
    Serial.print("Humidity: ");
    Serial.println(humidityHum);

    client.publish("1941720058/room/humidity", humidityHum);
    client.publish("1941720058/room/suhu", temperatureTemp); // agar lebih unix silakan tambahkan NIM ex: 0001/room/suhu
  }
}