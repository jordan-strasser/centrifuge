float prevTime= 0;
float currTime = 0;
volatile int pulseCount;
float freqHz;

void setup() {
  pinMode(7, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(7), pulseCounter, RISING); 

}

void pulseCounter() {
  pulseCount += 1;
}

void getFreq() {
  if(pulseCount == 0)  {
    prevTime = millis();
  }
  if(pulseCount == 30) {
    currTime = millis();
    float elapsed = (currTime - prevTime)/1000;
    freqHz = pulseCount/elapsed;
    pulseCount = 0;
    
  }
}

void loop() {

  getFreq(); 
  if(freqHz != 0){
    Serial.print("Current frequency (Hz): ");
    Serial.println(freqHz);
  }
}
