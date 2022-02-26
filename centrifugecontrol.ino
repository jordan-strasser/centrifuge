#include <PID_v1.h>

#define PIN_INPUT 13
#define PIN_OUTPUT 3

String userInput;
int duration;
int rpm;
int sepindex;
double setpoint, input, output;
double Kp = 1, Ki = 1, Kd = 0.1;
volatile int pulsecount = 0;
int prevTime = 0; 
int currTime = 0;
int freqHz;
int pulseCount = 0;
int shortelapsed; 


PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void pulseCounter() {
  pulseCount += 1;
}

//goal is to cut off power if derivative of freq change is too much
void mechanicalDanger() {
  
 
}
//to convert pulse counts to frequency
void getFreq() {
  if(pulsecount == 0)  {
    prevTime = millis();
  }
  if(pulsecount == 30) {
    currTime = millis();
    int elapsed = (currTime - prevTime)/1000;
    freqHz = pulseCount/elapsed;
    pulseCount = 0;
  }
}

void setup() {
  Serial.begin(9600);
  myPID.SetMode(AUTOMATIC); 
  myPID.SetTunings(Kp, Ki, Kd);
  attachInterrupt(digitalPinToInterrupt(13), pulseCounter, RISING);
  // attachInterrupt(digitalPinToInterrupt(13), mechanicalDanger, FALLING);
}


void loop() {
  
 
  if(Serial.available() > 0) {
    userInput = Serial.readString();

    sepindex = userInput.indexOf('n');
  

    if(userInput[0] == 's') {
      rpm = userInput.substring(1, sepindex).toInt();
      setpoint = map(rpm, 0, 2900, 0, 255);
      Serial.println(rpm);
    }
   
    if(userInput[sepindex + 1] == 't') {
     duration = userInput.substring(sepindex+2).toInt();
     Serial.println(duration);
    }
  }

  getFreq(); 
  if(freqHz != 0){
    Serial.print("Current frequency (Hz): ");
    Serial.println(freqHz); 
    input = map(freqHz, 0, 49, 0, 255);
  }
  // how does this check for FreqHz != 0 conflict with the logic of setpoint = 0;
  myPID.Compute();
  if(output > 255) {
    output = 255;
  }
  if(input == setpoint) {
    Serial.print("RPM reached, ");
    Serial.print(rpm);
  }
  analogWrite(3, output); //outputs value on pin 3 connecting to MOSFET to achieve desired rpm
  Serial.print(input);
  Serial.print(" "); 
  Serial.println(output);
  Serial.print(" "); 
  Serial.println(setpoint);

  
}

     
  
