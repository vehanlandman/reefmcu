#include <WiFi.h>
#include <WiFiUDP.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 13; 

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

const char* host = "ReefMCU-Sensor";
const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_broker = "MQTT Server";

const long utcOffsetInSeconds = 7200;

const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

long lastMsg = 0;
char msg[50];
int value = 0;

float Temp;

int ATOSensor;
int OldValue=1;
int OldRValue=1;
int ResevoirLevel;
int FloatSensor=12;
int FloatLevel=1;

void reconnect(){
  while (!client.connected()) {
      String client_id = "ReefMCU Sensor ";
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

void pubdata(){
    if(OldValue != ATOSensor){
    
    OldValue = ATOSensor;
 
    if (ATOSensor ==1){
    client.publish("aquarium1/ato", "ON");
    } else if (ATOSensor ==0){
    client.publish("aquarium1/ato", "OFF");
     }
    }
    if(OldRValue != ResevoirLevel){
    
    OldRValue = ResevoirLevel;
 
    if (ResevoirLevel ==0){
    client.publish("aquarium1/resevoir", "Full");
    } else if (ResevoirLevel ==1){
    client.publish("aquarium1/resevoir", "Empty");
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
  
  timeClient.begin();
  sensors.begin();

  timeClient.update();
  String TimeNow = timeClient.getFormattedTime();
  int hours = timeClient.getHours();

   pinMode(14,INPUT);
   pinMode(FloatSensor,INPUT_PULLUP);
   pinMode (13, INPUT);
}

void loop() {
  reconnect();
  client.loop();
  timeClient.update();
  pubdata();
  String TimeNow = timeClient.getFormattedTime();

  long now = millis();
  
if (now - lastMsg > 20000) {
   
   lastMsg = now;

   sensors.requestTemperatures(); 
   float tc = sensors.getTempCByIndex(0);

   char Temp[8];
    dtostrf(tc, 1, 2, Temp);
    Serial.print("Temperature: ");
    Serial.println(Temp);
    client.publish("aquarium1/temp", Temp);

  }

 ATOSensor=digitalRead(14);

 FloatLevel = digitalRead(FloatSensor);

 if(FloatLevel ==HIGH){
  ResevoirLevel=1;
 }else if (FloatLevel ==LOW){
  ResevoirLevel=0;
 }
}
