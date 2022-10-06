// This code is not necessary if you are using the SmartPlug. 

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <NTPClient.h>


const char* host = "Sump Light";
const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_broker = "MQTT Broker";

const long utcOffsetInSeconds = 7200;

const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

long lastMsg = 0;
char msg[50];
int value = 0;

String TimeNow;
String TimeOn = "08:00:00";
String TimeOff = "20:00:00";

int relayPin = 12;

int hours;
int hoursOn = 8;
int hoursOff = 20;

void reconnect(){
  while (!client.connected()) {
      String client_id = "Sump-Sonoff ";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
          Serial.println("MQTT broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
    client.subscribe("aquarium1/sumplight");
  }
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
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
  timeClient.begin();
  pinMode(relayPin, OUTPUT);

  timeClient.update();
  String TimeNow = timeClient.getFormattedTime();
  int hours = timeClient.getHours();
 if (hoursOn <= hours < hoursOff){ //This part is for my fellow South Africans if loadshedding causes your ESP to turn off
    digitalWrite(relayPin, HIGH);
 } else if (hoursOn > hours >= hoursOff){
    digitalWrite (relayPin, LOW);
  }
}

void loop() {
  reconnect();
  client.loop();
  timeClient.update();
  String TimeNow = timeClient.getFormattedTime();
  
  if (TimeNow == TimeOn){
     client.publish("aquarium1/sumplight", "on");
  } else if (TimeNow == TimeOff){
     client.publish("aquarium1/sumplight", "off");
  }
}

void callback(char *topic, byte *payload, unsigned int length) {

   Serial.print("Message arrived in topic: ");
   Serial.println(topic);
   Serial.print("Message: ");  
  
   String messageValue;
    for (int i=0;i<length;i++) {
        messageValue = messageValue + (char)payload[i];
        }
    Serial.print(messageValue);
    
    if (messageValue == "on"){
        digitalWrite(relayPin, HIGH);
    } else if (messageValue == "off"){
        digitalWrite(relayPin, LOW);
    }
   
    Serial.println();
 }
