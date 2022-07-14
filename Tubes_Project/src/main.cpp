#define BLYNK_PRINT Serial
#define BLYNK_AUTH_TOKEN "gAQ3fwjkUPNM9W06WYLw4JFKC1cgpATb"
#define BLYNK_TEMPLATE_ID "TMPL6NxNGg_9"
#define BLYNK_DEVICE_NAME "Weather Monitoring System"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

DHT dht(D3, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN; //Enter the Auth code which was send by Blink
char ssid[] = "D'House";  //Enter your WIFI Name
char pass[] = "ditana220101";  //Enter your WIFI Password

void weather() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int r = analogRead(A0);


  r = map(r, 0, 1023, 100, 0);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);  //V0 is for Temperature
  Blynk.virtualWrite(V1, h);  //V1 is for Humidity
  Blynk.virtualWrite(V2, r);  //V2 is for Rainfall
}

void setup() {
  Serial.begin(115200); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(10L, weather);
}

void loop() {
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
  
}