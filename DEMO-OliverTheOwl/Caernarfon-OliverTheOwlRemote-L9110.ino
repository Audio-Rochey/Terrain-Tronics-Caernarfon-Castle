/*
 * 1/24/2022 -- building upon the initial version.
 * This code uses 2 external files within arduino and will define the functionalty for almost every button the remote.
 * Here are the requirements:https://github.com/Audio-Rochey/Terrain-Tronics-Caernarfon-Castle/blob/main/Demo-MultiRemote/Requirements.txt
 * 
 * I followed this video to learn how to split the files in arduino: https://www.youtube.com/watch?v=BdstuZP6l5E
 * However, rather than namign files .cpp, i used INO.
 * 
 * This is the work done for Oliver the Owl (the actual NPC himself, not the room he's in!)
 * Wemos D1+ Mini +_ Caernarfon Castle, then Servo signal 1 and 2 are connected to the inputs to a 
 * 
 * Description of states:
 * ledState Zero is All Lights Off
 * ledState One is all Red.
 * ledState Two is flicker. (which gets updated in the main loop.
 * ledState Three is lava
 * ^^^ this was previously used to toggle the states.
 * 
 * trapOneState between 0 and 1 used to 
 *  * This work is based on the Servo for ESP8266 and the IRremoteESP8266: IRrecvDemo 
 * 
 * Wifi library is used to put it to sleep ASAP. Addd Feb 1st 2022. * 
 * 
 * Dafydd Roche - 2/1/2022
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
 * 
 * UPDATES IN V2
 * - Handle REPEAT (0xFFFFFFF) commands
 *      When the (results.value == 0xFFFFFFFFFFFFFFFF) replace results.value with lastCommand.
 *      else, you have a decent IR recieve - make it the "lastCommand".
 *      Toggle a bolean if it's a repeat, so it can be looked at by any function.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h> // added Feb 1st 2022
// Required for LIGHT_SLEEP_T delay mode
extern "C" {
#include "user_interface.h"
}


#include "buttonfunctions.h" // put the functions for each button in a separate file.

int trapOneState;
int trapOnePos;
int trapTwoState;
int trapTwoPos;
int trapThreeState;
int trapThreePos;

bool OgmoreState;

const String softwareVersion = "V1";
const String softwareDate = "3/22/2022 / checked 11/28/2023";     
const String CaernarfonVer = "1p0";
const int keepAlive = D0;// The Keepalive pin for USB Power Banks is D0, but isn't used in this demo
const String keepAlivePin = "D0";

#define LED_PIN    D3
#define LED_COUNT 51 // remember that there's one on the board. (A WS2812 chip to be exact)
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);  // - for WS2812
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);


// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = D5;

IRrecv irrecv(kRecvPin);

decode_results results;

int ledState = 0;
unsigned long ledPreviousMillis = 0;        // will store last time LED was updated
long flickerLedInterval = 0;                // this will be updated with every flicker.

unsigned long lavaPreviousMillis = 0;        // will store last time LED was updated
long lavaLedInterval = 0;                // this will be updated with every flicker.


int globalBrightness = 127; // start at half max brightness


// sleep counter numbers
unsigned long sleepConstantMillis = 7200000;        // lights will go to sleep after 2 hours seconds to save power. (1 hour = 3600000 timer ticks)
unsigned long sleepLastChangeMillis ;             // Variable that tracks when the system was last interacted with.

unsigned long lastCommand ;  // define a variable for the previous decent command that isn't a repeat
bool repeatedCommand = 0; // Repeated command (0xFFFFFFFFFFFFFFFF) sets this to 1.

void setup() {
  WiFi.disconnect();     // We're not using Wifi, so lets disable it to save power.
  WiFi.forceSleepBegin();
  delay(1); //For some reason the modem won't go to sleep unless you do a delay.


  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(globalBrightness); // 

  strip.setPixelColor(0, random(146,164), random(90,109), 0);
  strip.setPixelColor(1, random(146,164), random(90,109), 0);
  strip.setPixelColor(2, random(146,164), random(90,109), 0);
  strip.setPixelColor(3, random(146,164), random(90,109), 0);
  strip.show(); 


  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  delay(1000);
  Serial.println("*****");
  delay(100);
  Serial.println("TerrainTronics Demo - Oliver the Owl");
  Serial.print("Version ");
  Serial.print(softwareVersion);
  Serial.print(" Date of Compile ");
  Serial.print(softwareDate);
  Serial.print(" Caernarfon HW Version ");
  Serial.println(CaernarfonVer);
  Serial.print("IRrecv: ");
  Serial.println(kRecvPin);
  Serial.print("LED Count: ");
  Serial.println(LED_COUNT);
  pinMode(D6, OUTPUT);//Set the Servo1,2,3 on Caernarfon board as outputs.
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

    delay(500);


  sleepLastChangeMillis = millis();

  //Just making it turn on poweron.
  digitalWrite(D7, LOW);
  digitalWrite(D6, LOW);

  
}

void callback() {
  Serial.println("WAKE FROM IR!");
  irrecv.enableIRIn(); // Reconfigures timers etc on the device to accept IR (e.g. timer to 50uS to sample the input etc)

}

void loop() {
  unsigned long currentMillis = millis();



  // Checks if any led's have been pressed for the last sleepConstantMillis. If so, switch the LED's off.
  // sleepLastChangeMillis is updated every time an IR message is recieved.
  if (currentMillis - sleepLastChangeMillis >= sleepConstantMillis) {
      ledState = 0;
      ledUpdate(0);
      Serial.println("Auto Lights Off");


      // This code (added Feb 2022). It puts the device to sleep and wakes ut up if there's any activity on the IR recieve pin.
      // This then runs the callback function - which reconfigures the timers etc to accept IR.
      // That means that the first time you push an IR button, you wake the device, but no legitimate command. Push the button again and it'll wake up.
      gpio_pin_wakeup_enable(GPIO_ID_PIN(kRecvPin), GPIO_PIN_INTR_LOLEVEL);
      wifi_set_opmode(NULL_MODE);
      wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
      wifi_fpm_open();
      wifi_fpm_set_wakeup_cb(callback);
      wifi_fpm_do_sleep(0xFFFFFFFF);
      delay(100);

     WiFi.disconnect();     // After it comes back out of deep sleep, lets disconnect the wifi etc to make sure we're getting lower power
     WiFi.forceSleepBegin();
     delay(1); //For some reason the modem won't go to sleep unless you do a delay.
  }
  
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
      if (j < 6) {
        strip.setPixelColor(currLED, 150, random(0,30),random(0,3));
    
      }
      else {      strip.setPixelColor(currLED, 255, 0, 0);
    }
    }
    strip.show();   
    lavaLedInterval = random(250,500);
  }
  
  if (irrecv.decode(&results)) {

    // ACTIVITY! RESET THE TIMER!
    sleepLastChangeMillis = millis();
  
    // print() & println() can't handle printing long longs. (uint64_t)
    Serial.print("IR Recieve: ");
    serialPrintUint64(results.value, HEX);
    Serial.println("");


    //delay(150); // add a delay for debounce (stops repeats)
    
    if (results.value == 0xFFFFFFFFFFFFFFFF) { // if it IS the repeat.
      repeatedCommand = 1; // potentially used in each function.
      Serial.println("Repeated");
      results.value = lastCommand; // replaces the FFFF's wiht the last command.
      Serial.print("FFF's replaced with: ");
      serialPrintUint64(results.value, HEX);
      Serial.println("");
    }
    else{ // is a legit command.
      repeatedCommand = 0; // potentially used in each function.
      lastCommand = results.value; // writes the good command to the lastCommand, in case the next one is a repeat.
    }
    
    if (results.value == 0xFF02FD) { // Rotate the MOtor in 1 direction for 250mS
      digitalWrite(D6, HIGH);
      digitalWrite(D7, LOW);
      delay(250);
      digitalWrite(D6, LOW);  
      
    }

    if (results.value == 0xFF22DD) { // Rotate the MOtor in the other direction direction for 250mS
      digitalWrite(D7, HIGH);
      digitalWrite(D6, LOW);
      delay(250);
      digitalWrite(D7, LOW);  

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
    if (results.value == 0xFF42BD) { // Button 7  - can be used to switch an Ogmore USB swithc etc -- but not used on Oliver.
      Serial.println(" Button 7 - No Command ");
      digitalWrite(D8, OgmoreState);
      OgmoreState = !OgmoreState;
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
