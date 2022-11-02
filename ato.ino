#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define RelayPin 14
#define LevelPin 13

const char* ssid = "ssid";
const char* password = "password";
const char *mqtt_broker = "broker";
const int mqtt_port = 1883;

String resevoirlevel;
String OldLevel;

WiFiClient espClient;
PubSubClient client(espClient);

int Water_level=0;
int OldPump;
int TimeOn=0;

void pumpcontrol(){
    if(OldPump != Water_level){
    
    OldPump = Water_level;
 
    if (Water_level ==0){
      digitalWrite(RelayPin, HIGH);
      client.publish("vehan/muc/atopump", "ON");
      TimeOn = millis();
    } else if (Water_level ==1){
      digitalWrite(RelayPin, LOW);
      client.publish("vehan/muc/atopump", "OFF");
      TimeOn = 0;
    }
   }
}

void publevel(){
    if(OldLevel != resevoirlevel){
    
    OldLevel = resevoirlevel;
     
    if (resevoirlevel == "EMPTY"){
      digitalWrite(RelayPin, LOW);
      client.publish("vehan/muc/resevoir", "EMPTY");
    } else if (resevoirlevel == "FULL"){
      client.publish("vehan/muc/resevoir", "FULL");
    }
  }
}

void reconnect(){
  while (!client.connected()) {
      digitalWrite(RelayPin, LOW);
      String client_id = "MUC-Aquarium-Sensor";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
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
  pinMode(LevelPin,INPUT);
  pinMode(12, INPUT);
  pinMode(RelayPin, OUTPUT);
}

void loop() {
  client.loop();
  reconnect();
  pumpcontrol();
  publevel();
  
  Water_level=digitalRead(LevelPin);
  Serial.print("Water_level= ");
  Serial.println(Water_level,DEC);
  
    if (millis() - TimeOn >= 1800000){
      resevoirlevel= "EMPTY";
    }else{
      resevoirlevel= "FULL";
    }
 }
