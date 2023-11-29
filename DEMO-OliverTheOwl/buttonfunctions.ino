#include "buttonfunctions.h"


void ledUpdate(int ledState) // runs on every loop
{
  int currLED;
  switch (ledState) {
    case 0: // Mute LED's
    for (currLED = 0; currLED <= LED_COUNT; currLED++) {
      strip.setPixelColor(currLED, 0, 0, 0);
    }
        strip.show();
    break;
    case 1: // LED's All Red
    for (currLED = 0; currLED <= LED_COUNT; currLED++) {
      strip.setPixelColor(currLED, 255, 0, 0);
    }
        strip.show();
    break;
    case 2: // Flame Flicker - no action here as it's handled in the main loop. ledState already changed.
        strip.show();   
    break;
  }
}

void buttonZERO() // set ledState to 0
{
  Serial.println("All LED's OFF - FF6897");
  ledState = 0;
  ledUpdate(0);
}


void buttonONE() // toggle motor #1.
{
//    Serial.println("DOOR TOGGLE M1 ");  
//    if (trapOneState == 2 ){ trapOneState = 0;}
//    Serial.println(trapOneState);
//      switch (trapOneState) {
//    case 0:    // RESET THE TRAP
//      Serial.println("OPEN ");
//      for (trapOnePos = 0; trapOnePos <= 180; trapOnePos += 2) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//        trapOne.write(trapOnePos);              // tell servo to go to trapOnePosition in variable 'trapOnePos'
//      delay(25);  }                     // waits 15ms for the servo to reach the trapOnePosition
//      break;
//    case 1:    // GATE 1 Down
//      Serial.println("CLOSED ");
//      for (trapOnePos = 180; trapOnePos >= 0; trapOnePos -= 2) { // goes from 180 degrees to 0 degrees
//      trapOne.write(trapOnePos);              // tell servo to go to trapOnePosition in variable 'trapOnePos'
//      delay(25); }                       // waits 15ms for the servo to reach the trapOnePosition
//      break;
//      }
//    trapOneState++;
}

void buttonTWO() // toggle motor #2.
{
//    Serial.println("DOOR TOGGLE M2 ");  
//    if (trapTwoState == 2 ){ trapTwoState = 0;}
//    Serial.println(trapTwoState);
//      switch (trapTwoState) {
//    case 0:    // RESET THE TRAP
//      Serial.println("OPEN ");
//      for (trapTwoPos = 0; trapTwoPos <= 180; trapTwoPos += 2) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//        trapTwo.write(trapTwoPos);              // tell servo to go to trapTWOPosition in variable 'trapTWOPos'
//      delay(25);  }                     // waits 15ms for the servo to reach the trapTWOPosition
//      break;
//    case 1:    // GATE 1 Down
//      Serial.println("CLOSED ");
//      for (trapTwoPos = 180; trapTwoPos >= 0; trapTwoPos -= 10) { // goes from 180 degrees to 0 degrees
//      trapTwo.write(trapTwoPos);              // tell servo to go to trapOnePosition in variable 'trapOnePos'
//      delay(25); }                       // waits 15ms for the servo to reach the trapOnePosition
//      break;
//      }
//    trapTwoState++;
}

void buttonTHREE() // toggle motor #3.
{
//    Serial.println("DOOR TOGGLE M3 ");  
//    if (trapThreeState == 2 ){ trapThreeState = 0;}
//    Serial.println(trapThreeState);
//      switch (trapThreeState) {
//    case 0:    // RESET THE TRAP
//      Serial.println("OPEN ");
//      for (trapThreePos = 0; trapThreePos <= 180; trapThreePos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//        trapThree.write(trapThreePos);              // tell servo to go to trapTWOPosition in variable 'trapTWOPos'
//      delay(25);  }                     // waits 15ms for the servo to reach the trapTWOPosition
//      break;
//    case 1:    // GATE 1 Down
//      Serial.println("CLOSED ");
//      for (trapThreePos = 180; trapThreePos >= 0; trapThreePos -= 1) { // goes from 180 degrees to 0 degrees
//      trapThree.write(trapThreePos);              // tell servo to go to trapOnePosition in variable 'trapOnePos'
//      delay(25); }                       // waits 15ms for the servo to reach the trapOnePosition
//      break;
//      }
//    trapThreeState++;
}

void buttonFOUR() // set ledState to 1
{
  Serial.println("All LEDS RED - FF10EF");
  ledState = 1;
  ledUpdate(ledState);
}

void buttonFIVE() // set ledState to 2
{
  Serial.println("All LED's BLUE - FF38C7");
  ledState = 4;
  for (int currLED = 0; currLED <= LED_COUNT; currLED++) {
      strip.setPixelColor(currLED, 0, 255, 0);
    }
        strip.show();
}

void buttonSIX() // set ledState to 2
{
  Serial.println("All Green");
  ledState = 4;
  for (int currLED = 0; currLED <= LED_COUNT; currLED++) {
      strip.setPixelColor(currLED, 0, 0, 0, 255);
    }
        strip.show();
}
