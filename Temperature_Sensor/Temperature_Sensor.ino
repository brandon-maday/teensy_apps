#include "DHT.h"
#define DHTPIN 21      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 

#define LEDPIN 11

int RED = 16;
int YELLOW = 15;
int GREEN = 14;
int BUZZER = 17;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
// Setup serial for monitor and Setup Serial1 for BlueTooth
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(DHTPIN, INPUT);
  dht.begin();
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
// Process commands from bluetooth first.
  if(Serial1.available() > 0){
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, LOW);
      String str = Serial1.readString();//.substring(1);

      if(str == "START_TEMP"){
        bool started = true;
        while(started){
  

          Serial.println("RUNNING in start temp");
    
        
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          float f = dht.readTemperature(true);
      
          float hif = dht.computeHeatIndex(f, h);
          float hic = dht.computeHeatIndex(t, h, false);

     //      if(t > 29.0){
       //     Serial1.print("T");
        //  }  
          Serial1.print(F("Temperature: "));
          Serial1.print(t);
          Serial1.print(F("C Humidity: "));
          Serial1.print(h);
          Serial1.print(F("% "));
         // Serial1.print(t);
          // Serial1.print(F("C "));
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
 
          
        

    
    //Serial.println(str);

  } 
  //else if(str == "STOP_TEMP"){
    //  digitalWrite(LEDPIN, LOW);
      //Serial.println("STOPPED");
      //delay(1000);
  //}
  }
}
}
