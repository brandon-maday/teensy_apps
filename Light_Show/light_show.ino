
#define APIN 20

//initialise variables
int state = 1;
int RED = 16;
int YELLOW = 15;
int GREEN = 14;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  // Set pinModes
  pinMode(APIN, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);

}

// Simple program that will cycle through 4 different colour states (+1 more state for all LEDs off)
// Each time CHANGE_STATE is receieved it will change.

void loop() {

  if(Serial1.available() > 0)
  {
    String str = Serial1.readString();
       
    if(str == "CHANGE_STATE"){

      if(state == 1){
        Serial.println("Yellow Active");
        state = state + 1;
        digitalWrite(YELLOW, HIGH);
        digitalWrite(GREEN, LOW);
            }

      else if(state == 2){
        Serial.println("Red Active");
        state = state + 1;
        digitalWrite(RED, HIGH);
        digitalWrite(YELLOW, LOW);
            }

      else if(state == 3){
        Serial.println("Green Active");
        digitalWrite(GREEN, HIGH);
        digitalWrite(RED, LOW); 
        state = state + 1;
            }

      else if(state == 4){
        Serial.println("Light Show Active");
                            
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






      


    
