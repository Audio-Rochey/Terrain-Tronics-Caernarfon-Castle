/*
 * This code can be run on a simple Wemos D1 Mini, but it may be much easier to do so with a Caernarfon Castle board,
 * as it has pins onboard to connect to a Neopixel strip.  
 *
 * This code has been drastically simplified from other Caernarfon Castle code.
 *
 * Credit where credit is due. Adafruit are a store that sells parts for electronics hobbyists. They also made a ton of
 * libraries that can be used in your projects to make driving things like RGB LED's easy.
 * If you do need tools and parts, consider visiting their website. http://www.adafruit.com
 *
 * Video up at: https://www.youtube.com/watch?v=cYuFJSO46kM
 *
 * Wemos D1 mini.
 * Neopixel Data out on D3.
 *
 * Keepalive isn't used.
 *
 */
 
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
     #include <ESP8266WiFi.h>
 
const String softwareVersion = "V1.0";
const String softwareDate = "15/1/23";    
const String CaernarfonVer = "1p0";
const int keepAlive = D0;// The Keepalive pin for USB Power Banks is D0, but isn't used in this demo
const String keepAlivePin = "D0";
 
#define LED_PIN    D3
#define LED_COUNT 128 // How many pixels in your strip?
#define NUMPIXELS 128 // How many pixels in your strip?
 
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
 
int ledState = 0;
int stepDirection = 1; // 1 is climbing, -1 is falling
int Brightness = 0;
int flickerDelay = 0;
 
void setup() {
  WiFi.mode(WIFI_OFF);    //This also works to save power.
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255)
 
  for(int i=0; i<NUMPIXELS; i++) {
  //This sets all pixels to all on.
  strip.setPixelColor(i, 0,0,255);
  }
  strip.show();
  delay(1000);
 
 
  Serial.begin(115200);
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
 
  Serial.println("*****");
  delay(100);
  Serial.println("TerrainTronics Collaboration with Tabletop Witchcraft - Mounstain");
  Serial.print("Version ");
  Serial.print(softwareVersion);
  Serial.print(" Date: ");
  Serial.print(softwareDate);
  Serial.print(" Caernarfon HW Version ");
  Serial.println(CaernarfonVer);
 
 
 
 strip.setBrightness(0); // start brightness at 0.
}
 
void loop() {
  // define 3 states of LED.... Off, lightening strike, flicker down the line.
  Serial.println(ledState);
  switch (ledState) {
    case 0: //  ledState is Zero, when things are dark. "Case" is used to test ledState when 0. A bit like an if-then statement.
      for(int i=0; i<NUMPIXELS; i++) {  // reset all LED brightnesses to zero.
      strip.setPixelColor(i, 0,0,0); // all leds off.
      }
      flickerDelay = random(4000,8000); // set delay between 4 and 8 seconds of darkness.
      ledState = random(1,6); // randomize the chance of a double strike.
      if (ledState < 4) { ledState = 2; } // if that random chance is less than 4, then do a double strike. (ledState2)
      if (ledState == 4) { ledState = 1; } // if it's 4 (1 in 4 chance) do a single strike.
      if (ledState == 5) { ledState = 3; }; // if it's a 5 do a lightening strike.
      break;
    case 1: // Single flash
      for(int i=0; i<NUMPIXELS; i++) {
      strip.setPixelColor(i, 255,255,255); // all leds on.
      }
      flickerDelay = random(20,100); // set delay between 20mS and 100mS of light.
      ledState = 0; // go dark after this.
      break;
    case 2: // Double flash
      for(int i=0; i<NUMPIXELS; i++) {
      strip.setPixelColor(i, 255,255,210); // all leds on. the 210 gives it a tint.
      }
      strip.show();  // now update the WS2811 LED strip
      delay(20); // wait 20 miliseconds wiht them on.
      for (int i=0; i<NUMPIXELS; i++) { // now switch all off again,
      strip.setPixelColor(i, 0,0,0); // all leds off.
      }
      strip.show();  // now update the WS2811 LED strip
      delay(100); // dead time of darkness in the double strike.
       for(int i=0; i<NUMPIXELS; i++) {
      strip.setPixelColor(i, 200,200,150); // all leds on.
      }
      strip.show();  // now update the WS2811 LED strip
      flickerDelay = random(20,100); // set delay between 20mS and 100mS of light - this makes the second strike random in time.
      ledState = 0; // go dark after this.
      break;
    case 3: // Lightening Streak Accross the Sky
      strip.clear();
      strip.show();  // now update the WS2811
      for(int i=0; i<NUMPIXELS; i++) { // This loop runs for each LED in your strip, addressed as 0 through 128. (128 isn't fixed)
        // 5 LED's are shown at any one time. The middle led is tracked with "i".
        // LED "i-2" is barely lit up, Led "i-1" is mid light, and LED "i" is max brightness. 
        // Same then goes for i+1 and i+2.
        // Each of these are updated and light up, then the whole loop starts again, but this time 1 is added to i
        // moving the pattern down one led int he strip.
      strip.clear();
      strip.setPixelColor((i-2), 32,32,10); // one before middle blue
      strip.setPixelColor((i-1), 125,125,105); // one before middle blue
      strip.setPixelColor(i, 255,255,210); // all leds on.
      strip.setPixelColor((i+1), 125,125,105); // one after middle blue
      strip.setPixelColor((i+2), 32,32,10); // one after m blue
      flickerDelay = random(250,500); // set delay between 20mS and 100mS of light.
      strip.show();  // now update the led strip.
      } // loop around until i=128
      strip.clear();
      ledState = 0; // go dark after this.
      break;
 
      break;
 
  }
 
    strip.setBrightness(254); // start brightness at 0
    strip.show();  // now update the WS2811
    delay(flickerDelay); // wait 10 miliseconds.
 
 
 
 
  }
  
