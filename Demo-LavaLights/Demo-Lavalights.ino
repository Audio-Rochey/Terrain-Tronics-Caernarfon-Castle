/*
 * This code can be run on a simple Wemos D1 Mini, but it may be much easier to do so with a Caernarfon Castle board, 
 * as it has pins onboard to connect to a Neopixel strip.  
 * 
 * This code has been drastically simplified from other Caernarfon Castle code.
 * It's job is simple, light up a strip with red (255,0,0) and occasionally ripple an LED or two to a more orangish red.
 * 
 * Credit where credit is due. Adafruit are a store that sells parts for electronics hobbyists. They also made a ton of
 * libraries that can be used in your projects to make driving things like RGB LED's easy.
 * If you do need tools and parts, consider visiting their website. http://www.adafruit.com
 * 
 * Dafydd Roche - 12/2/2021
 * 
 * Wemos D1 mini.
 * Neopixel Data out on D3.
 * 
 * Keepalive isn't used.
 * 
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const String softwareVersion = "V1.0";
const String softwareDate = "12/2/21";     
const String CaernarfonVer = "1p0";
const int keepAlive = D0;// The Keepalive pin for USB Power Banks is D0, but isn't used in this demo
const String keepAlivePin = "D0";

#define LED_PIN    D3
#define LED_COUNT 64
#define NUMPIXELS 64 // How many pixels in your strip?

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int ledState = 0;



void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255)

  for(int i=0; i<NUMPIXELS; i++) { 
  //This sets all pixels to red
  strip.setPixelColor(i, 255,0,0);
  }
  strip.show(); 
  delay(1000);

  
  Serial.begin(115200);
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  
  Serial.println("*****");
  delay(100);
  Serial.println("TerrainTronics Collaboration with Tabletop Witchcraft");
  Serial.print("Version ");
  Serial.print(softwareVersion);
  Serial.print(" Date: ");
  Serial.print(softwareDate);
  Serial.print(" Caernarfon HW Version ");
  Serial.println(CaernarfonVer);
  
}

void loop() {
  if (ledState == 0) {
    for(int i=0; i<NUMPIXELS; i++) { 
     int j = random(0,63); // 10 in 64 chance that there will be a flicker that isn't pure red.
     if (j < 10) {
     //Colors are arrange Pixel, R, G, B.
     strip.setPixelColor(i, 255,random(0,30),random(0,3));
      }
      else {
     strip.setPixelColor(i, 255,0,0);  
     }
    }
      strip.show();  
    delay(random(100,250));
  }
  
     
}
