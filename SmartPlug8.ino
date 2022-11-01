#include "Adafruit_MCP23X17.h"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define Relay8 4
#define Relay7 5
#define Relay6 6
#define Relay5 7
#define Relay4 11
#define Relay3 10
#define Relay2 8
#define Relay1 9

const char* ssid = "ssid";
const char* password = "password";
const char *mqtt_broker = "broker";
const int mqtt_port = 1883;

String messageValue;

WiFiClient espClient;
PubSubClient client(espClient);

Adafruit_MCP23X17 mcp;

void reconnect(){
  while (!client.connected()) {
      String client_id = "SmartPlug";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
          Serial.println("Mqtt broker connected");
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
  mcp.begin_I2C(0x20);
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "Reef Smart Plug";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
          Serial.println("HA mqtt broker connected");
          client.publish ("vehan/test/internet", "Everything is connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
  client.subscribe("vehan/aquarium1/relay1");
  client.subscribe("vehan/aquarium1/relay2");
  client.subscribe("vehan/aquarium1/relay3");
  client.subscribe("vehan/aquarium1/relay4");
  client.subscribe("vehan/aquarium1/relay5");
  client.subscribe("vehan/aquarium1/relay6");
  client.subscribe("vehan/aquarium1/relay7");
  client.subscribe("vehan/aquarium1/relay8");
  
  mcp.pinMode(Relay1, OUTPUT);
  mcp.pinMode(Relay2, OUTPUT);
  mcp.pinMode(Relay3, OUTPUT);
  mcp.pinMode(Relay4, OUTPUT);
  mcp.pinMode(Relay5, OUTPUT);
  mcp.pinMode(Relay6, OUTPUT);
  mcp.pinMode(Relay7, OUTPUT);
  mcp.pinMode(Relay8, OUTPUT);

  mcp.digitalWrite(Relay1, HIGH);
  mcp.digitalWrite(Relay2, HIGH);
  mcp.digitalWrite(Relay3, HIGH);
  mcp.digitalWrite(Relay4, HIGH);
  mcp.digitalWrite(Relay5, HIGH);
  mcp.digitalWrite(Relay6, HIGH);
  mcp.digitalWrite(Relay7, HIGH);
  mcp.digitalWrite(Relay8, HIGH);
}

void loop() {
  client.loop();
  reconnect();
}

void callback(char *topic, byte *payload, unsigned int length) {
  if (strcmp(topic,"vehan/aquarium1/relay1")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '0')
        mcp.digitalWrite(Relay1, HIGH);
    else if (messageValue == '1')
        mcp.digitalWrite(Relay1, LOW);
    else
        mcp.digitalWrite(Relay1, HIGH);
   }
  Serial.println();
  }
    if (strcmp(topic,"vehan/aquarium1/relay2")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '0')
        mcp.digitalWrite(Relay2, HIGH);
    else if (messageValue == '1')
        mcp.digitalWrite(Relay2, LOW);
    else
        mcp.digitalWrite(Relay2, HIGH);
   }
  Serial.println();
  }

      if (strcmp(topic,"vehan/aquarium1/relay3")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '0')
        mcp.digitalWrite(Relay3, HIGH);
    else if (messageValue == '1')
        mcp.digitalWrite(Relay3, LOW);
    else
        mcp.digitalWrite(Relay3, HIGH);
   }
  Serial.println();
  }

      if (strcmp(topic,"vehan/aquarium1/relay4")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '0')
        mcp.digitalWrite(Relay4, HIGH);
    else if (messageValue == '1')
        mcp.digitalWrite(Relay4, LOW);
    else
        mcp.digitalWrite(Relay4, HIGH);
   }
  Serial.println();
  }

      if (strcmp(topic,"vehan/aquarium1/relay5")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '0')
        mcp.digitalWrite(Relay5, HIGH);
    else if (messageValue == '1')
        mcp.digitalWrite(Relay5, LOW);
    else
        mcp.digitalWrite(Relay5, HIGH);
   }
  Serial.println();
  }

      if (strcmp(topic,"vehan/aquarium1/relay6")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '0')
        mcp.digitalWrite(Relay6, HIGH);
    else if (messageValue == '1')
        mcp.digitalWrite(Relay6, LOW);
    else
        mcp.digitalWrite(Relay6, HIGH);
   }
  Serial.println();
  }

      if (strcmp(topic,"vehan/aquarium1/relay7")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '0')
        mcp.digitalWrite(Relay7, HIGH);
    else if (messageValue == '1')
        mcp.digitalWrite(Relay7, LOW);
    else
        mcp.digitalWrite(Relay7, HIGH);
   }
  Serial.println();
  }

      if (strcmp(topic,"vehan/aquarium1/relay8")==0){
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
    for (int i=0;i<length;i++) {
        char messageValue = (char)payload[i];
        Serial.print(messageValue);
    if (messageValue == '0')
        mcp.digitalWrite(Relay8, HIGH);
    else if (messageValue == '1')
        mcp.digitalWrite(Relay8, LOW);
    else
        mcp.digitalWrite(Relay8, HIGH);
   }
  Serial.println();
  }
}
