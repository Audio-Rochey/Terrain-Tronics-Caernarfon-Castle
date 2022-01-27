/*
 * This is based on the door and lights project.
 * It counts down from 10 every time the EQ button is pressed on the remote. The aim is that an entire table would be supported with one remote.
 * 
 * EQ Button has the code: FF906F
 * PLAY/PAUSE has the code: FFC23D
 * 
 * DND Time suggestions at:https://www.dndbeyond.com/forums/dungeons-dragons-discussion/tips-tactics/2551-how-does-time-work-in-d-d?comment=6
 * Combat: round based time.
 * Exploring(dungeons, cities): minutes, hours.
 * Traveling: hours, days.
 * 
 * 
 * This work is based on the Servo for ESP8266 and the IRremoteESP8266: IRrecvDemo 
 * 
 * Dafydd Roche - 6/1/2021
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
 * Keepalive isn't used.
 * 
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <Adafruit_NeoPixel.h>

const String softwareVersion = "V1.0";
const String softwareDate = "6/1/21";     
const String CaernarfonVer = "1p0";
const int keepAlive = D0;// The Keepalive pin for USB Power Banks is D0, but isn't used in this demo
const String keepAlivePin = "D0";

#define LED_PIN    D3
#define LED_COUNT 6


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = D5;

IRrecv irrecv(kRecvPin);

decode_results results;

int ledState = 10;
int greenLEDCount = 0;
int redLEDCount = 0;
int defaultRounds = 10;
int globalBrightness = 127; // start at half max brightness

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(globalBrightness); // 


  for(int i=0; i<LED_COUNT; i++) {
    strip.setPixelColor(i, 0,255,0);
  }
  strip.show(); 

  
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  
  Serial.println("*****");
  delay(100);
  Serial.println("TerrainTronics - Spell Tracker");
  Serial.print("Version ");
  Serial.print(softwareVersion);
  Serial.print(" Date: ");
  Serial.print(softwareDate);
  Serial.print(" Caernarfon HW Version ");
  Serial.println(CaernarfonVer);
  Serial.print("IRrecv: ");
  Serial.println(kRecvPin);
}

void loop() {
  
  
  if (irrecv.decode(&results)) {
  
    // print() & println() can't handle printing long longs. (uint64_t)
    Serial.print("IR Recieve: ");
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    if (results.value == 0xFF906F) { // if the EQ (Decrease by one round) button is pressed.
        
      ledState--;
      if (ledState<0) { ledState=0; }
      greenLEDCount = ledState / 2; // divide the number of rounds remaining by 2. (2 states for the LED's)
      redLEDCount = ledState % 2;  // Anything leftover?
      
      Serial.print("Subtract One. ledState= ");
      Serial.println(ledState);
      Serial.print("Green LED Count: ");
      Serial.println(greenLEDCount);


      
      //Clear Existing lights
      for(int i=0; i<LED_COUNT; i++) {
      strip.setPixelColor(i, 0,0,0);
      }

      // Light up only complete integer numbers in green.
      for(int i=1; i<(greenLEDCount+1); i++) {
      strip.setPixelColor(i, 0,255,0);
      }
      if (redLEDCount) {strip.setPixelColor((greenLEDCount+1), 255,0,0);}
      
      
    }
    if (results.value == 0xFFC23D) { // If the PLAY?PAUSE (RESET) Button is pressed.
      Serial.print("Reset: State now: ");
      Serial.println(ledState);
      ledState = defaultRounds;  
      for(int i=0; i<ledState; i++) {
      strip.setPixelColor(i, 0,255,0);
      }
    }
    if (results.value == 0xFFE01F) { // Arduino Remote Vol- lower the brightness in half.
      globalBrightness = (globalBrightness/2);
      if (globalBrightness < 1 ) { globalBrightness = 1; }
      strip.setBrightness(globalBrightness);
    }

    if (results.value == 0xFFA857) { // Arduino Remote Vol+ Double the brightness.
      globalBrightness = (globalBrightness*2);
      if (globalBrightness > 255) { globalBrightness = 255; }
      strip.setBrightness(globalBrightness);
    }

    
    strip.show();
    
    delay(500);

    irrecv.resume();  // Receive the next value
  }
    
}
