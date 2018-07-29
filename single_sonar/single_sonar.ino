// DueTimer - Version: Latest 
#include <DueTimer.h>
#include <FIR.h>

// Finite Impulse Response
//20 Hz rate
FIR<long, 9> fir;

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
volatile long duration; //microseconds
volatile long distance; // inches
volatile long filtered;

void setup() {
  //pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  //http://t-filter.engineerjs.com
  //0-1 Hz Pass
  //3-10Hz Stop
  long coef[13] = {
    394,
    1069,
    2006,
    3240,
    4361,
    5250,
    5524,
    5250,
    4361,
    3240,
    2006,
    1069,
    394
  };
  // Set the coefficients
  fir.setFilterCoeffs(coef);

  attachInterrupt(echoPin, startMeasuring, RISING);
  Timer3.attachInterrupt(displayFilteredMetrics).setFrequency(20).start();
  Serial.begin(115200); // Starts the serial communication
}

void startMeasuring() {
  duration = micros();
  attachInterrupt(echoPin, stopMeasuring, FALLING);
}

void stopMeasuring() {
  duration = micros() - duration;
  distance = duration / 147;
  
  attachInterrupt(echoPin, startMeasuring, RISING);
}

void displayFilteredMetrics() {
  //filter reading every 20Hz
  filtered = fir.processReading(distance);
  
  // Prints the distance on the Serial Monitor for prev iteration
  Serial.print(distance);
  Serial.print(" ");
  Serial.println(filtered);
}

void loop() {
  while (1) {
    
  }
}
