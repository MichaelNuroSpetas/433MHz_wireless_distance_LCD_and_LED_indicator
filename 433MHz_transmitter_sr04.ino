/*
By Michael Nuro Spetås
Michael.Nuro.Spetas@gmail.com 

Thanks to Markus Ulfberg

Feel free to use and modify
*/


#include <VirtualWire.h>

// LED's
const int ledPin = 13;


// Ultrasonic sensor 
const int trigPin = 2;
const int echoPin = 3;


int distanceData;
char distanceCharMsg[4]; 

void setup() {

 // PinModes 
 pinMode(ledPin,OUTPUT);
 // Sensor(s)
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 
 // for debugging
 Serial.begin(9600); 
 
 // VirtualWire setup
 vw_set_tx_pin(12);
 vw_setup(4000);     // Bits per sec


}

void loop() {
  int duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  // Read and store Sensor 1 data
  
  // Convert integer data to Char array directly 
  itoa(distance,distanceCharMsg,10);
  
  // DEBUG
  Serial.print("distance Integer: ");
  Serial.print(distance);
  Serial.print(" distance CharMsg: ");
  Serial.print(distanceCharMsg);
  Serial.println(" ");
  delay(10);

  // END DEBUG
 
 digitalWrite(13, true); // Turn on a light to show transmitting
 vw_send((uint8_t *)distanceCharMsg, strlen(distanceCharMsg));
 vw_wait_tx(); // Wait until the whole message is gone
 digitalWrite(13, false); // Turn off a light after transmission
 delay(10); 
 
} // END void loop...
