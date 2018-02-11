#include <dht.h>
#include <ESP8266WiFi.h>
#include <MQTTClient.h>
 
 
const char* ssid     = "Priyam";
const char* password = "priyam12345";
 
WiFiClient WiFiclient;
MQTTClient client;
dht DHT;

unsigned long lastMillis = 0;

 
void setup() {
  pinMode(5, OUTPUT);
 Serial.begin(115200);
 delay(10);
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 
 Serial.println("");
 Serial.println("WiFi connected");  
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 delay(2000);
 
 Serial.print("connecting to MQTT broker...");
 client.begin("bitvolt.tk", WiFiclient);
 connect();
 client.onMessage(messageReceived);
}
 
void connect() {
 while (!client.connect("nodemcu 1", "priyam", "priyam")) {
   Serial.print(".");
 }
 
 Serial.println("\nconnected!");
 client.subscribe("/priyam/light");
}
 
void loop() {
 int chk = DHT.read11(16);
 double temp = DHT.temperature;
 double humidity = DHT.humidity;

 
 client.loop();
 if(!client.connected())
 {
   connect();
 }
 
if(millis() - lastMillis > 3000)
{
   lastMillis = millis();
   client.publish("/priyam/temp", (String)temp);
  Serial.println(temp);
   client.publish("/priyam/humidity", (String)humidity);
   Serial.println(humidity);
 }
   
   
   
 
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if(payload=="0")
  digitalWrite(5,LOW);
  else
  digitalWrite(5,HIGH);
}
