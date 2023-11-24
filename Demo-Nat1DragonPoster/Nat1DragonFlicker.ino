/*
* This code is heavily influenced by the simple Balrog Build by Michael at Nat1.
* Main change to make is that the flicker should only run when the reed swith is pulled low.
* 
* The switch needed to monitor is D6.

* This code has been drastically simplified from other Caernarfon Castle code.
* it takes advantage of the WS2811 LED driver that's on a Caernarfon board.
* the WS2811 takes a single data input and outputs for 3 LED's. These would typically be a Red, Green and Blue led.
* In this case, for the balrog, they were connected to 3 Flexileds - all of them yellow.
*
* Credit where credit is due. Adafruit are a store that sells parts for electronics hobbyists. They also made a ton of
* libraries that can be used in your projects to make driving things like RGB LED's easy.
* If you do need tools and parts, consider visiting their website. http://www.adafruit.com
*
* The code in void Setup() runs once on powerup. It tells the Wemos D1 what to do with various pins, and 
* Wemos D1 mini. It also sets parameters for the library used to drive the WS2811. (termed "neopixel).
* Neopixel Data out on D3.
*
* Keepalive isn't used.
*
*/

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const String softwareVersion = "V1.1";
const String softwareDate = "11/17/23"; 
const String CaernarfonVer = "1p0";
const int keepAlive = D0;// The Keepalive pin for USB Power Banks is D0, but isn't used in this demo
const String keepAlivePin = "D0";

#define LED_PIN D3
#define LED_COUNT 1
#define NUMPIXELS 2 // How many pixels in your strip?

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int ledState = 1;




void setup() {
strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
strip.show(); // Turn OFF all pixels ASAP
strip.setBrightness(255); // Set BRIGHTNESS (max = 255)

for(int i=0; i<NUMPIXELS; i++) {
//This sets all pixels to all on.
strip.setPixelColor(i, 255,255,255);
}
strip.show();
delay(1000);

Serial.begin(115200);
while (!Serial) // Wait for the serial connection to be establised.
delay(50);
Serial.println();
Serial.println("*****");
delay(100);
Serial.println("TerrainTronics Collaboration with Nat1 (Michael)");
Serial.print("Version ");
Serial.print(softwareVersion);
Serial.print(" Date: ");
Serial.print(softwareDate);
Serial.print(" Caernarfon HW Version ");
Serial.println(CaernarfonVer);


pinMode(12, INPUT_PULLUP);
}

void loop() {
Serial.println(digitalRead(D6));
if (digitalRead(D6) == 0) {ledState = 0;} // If the reed switch has a magnet next to it, make "ledState = 0"
if (digitalRead(D6) == 1) {ledState = 1;}

if (ledState == 1) {
strip.setPixelColor(0, 0,0,0); // take the 3 random values and push them to into the right place in memory
strip.show(); // now update the WS2811
delay(500);

}

if (ledState == 0) {
int led1 = random(80,255); // randomize a brightness between 80 and 255. 255 is full brightness
int led2 = random(80,238); // randomize a brightness between 80 and 238 -- this is the middle one behind the balrogs head
int led3 = random(80,255); // randomize a brightness between 80 and 255.
strip.setPixelColor(0, led1,led2,led3); // take the 3 random values and push them to into the right place in memory
strip.show(); // now update the WS2811
delay(random(10,200)); // wait for any amount of time between 10mS and 200mS.
/*
If I had more time, what would I have done?
- I would have had everything on a 10mS update rate, and had the value go up, or go down with each update. (that would have created more "swelling").
- Target brightness would be set randomly, then the value would be interpolated up and down to the target.
- Updates would be done randomly, per LED. This would have been done using the millis() method.
*/
}}
