#include "Adafruit_MCP23X17.h"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define Relay8 7
#define Relay7 6
#define Relay6 5
#define Relay5 4
#define Relay4 3
#define Relay3 2
#define Relay2 1
#define Relay1 0

const char* ssid = "ssid";
const char* password = "password";
const char *mqtt_broker = "MQTT Broker";
const int mqtt_port = 1883;

String messageValue;

WiFiClient espClient;
PubSubClient client(espClient);

Adafruit_MCP23X17 mcp;

void reconnect(){
  while (!client.connected()) {
      String client_id = "ReefMCU SmartPlug8";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
          Serial.println("MQTT broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
      }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Wire.begin(2,0);
  mcp.begin_I2C(0x27); //might be 0x20
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "ReefMCU SmartPlug8";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
          Serial.println("MQTT broker connected");
          client.publish ("test/internet", "Everything is connected"); //not necessary at all, I was just struggling with a broken ESP-01
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
  client.subscribe("aquarium1/relay1");
  client.subscribe("aquarium1/relay2");
  client.subscribe("aquarium1/relay3");
  client.subscribe("aquarium1/relay4");
  client.subscribe("aquarium1/relay5");
  client.subscribe("aquarium1/relay6");
  client.subscribe("aquarium1/relay7");
  client.subscribe("aquarium1/relay8");
  
  mcp.pinMode(Relay1, OUTPUT);
  mcp.pinMode(Relay2, OUTPUT);
  mcp.pinMode(Relay3, OUTPUT);
  mcp.pinMode(Relay4, OUTPUT);
  mcp.pinMode(Relay5, OUTPUT);
  mcp.pinMode(Relay6, OUTPUT);
  mcp.pinMode(Relay7, OUTPUT);
  mcp.pinMode(Relay8, OUTPUT);
}

void loop() {
  client.loop();
  reconnect();
}

void callback(char *topic, byte *payload, unsigned int length) {
  if (strcmp(topic,"aquarium1/relay1")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '1')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '0')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
  if (strcmp(topic,"aquarium1/relay2")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '1')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '0')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
    if (strcmp(topic,"aquarium1/relay3")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '1')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '0')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
    if (strcmp(topic,"aquarium1/relay4")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '1')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '0')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
    if (strcmp(topic,"aquarium1/relay5")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '1')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '0')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
    if (strcmp(topic,"aquarium1/relay6")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '1')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '0')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
    if (strcmp(topic,"aquarium1/relay7")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '1')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '0')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
    if (strcmp(topic,"aquarium1/relay8")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '1')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '0')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
}
