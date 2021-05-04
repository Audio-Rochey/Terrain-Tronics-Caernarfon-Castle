

// FIRST REV OF CODE.
// Runs on an Arduino Nano
// Uploaded on 5/3/2021

// #include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#include <INA226.h>
INA226 ina;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define LED_PIN    3

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 2
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);





void setup() {

  
  // Set up the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize with the I2C addr 0x3D if not working use 0x3C (for the 128x64)
  display.setTextColor(WHITE);

    strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // Config the IN226
  ina.begin();
  ina.configure(INA226_AVERAGES_1, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
  ina.calibrate(0.1, 4);

  delay(1);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Ref V & I");
  display.setTextSize(1);
  display.println("Shunt current: ");
  display.setTextSize(2);
  display.print(ina.readShuntCurrent(), 2);
  display.println(" A");
  display.display();
  delay(2 000); 

  

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  float kaCurrent = ina.readShuntCurrent();
  delay(800);                       // wait for a second


  
  delay(1);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("TESTING KEEPALIVE");
  display.setTextSize(1);
  display.println("Shunt current: ");
  display.setTextSize(2);
  display.print(kaCurrent);
  display.println(" A");
  if(kaCurrent > 0.07 ){
    display.invertDisplay(true);
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    }
  else
    {
    display.invertDisplay(false);
    }
  display.display();

  delay(3000);                       // wait for a second
  
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW 
  
}
void loop(){

   // draw scrolling text
  delay(1);
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Analog Read V1.0");
  display.setTextColor(BLACK, WHITE);
  display.setCursor(20,10);
  display.println("A1");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(80,10);
  display.println("A2");
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setTextSize(2);
  int sensorValuea1 = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltagea1 = sensorValuea1 * (5.0 / 1023.0);
  // print out the value you read:
  display.print(voltagea1); display.print(" ");
  int sensorValuea2 = analogRead(A2);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):                               
  float voltagea2 = sensorValuea2 * (5.0 / 1023.0);
  // print out the value you read:
  display.print(voltagea2); display.print("V");
  if(sensorValuea1 >= 409 && sensorValuea1 <= 613 && sensorValuea2 >= 409 && sensorValuea2 <= 613){
    display.invertDisplay(true);
    }
  else
    {
    display.invertDisplay(false);
    }
  
  display.display();
  

  strip.setPixelColor(0, strip.Color(255, 255, 255));
  strip.setPixelColor(1, strip.Color(255, 255, 255));
  strip.show();
  delay(100);
}
