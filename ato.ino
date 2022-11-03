#include <WiFiManager.h> 
#include <PubSubClient.h>
#include "Arduino.h"
#include <ESP_Mail_Client.h>

const char *mqtt_broker = "mqtt";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

int Water_level=0;
int OldPump;
int timer=0;
int pumpstate;

long lastMsg = 0;

String resevoirlevel;
String OldLevel;

#define RelayPin 14
#define LevelPin 13

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "<SENDER EMAIL>"
#define AUTHOR_PASSWORD "<SENDER PASSWORD>"

#define RECIPIENT_EMAIL "<NUMBER@SERVICEPROVIDER.COM>"

SMTPSession smtp;

void smtpCallback(SMTP_Status status);

void reconnect(){
  while (!client.connected()) {
      digitalWrite(RelayPin, LOW); //prevents pump from staying on if lost signal to MQTT
      String client_id = "ESP-ATO";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s is connecting to the mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
          Serial.println("Mqtt broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
   }
}

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res;
  res = wm.autoConnect("ESP-ATO");
    if(!res) {
        Serial.println("Failed to connect");
        delay (5000);
        ESP.restart();
    } 
    else {   
        Serial.println("connected");
    }

  client.setServer(mqtt_broker, mqtt_port);
  pinMode(LevelPin,INPUT);
  pinMode(RelayPin, OUTPUT);
}

void loop() {
  client.loop();
  reconnect();
  pumpcontrol();
  publevel();

  long now = millis();

if (now - lastMsg > 1000){
  lastMsg = now;
  Water_level=digitalRead(LevelPin);
  Serial.print("Water_level= ");
  Serial.println(Water_level,DEC);
  if (pumpstate = 1){
    timer = timer + 1;
   }else if (pumpstate = 0){
    timer = 0;
  }
}

if (timer >= 1800){
      resevoirlevel= "EMPTY";
    }else if (timer < 1800){
      resevoirlevel= "FULL";
    }
}

void pumpcontrol(){
    if(OldPump != Water_level){
    
    OldPump = Water_level;
 
    if (Water_level == 0){
      digitalWrite(RelayPin, HIGH);
      client.publish("esp/atopump", "ON");
      pumpstate = 1;
    } else if (Water_level == 1){
      digitalWrite(RelayPin, LOW);
      client.publish("esp/atopump", "OFF");
      pumpstate = 0;
    }
  }
}

void publevel(){
    if(OldLevel != resevoirlevel){
    
    OldLevel = resevoirlevel;
     
    if (resevoirlevel == "EMPTY"){
      digitalWrite(RelayPin, LOW);
      client.publish("esp/resevoir", "EMPTY");
      client.publish("esp/atopump", "OFF");
      sendSMS();
    } else if (resevoirlevel == "FULL"){
      client.publish("esp/resevoir", "FULL");
    }
  }
}

void sendSMS(){
  
  smtp.debug(1);

  ESP_Mail_Session session;

  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  SMTP_Message message;

  message.sender.name = "ESP-ATO";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "";
  message.addRecipient("name", RECIPIENT_EMAIL);

  String textMsg = "Tank Notification: The resevoir of your reef tank is empty!";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  if (!smtp.connect(&session))
    return;

  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
}
