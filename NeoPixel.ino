// C++ code
//Group Member: Aryan Patel,Gurpreet,Gagandeep.

                
#include <Adafruit_NeoPixel.h> //include the library for the NeoPixel LED strip

int ledPin = 3; //initialize the LED pin number
int ledNo = 12; //initialize the number of LEDs in the strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledNo, ledPin, NEO_RGB + NEO_KHZ800); // the NeoPixel strip object

int buzzerPin = 2; //initialize the buzzer pin number
int echoPin = 6; //initialize the echo pin number
int trigPin = 5; //initialize the trigger pin number
int minDistance = 100; //set the minimum distance to be detected
int maxDistance = 300; //set the maximum distance to be detected

void setup() {
  pinMode(buzzerPin, OUTPUT); //set the buzzer pin as an output
  pinMode(trigPin, OUTPUT); //set the trigger pin as an output
  pinMode(echoPin, INPUT); //set the echo pin as an input
  Serial.begin(9600); 
  strip.begin(); //initialize the NeoPixel strip object
  for (int i = 0; i < ledNo; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); //turn off all the LEDs in the strip
  }
  strip.show(); //show the current state of the NeoPixel strip
}

void loop() {
  int distance = calcDistance(); //get the distance from the ultrasonic sensor
  Serial.println(distance); //print the distance to the serial monitor
  int ledsToGlow = map(distance, minDistance, maxDistance, ledNo, 1); //map the distance to the number of LEDs to turn on
  Serial.println(ledsToGlow); //print the number of LEDs to turn on to the serial monitor
  if (ledsToGlow == 12) {
    digitalWrite(buzzerPin, HIGH); //if all LEDs are turned on, turn on the buzzer
  }
  else {
    digitalWrite(buzzerPin, LOW); //otherwise, turn off the buzzer
  }
  for (int i = 0; i < ledsToGlow; i++) {
    if (i < 4) {
      strip.setPixelColor(i, strip.Color(50, 0, 0)); //set the color of the first 4 LEDs to red
    }
    else if (i >= 4 && i < 8) {
      strip.setPixelColor(i, strip.Color(50, 50, 0)); //set the color of the next 4 LEDs to yellow
    }
    else if (i >= 8 && i < 12) {
      strip.setPixelColor(i, strip.Color(0, 50, 0)); //set the color of the last 4 LEDs to green
    }
  }
  for (int i = ledsToGlow; i < ledNo; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); //turn off any remaining LEDs in the strip
  }
  strip.show(); //show the current state of the NeoPixel strip
  delay(50); //delay for 50 milliseconds
}

// This function calculates the distance of an object from the ultrasonic sensor

int calcDistance()
{
  long distance, duration;
  // set the trigger pin to LOW state for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // set the trigger pin to HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  // set the trigger pin to LOW state
  digitalWrite(trigPin, LOW);
  // read the duration of the echo pulse and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 29 / 2; // divide by 29 to convert microseconds to centimeters and divide by 2 for round trip
  // ensure that the distance is within the minimum and maximum distance range
  if(distance >= maxDistance)
  {
    distance = maxDistance;
  }
  if(distance <= minDistance)
  {
    distance = minDistance;
  }
  // return the calculated distance
  return distance;
}
