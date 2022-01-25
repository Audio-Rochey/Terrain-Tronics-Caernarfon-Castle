/*
 * 1/24/2022 -- building upon the initial version.
 * This code uses 2 external files within arduino and will define the functionalty for almost every button the remote.
 * Here are the requirements:https://github.com/Audio-Rochey/Terrain-Tronics-Caernarfon-Castle/blob/main/Demo-MultiRemote/Requirements.txt
 * 
 * I followed this video to learn how to split the files in arduino: https://www.youtube.com/watch?v=BdstuZP6l5E
 * However, rather than namign files .cpp, i used INO.
 * 
 * Description of states:
 * ledState Zero is All Lights Off
 * ledState One is all Red.
 * ledState Two is flicker. (which gets updated in the main loop.
 * ledState Three is lava
 * ^^^ this was previously used to toggle the states.
 * 
 * trapOneState between 0 and 1 used to 
 * 
 * 
 * This work is based on the Servo for ESP8266 and the IRremoteESP8266: IRrecvDemo 
 * 
 * Dafydd Roche - 1/24/2022
 * 
 * Remote control to switch on some gates.
 * https://amzn.to/2Qc9BI0
 * 
 * Wemos D1 mini.
 * D5 connected to VOUT of the IR reciever
 * D6,D7,D8 connected to the VIN of 3 servos.
 * Neopixel Data out on D3.
 * Keepalive isn't used.
 * 
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
//#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#include "buttonfunctions.h" // put the functions for each button in a separate file.

Servo trapOne;
Servo trapTwo;
Servo trapThree;
int trapOneState;
int trapOnePos;
int trapTwoState;
int trapTwoPos;
int trapThreeState;
int trapThreePos;

const String softwareVersion = "V1.0";
const String softwareDate = "1/24/2022";     
const String CaernarfonVer = "1p0";
const int keepAlive = D0;// The Keepalive pin for USB Power Banks is D0, but isn't used in this demo
const String keepAlivePin = "D0";

#define LED_PIN    D3
#define LED_COUNT 33
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = D5;

IRrecv irrecv(kRecvPin);

decode_results results;

// int trapOneState = 0;
int ledState = 0;
unsigned long ledPreviousMillis = 0;        // will store last time LED was updated
long flickerLedInterval = 0;                // this will be updated with every flicker.

unsigned long lavaPreviousMillis = 0;        // will store last time LED was updated
long lavaLedInterval = 0;                // this will be updated with every flicker.


int globalBrightness = 127; // start at half max brightness




void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(globalBrightness); // 

  strip.setPixelColor(0, random(146,164), random(90,109), 0);
  strip.setPixelColor(1, random(146,164), random(90,109), 0);
  strip.setPixelColor(2, random(146,164), random(90,109), 0);
  strip.show(); 


  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  
  Serial.println("*****");
  delay(100);
  Serial.println("TerrainTronics Demo - Generic Remote Control Standard");
  Serial.print("Version ");
  Serial.print(softwareVersion);
  Serial.print(" Date of Compile ");
  Serial.print(softwareDate);
  Serial.print(" Caernarfon HW Version ");
  Serial.println(CaernarfonVer);
  Serial.print("IRrecv: ");
  Serial.println(kRecvPin);
  trapOne.attach(D6,500,2400);
  trapTwo.attach(D7,500,2400);
  trapThree.attach(D8,500,2400);
  trapOne.write(0);
    delay(500);
  //trapOne.detach();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // this is the only LED update that's handled on every loop - as it randomizes the colors.
  if ((ledState == 2)&&(currentMillis - ledPreviousMillis >= flickerLedInterval)) { // if we're in mode 2, AND the current-prev time is more than the flicker
    // save the last time you blinked the LED
    ledPreviousMillis = currentMillis; // resets the timer.
    int currLED = 0;
    for (currLED = 0; currLED <= LED_COUNT; currLED++) {
      strip.setPixelColor(currLED, random(146,164), random(90,109), 0);
    }
    strip.show();   
    flickerLedInterval = random(50,100);
  }


  if ((ledState == 3)&&(currentMillis - lavaPreviousMillis >= lavaLedInterval)) { // if we're in mode 2, AND the current-prev time is more than the flicker
    // save the last time you blinked the LED
    lavaPreviousMillis = currentMillis; // resets the timer.
    int currLED = 0;
    for (currLED = 0; currLED <= LED_COUNT; currLED++) {
      int j = random(0,63); // 10 in 64 chance that there will be flicker that isn't pure red.
      if (j < 10) {
        strip.setPixelColor(currLED, 150, random(0,30),random(0,3));
    
      }
      else {      strip.setPixelColor(currLED, 255, 0, 0);
    }
    }
    strip.show();   
    lavaLedInterval = random(250,500);
  }
  
  if (irrecv.decode(&results)) {
  
    // print() & println() can't handle printing long longs. (uint64_t)
    Serial.print("IR Recieve: ");
    serialPrintUint64(results.value, HEX);
    Serial.println("");

    
    if (results.value == 0xFF02FD) { // NEXT - add 15 to current position..
      trapOnePos = trapOnePos + 15;
      if (trapOnePos > 180) { trapOnePos = 180; }
      Serial.println(trapOnePos);
      trapOne.write(trapOnePos);
    }

    if (results.value == 0xFF22DD) { // PREV - subtract 15 to current position..
      trapOnePos = trapOnePos - 15;
      if (trapOnePos < 1) { trapOnePos = 0; }
      Serial.println(trapOnePos);
      trapOne.write(trapOnePos);
    }
    
    if (results.value == 0xFFE01F) { // Arduino Remote Vol- lower the brightness in half.
      globalBrightness = (globalBrightness/2);
      if (globalBrightness < 1 ) { globalBrightness = 1; }
      strip.setBrightness(globalBrightness);
      strip.show();
    }

    if (results.value == 0xFFA857) { // Arduino Remote Vol+ Double the brightness.
      globalBrightness = (globalBrightness*2);
      if (globalBrightness > 255) { globalBrightness = 255; }
      strip.setBrightness(globalBrightness);
      strip.show();
    }
    
    if (results.value == 0xFF6897) { // Button 0 - only runs if this is the code pressed
      buttonZERO();
    }    
    if (results.value == 0xFF30CF) { // Button 0 Toggle Motor A all the way one way or the other (e.g. a sliding door)
      buttonONE();
    }
    if (results.value == 0xFF18E7) { // Button 2 Toggle Motor B all the way one way or the other (e.g. a sliding door)
      buttonTWO();
    }
    if (results.value == 0xFF7A85) { // Button 3 Toggle Motor C all the way one way or the other (e.g. a sliding door)
      buttonTHREE();
    }
    if (results.value == 0xFF10EF) { // Button 4 All Lights Red
      buttonFOUR();
    }
    if (results.value == 0xFF38C7) { // Button 5 All LED's Flicker Yellow etc. 
      buttonFIVE();
    }
    if (results.value == 0xFF5AA5) { // Button 6  
      Serial.println(" Button 6 - Lava ");
      buttonSIX();
    }
    if (results.value == 0xFF42BD) { // Button 7  
      Serial.println(" Button 7 - No Command ");
    }
    if (results.value == 0xFF4AB5) { // Button 8  
      Serial.println(" Button 8 - No Command ");
    }
    if (results.value == 0xFF52AD) { // Button 9  
      Serial.println(" Button 9 - No Command ");
    }



  

    irrecv.resume();  // Receive the next value
  }
    
}
