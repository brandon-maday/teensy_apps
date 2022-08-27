//#include <SoftwareSerial.h>
#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

//SoftwareSerial BTOOTH =  SoftwareSerial(rxPin, txPin);

#define APIN 20

int normal = 800;
int medium = 820;
int high = 830;

int BUZZER = 17;
int RED = 16;
int YELLOW = 15;
int GREEN = 14;
int sensorValue = 0;



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  pinMode(APIN, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial1.begin(9600);

}

// the loop routine runs over and over again forever:
void loop() {
  //Serial.println(Serial.available());
  // delay(300);
  if(Serial1.available() > 0)
  {
 //       String str = Serial1.readString();
       
 //         if(str == "ALARM_ON"){
 //           digitalWrite(BUZZER, HIGH);
 //           delay(2000);
 //           digitalWrite(BUZZER, LOW);// read the input on analog pin 0:
 //         }

  // print out the value you read:
    sensorValue = analogRead(APIN);
    digitalWrite(GREEN, HIGH);
    Serial.println(sensorValue);
    //Serial1.println(sensorValue);
    if(sensorValue > medium)
    {
  
      digitalWrite(YELLOW, HIGH);
      //Serial1.println(sensorValue);

      
      if(sensorValue > high)      
      {
        Serial1.print("RED level: ");
        Serial1.println(sensorValue);
        //Serial1.println(sensorValue);
        digitalWrite(RED, HIGH);
        digitalWrite(BUZZER, HIGH);
        delay(500);
      }
      else{
        Serial1.print("YELLOW level: ");
        Serial1.println(sensorValue);
        delay(100);
        
      }
      digitalWrite(RED, LOW);
      digitalWrite(BUZZER, LOW);
    }
    digitalWrite(YELLOW, LOW);

  }

  //Serial.println(sensorValue);
}
