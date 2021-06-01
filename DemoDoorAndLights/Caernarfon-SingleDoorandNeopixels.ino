/*
 * This work is based on the Servo for ESP8266 and the IRremoteESP8266: IRrecvDemo 
 * 
 * Dafydd Roche - 4/7/2021
 * 
 * Remote control to switch on some gates.
 * https://amzn.to/2Qc9BI0
 * 
 * Wemos D1 mini.
 * D5 connected to VOUT of the IR reciever
 * D6,D7,D8 connected to the VIN of 3 servos.
 * 
 * Neopixel Data out on D3.
 * 
 * 
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>


#define LED_PIN    D3
#define LED_COUNT 3
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = D5;

IRrecv irrecv(kRecvPin);

decode_results results;
Servo trapOne;


int trapState = 0;
int ledState = 0;

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

  strip.setPixelColor(0, random(146,164), random(90,109), 0);
  strip.setPixelColor(1, random(146,164), random(90,109), 0);
  strip.setPixelColor(2, random(146,164), random(90,109), 0);
  strip.show(); 

  
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
  trapOne.attach(D6);
  trapOne.write(0);
    delay(500);
  trapOne.detach();
}

void loop() {
  
  if (ledState == 0) {
    strip.setPixelColor(2, random(146,164), random(90,109), 0);
    strip.setPixelColor(1, random(146,164), random(90,109), 0);
    strip.setPixelColor(0, random(146,164), random(90,109), 0);
    strip.show();   
    delay(random(50,100));
  }
  
  if (irrecv.decode(&results)) {

  
  int pos;
  
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    if (results.value == 0xFF6897) { // Arduino Remote 0 - only runs if this is the code pressed
      
     trapOne.attach(D6);  

    if (trapState == 2 ){ trapState = 0;}
    Serial.println(trapState);
      switch (trapState) {
    case 0:    // RESET THE TRAP
      Serial.println("RESET TRAP");
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        trapOne.write(pos);              // tell servo to go to position in variable 'pos'
      delay(25);  }                     // waits 15ms for the servo to reach the position
      break;
    case 1:    // GATE 1 Down
      Serial.println("GATE 1 DOWN");
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      trapOne.write(pos);              // tell servo to go to position in variable 'pos'
      delay(25); }                       // waits 15ms for the servo to reach the position
      break;
      }
    trapState++;
    trapOne.detach();
    }
    if (results.value == 0xFF30CF) {
      if (ledState == 0) {
        ledState = 1;
        strip.setPixelColor(2, 255,0,0);
        strip.setPixelColor(1, 255,0,0);
        strip.setPixelColor(0, 255,0,0);
        strip.show();
      }
      else {
        ledState = 0;
      }
    }
  delay(500);

    irrecv.resume();  // Receive the next value
  }
    
}
