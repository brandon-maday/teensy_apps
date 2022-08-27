#include "DHT.h"
#define DHTPIN 21      
#define DHTTYPE DHT11
#define LEDPIN 11

// define coloured LED and buzzer pins

int RED = 16;
int YELLOW = 15;
int GREEN = 14;
int BUZZER = 17;

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);

  dht.begin();
  
}

//Teensy waits for any command to light GREEN LED to show it is
//ready to receive commands. It will wait for START_TEMP before sending 
//sensor readings through Serial1.

//This program will not activate yellow and red LEDs or the buzzer through reading the temperature.
//The logic flow is: READ TEMP >> SEND TEMP to Raspi >> Raspi interprets temp and sends message if 
//threshold has been reached >> publishes MQTT message >> Subcriber receives and sends message to Teensy
//>> Teensy will interpret message.

void loop() {

  if(Serial1.available() > 0){

      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, LOW);

      String str = Serial1.readString();

      if(str == "START_TEMP"){
        bool started = true;
        while(started){
        
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          float f = dht.readTemperature(true);
          float hif = dht.computeHeatIndex(f, h);
          float hic = dht.computeHeatIndex(t, h, false);

          Serial1.print(F("Temperature: "));
          Serial1.print(t);
          Serial1.print(F("C Humidity: "));
          Serial1.print(h);
          Serial1.print(F("% "));
          Serial1.print(f);
          Serial1.print(F("F  Heat index: "));
          Serial1.print(hic);
          Serial1.print(F("C "));
          Serial1.print(hif);
          Serial1.println(F("F"));

          delay(1000);
          String str = Serial1.readString();

          if (str == "MEDIUM_TEMP"){
              digitalWrite(YELLOW, HIGH);
              digitalWrite(RED, LOW);
          }
          if (str == "HIGH_TEMP"){
              
              digitalWrite(RED, HIGH);
              digitalWrite(BUZZER, HIGH);
              delay(100);
              digitalWrite(BUZZER, LOW);
              delay(100);
              digitalWrite(BUZZER, HIGH);
              delay(100);
              digitalWrite(BUZZER, LOW);
              delay(100);
              digitalWrite(BUZZER, HIGH);
              delay(100);
              digitalWrite(BUZZER, LOW);
              delay(100);
          }
          if(str == "NORMAL_TEMP"){
              digitalWrite(YELLOW, LOW);
          }
          if(str == "STOP_TEMP"){
              digitalWrite(GREEN, LOW);
              digitalWrite(YELLOW, LOW);
              digitalWrite(RED, LOW);
              Serial.println("STOPPED");
              started = false;
              delay(1000);
          }

        } 

      }
  }
}
