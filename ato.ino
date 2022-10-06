//A lot of redundant code in here. Needs work.

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>

#define RelayPin 14

const char* ssid = "ssid";
const char* password = "password";
const char *mqtt_broker = "MQTT Broker";
const int mqtt_port = 1883;

String messageValue;
String resevoirlevel;

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

int Water_level=0;
int FloatSwitch=1;
int OldPump = 1;

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    resevoirlevel += (char)message[i];
  }
  Serial.println();
 
  if (String(topic) == "vehan/muc/resevoir") {
    Serial.print("Float Level = ");
    if(resevoirlevel == "FULL"){
      Serial.println("FULL");
    }
    else if(resevoirlevel == "EMPTY"){
      Serial.println("EMPTY");
    }
  }
}

void pubdata(){
    if(OldPump != Water_level){
    
    OldPump = Water_level;
 
    if (Water_level ==0){
    client.publish("aquarium1/atopump", "ON");
    } else if (Water_level ==1){
    client.publish("aquarium1/atopump", "OFF");
    }
   }
}

void reconnect(){
  while (!client.connected()) {
      digitalWrite(RelayPin, LOW);
      String client_id = "ATOMCU";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
          Serial.println("Mqtt broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
      }
      client.subscribe ("vehan/muc/resevoir");
  }
} 


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  pinMode(13,INPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(RelayPin, OUTPUT);
}

void loop() {
  client.loop();
  reconnect();
  pubdata();

 long now = millis();
  
if (now - lastMsg > 1000) {

   lastMsg = now;
   
   Water_level=digitalRead(13);
   Serial.print("Water_level= ");
   Serial.println(Water_level,DEC);
   FloatSwitch=digitalRead(12);
   Serial.print("FloatSwitch= ");
   Serial.println(FloatSwitch);
    
    if (Water_level ==0){
    Serial.println ("PUMP ON");
    digitalWrite(RelayPin, HIGH);
    } else {
    Serial.println ("PUMP OFF");
    digitalWrite(RelayPin, LOW);
    } 
  }
}
