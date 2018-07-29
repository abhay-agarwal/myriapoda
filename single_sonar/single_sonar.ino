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
long distance;
long elapsed = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication

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
  
  // The filter automatically determines the gain
  //Serial.print("Automatically calculated gain: ");
  //Serial.println(fir.getGain());
}

void loop() {
  
  elapsed = millis();
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  // 147 uS per inch
  distance = pulseIn(echoPin, HIGH) / 147;
  
  // Calculating the distance
  //smoothed = (a * distance) + (b * smoothed);
  
  digitalWrite(trigPin, LOW);

  elapsed = millis() - elapsed;
  
  // Prints the distance on the Serial Monitor
  Serial.print(distance);
  Serial.print(" ");
  Serial.print(fir.processReading(distance));
  Serial.print(" ");
  Serial.println(1000 / elapsed);
}
