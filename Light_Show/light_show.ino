//#include <SoftwareSerial.h>
#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

//SoftwareSerial BTOOTH =  SoftwareSerial(rxPin, txPin);

#define APIN 20

int normal = 800;
int medium = 820;
int high = 830;
int state = 1;
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

if(Serial1.available() > 0)
 {

    String str = Serial1.readString();
       
          if(str == "CHANGE_STATE"){
            if(state == 1){
              Serial.println("Yellow");
              state = state + 1;
              digitalWrite(YELLOW, HIGH);
              digitalWrite(GREEN, LOW);
            }
            else if(state == 2){
              Serial.println("red");
              state = state + 1;
              digitalWrite(RED, HIGH);
              digitalWrite(YELLOW, LOW);
            }
            else if(state == 3){
              Serial.println("green");
              digitalWrite(GREEN, HIGH);
              digitalWrite(RED, LOW); 
              state = state + 1;
            }
              else if(state == 4){
              Serial.println("colours");
                            
              bool colours = true;
                  while (colours){
                    
                  digitalWrite(GREEN, LOW);
                  digitalWrite(YELLOW, HIGH);
                  digitalWrite(RED, LOW);
                  delay(400);
                  digitalWrite(GREEN, LOW);
                  digitalWrite(YELLOW, LOW);
                  digitalWrite(RED, HIGH);
                  delay(400);
                  digitalWrite(GREEN, LOW);
                  digitalWrite(YELLOW, HIGH);
                  digitalWrite(RED, LOW);
                  delay(400);
                  digitalWrite(GREEN, HIGH);
                  digitalWrite(YELLOW, LOW);
                  digitalWrite(RED, LOW);
                  //delay(250);                          

                  String str = Serial1.readString();
                  if(str == "CHANGE_STATE") {
                    colours = false;
                    state = state - 3;
                  digitalWrite(GREEN, LOW);
                  digitalWrite(YELLOW, LOW);
                  digitalWrite(RED, LOW);
                  }
              }
            }
          }
    }
}






      


    
