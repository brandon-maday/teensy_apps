
#define APIN 20

// Sound threshold values

int normal = 800;
int medium = 820;
int high = 830;

// Define teensy pins

int BUZZER = 17;
int RED = 16;
int YELLOW = 15;
int GREEN = 14;
int sensorValue = 0;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  // Set Pinmodes

  pinMode(APIN, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

}

//Once receiving an initial start message, teensy will continuously listen
//for sound and print to serial. CTRL+SHIFT+L in arduino IDE for plot monitor.
//if sound reaches above thresholds for MEDIUM and HIGH it will send 
//the sound level reached and light the colour of the yellow or red LED.

void loop() {

  if(Serial1.available() > 0)
  {
    sensorValue = analogRead(APIN);
    digitalWrite(GREEN, HIGH);
    Serial.println(sensorValue);

    if(sensorValue > medium)
    {  
      digitalWrite(YELLOW, HIGH);
      
      if(sensorValue > high)      
      {
        Serial1.print("RED level: ");
        Serial1.println(sensorValue);

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

}
