String userInput;
int duration;
int rpm;
int sepindex;
int setpoint;


void setup() {
  Serial.begin(9600);
}

void loop() {
 
  if(Serial.available() > 0) {
    userInput = Serial.readString();

    sepindex = userInput.indexOf('n');
  

    if(userInput[0] == 's') {
      rpm = userInput.substring(1, sepindex).toInt();
      Serial.println(" ");
      Serial.println(" ");
      Serial.print("Set RPM: ");
      Serial.println(rpm);
      setpoint = map(rpm, 0, 2900, 0, 255);
      Serial.print("Duty cycle setpoint for pin 3: ");
      Serial.println(setpoint);
    }
   
    if(userInput[sepindex + 1] == 't') {
     duration = userInput.substring(sepindex+2).toInt();
     Serial.print("Duration (seconds): ");
     Serial.println(duration);
    }
  } 
}

     
  
