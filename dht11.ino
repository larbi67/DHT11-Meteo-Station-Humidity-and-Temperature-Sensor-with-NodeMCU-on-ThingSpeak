#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
 
const char *ssid =  "SSID";  
const char *pass =  "WIFI Pass";
 
 
DHT dht(D4, DHT11);
 
WiFiClient client;
 
long myChannelNumber = xxxxxxxxxx;
const char myWriteAPIKey[] = "xxxxxxxxxx";
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(2000);
}
