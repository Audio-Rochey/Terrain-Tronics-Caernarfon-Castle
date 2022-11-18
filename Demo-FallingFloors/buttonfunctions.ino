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
    case 4: //
      for (currLED = 0; currLED <= (LED_COUNT+1); currLED++) {
      strip.setPixelColor(currLED, floorArray [currLED][1],floorArray [currLED][2], floorArray [currLED][3]);
  }
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
    Serial.println("DOOR TOGGLE M1 ");  
    if (trapOneState == 2 ){ trapOneState = 0;}
    Serial.println(trapOneState);
      switch (trapOneState) {
    case 0:    // RESET THE TRAP
      Serial.println("OPEN ");
      for (trapOnePos = 0; trapOnePos <= 180; trapOnePos += 2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        trapOne.write(trapOnePos);              // tell servo to go to trapOnePosition in variable 'trapOnePos'
      delay(25);  }                     // waits 15ms for the servo to reach the trapOnePosition
      break;
    case 1:    // GATE 1 Down
      Serial.println("CLOSED ");
      for (trapOnePos = 180; trapOnePos >= 0; trapOnePos -= 2) { // goes from 180 degrees to 0 degrees
      trapOne.write(trapOnePos);              // tell servo to go to trapOnePosition in variable 'trapOnePos'
      delay(25); }                       // waits 15ms for the servo to reach the trapOnePosition
      break;
      }
    trapOneState++;
}

void buttonTWO() // toggle motor #2.
{
    Serial.println("DOOR TOGGLE M2 ");  
    if (trapTwoState == 2 ){ trapTwoState = 0;}
    Serial.println(trapTwoState);
      switch (trapTwoState) {
    case 0:    // RESET THE TRAP
      Serial.println("OPEN ");
      for (trapTwoPos = 0; trapTwoPos <= 180; trapTwoPos += 2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        trapTwo.write(trapTwoPos);              // tell servo to go to trapTWOPosition in variable 'trapTWOPos'
      delay(25);  }                     // waits 15ms for the servo to reach the trapTWOPosition
      break;
    case 1:    // GATE 1 Down
      Serial.println("CLOSED ");
      for (trapTwoPos = 180; trapTwoPos >= 0; trapTwoPos -= 10) { // goes from 180 degrees to 0 degrees
      trapTwo.write(trapTwoPos);              // tell servo to go to trapOnePosition in variable 'trapOnePos'
      delay(25); }                       // waits 15ms for the servo to reach the trapOnePosition
      break;
      }
    trapTwoState++;
}

void buttonTHREE() // toggle motor #3.
{
    Serial.println("DOOR TOGGLE M3 ");  
    if (trapThreeState == 2 ){ trapThreeState = 0;}
    Serial.println(trapThreeState);
      switch (trapThreeState) {
    case 0:    // RESET THE TRAP
      Serial.println("OPEN ");
      for (trapThreePos = 0; trapThreePos <= 180; trapThreePos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        trapThree.write(trapThreePos);              // tell servo to go to trapTWOPosition in variable 'trapTWOPos'
      delay(25);  }                     // waits 15ms for the servo to reach the trapTWOPosition
      break;
    case 1:    // GATE 1 Down
      Serial.println("CLOSED ");
      for (trapThreePos = 180; trapThreePos >= 0; trapThreePos -= 1) { // goes from 180 degrees to 0 degrees
      trapThree.write(trapThreePos);              // tell servo to go to trapOnePosition in variable 'trapOnePos'
      delay(25); }                       // waits 15ms for the servo to reach the trapOnePosition
      break;
      }
    trapThreeState++;
}

void buttonFOUR() // set ledState to 1
{
  Serial.println("All LEDS RED - FF10EF");
  ledState = 1;
  ledUpdate(ledState);
}

void buttonFIVE() // set ledState to 2
{
  Serial.println("All LED's Flame - FF38C7");
  ledState = 2;
  ledUpdate(ledState);
}

void buttonSIX() // set ledState to 2
{
  Serial.println("LAVA");
  ledState = 3;
  ledUpdate(ledState);
}

void buttonSEVEN() // set ledState to 4
{
  eachStep();
//  Serial.println("LOSE A BLOCK");
//  ledState = 4;
//  int dyingBlock = random(1,(LED_COUNT+1)/2);
//  floorArray [dyingBlock*2][1]=0;
//  floorArray [dyingBlock*2][2]=0;
//  floorArray [dyingBlock*2][3]=0;
//  floorArray [(dyingBlock*2)-1][1]=0;
//  floorArray [(dyingBlock*2)-1][2]=0;
//  floorArray [(dyingBlock*2)-1][3]=0;
//  for (currLED = 0; currLED <= (LED_COUNT+1); currLED++) {
//      strip.setPixelColor(currLED, floorArray [currLED][1],floorArray [currLED][2], floorArray [currLED][3]);
//  }
//  strip.show(); 
//  ledUpdate(ledState);
}

void buttonEIGHT()
{
  ledState = 4;
  removeABadStep();
  ledUpdate(ledState);
}

void buttonNINE() // set ledState to 4
{
  generateGS();
  Serial.println("Reset 5x5 Array");
  currentRow = 0;
  ledState = 4;
  //Initialize all boxes blue
  for (currLED = 0; currLED <= (LED_COUNT+1); currLED++) {
     // floorArray [currLED][1]=219; // yellow
     // floorArray [currLED][2]=175; // yellow
     // floorArray [currLED][3]=15;  // yellow
      floorArray [currLED][1]=leifsRed; // Diablo Blue
      floorArray [currLED][2]=leifsGreen; // Diablo Blue
      floorArray [currLED][3]=leifsBlue;  // Diablo Blue
  }
  for (currLED = 0; currLED <= (LED_COUNT+1); currLED++) {
      strip.setPixelColor(currLED, floorArray [currLED][1],floorArray [currLED][2], floorArray [currLED][3]);
  }

  
  strip.show(); 
  ledUpdate(ledState);
}




// Leifs Game Mode Functions


void generateGS()
{
  Serial.println("Generating Random Path");
  int NextGSLow = 0;
  int NextGSHigh = 5;
  for (byte i = 0; i < 5; i = i + 1) {
    GS[i] = random(NextGSLow,NextGSHigh);
    Serial.print(GS[i]);
    Serial.print(", ");
    if (GS[i] == 0) {
    NextGSLow = 0;
    }
    else NextGSLow = GS[i]-1;
    if (GS[i] == 4) {
    NextGSHigh = 4;
    }
    else NextGSHigh = GS[i]+2;
  }
Serial.println();
}


void showGSPath()
{
    //Pick out the ones to remove as path
  for (byte i = 0; i < 5; i = i + 1) {

    int PixelToLight = ((i*5)+GS[i]+1); // 
    Serial.print(PixelToLight);
    Serial.print(", ");
    floorArray [PixelToLight*2][1]=0;
    floorArray [PixelToLight*2][2]=0;
    floorArray [PixelToLight*2][3]=0;
    floorArray [(PixelToLight*2)-1][1]=0;
    floorArray [(PixelToLight*2)-1][2]=0;
    floorArray [(PixelToLight*2)-1][3]=0; 
  }
  for (currLED = 0; currLED <= (LED_COUNT+1); currLED++) {
      strip.setPixelColor(currLED, floorArray [currLED][1],floorArray [currLED][2], floorArray [currLED][3]);
  }
}


void eachStep() 
{
  // typically happens when you take a step. Need to update floorArray to remove all on that row
  // and add the current step. Also need to only show the options ahead.
    
    Serial.print("Current Row: ");
    Serial.println(currentRow);
    
    //DARKEN the ROW YOU ARE NOW ON (next step, except for the Good Step)
    for (byte i = 0; i < 10; i = i + 1) {
    int PixelToDark =  ((currentRow*5*2)+i+1); // 
    //Serial.print(PixelToDark);
    //Serial.print(", ");
    floorArray [PixelToDark][1]=0;
    floorArray [PixelToDark][2]=0;
    floorArray [PixelToDark][3]=0;
    }

    Serial.println();

    //Brighten the Step you are on.
    // currentRow*5 gives the LED offset
    // GS[currentRow] gives the location in the row you are on.
    // +1 to offset for the first LED driver on Caernarfon board.
    
    int PixelToLight = ((currentRow*5)+(GS[currentRow])+1); // 
    //Serial.print(PixelToLight);
    //Serial.print(", ");

    floorArray [PixelToLight*2][1]=leifsRed;
    floorArray [PixelToLight*2][2]=leifsGreen;
    floorArray [PixelToLight*2][3]=leifsBlue;
    floorArray [(PixelToLight*2)-1][1]=leifsRed;
    floorArray [(PixelToLight*2)-1][2]=leifsGreen;
    floorArray [(PixelToLight*2)-1][3]=leifsBlue;

    // Now wipe the row ahead
    for (byte i = 0; i < 10; i = i + 1) {
    int PixelToDark =  (((currentRow+1)*5*2)+i+1); // 
    //Serial.print(PixelToDark);
    //Serial.print(", ");
    floorArray [PixelToDark][1]=0;
    floorArray [PixelToDark][2]=0;
    floorArray [PixelToDark][3]=0;
    }
    
    // and light up the options in front.
    if (GS[currentRow] > 0){   // Checks that you aren't on the edge.   
    PixelToLight = (((currentRow+1)*5)+(GS[currentRow])); // 
    //Serial.print(PixelToLight);
    //Serial.print(", ");
    floorArray [PixelToLight*2][1]=leifsRed;
    floorArray [PixelToLight*2][2]=leifsGreen;
    floorArray [PixelToLight*2][3]=leifsBlue;
    floorArray [(PixelToLight*2)-1][1]=leifsRed;
    floorArray [(PixelToLight*2)-1][2]=leifsGreen;
    floorArray [(PixelToLight*2)-1][3]=leifsBlue;
    }
    PixelToLight = (((currentRow+1)*5)+(GS[currentRow])+1); // 
    //Serial.print(PixelToLight);
    //Serial.print(", ");
    floorArray [PixelToLight*2][1]=leifsRed;
    floorArray [PixelToLight*2][2]=leifsGreen;
    floorArray [PixelToLight*2][3]=leifsBlue;
    floorArray [(PixelToLight*2)-1][1]=leifsRed;
    floorArray [(PixelToLight*2)-1][2]=leifsGreen;
    floorArray [(PixelToLight*2)-1][3]=leifsBlue;
    PixelToLight = (((currentRow+1)*5)+(GS[currentRow])+2); // 
    //Serial.print(PixelToLight);
    //Serial.print(", ");
    floorArray [PixelToLight*2][1]=leifsRed;
    floorArray [PixelToLight*2][2]=leifsGreen;
    floorArray [PixelToLight*2][3]=leifsBlue;
    floorArray [(PixelToLight*2)-1][1]=leifsRed;
    floorArray [(PixelToLight*2)-1][2]=leifsGreen;
    floorArray [(PixelToLight*2)-1][3]=leifsBlue;



    // OUTPUT THE floorArray
  for (currLED = 0; currLED <= (LED_COUNT+1); currLED++) {
      strip.setPixelColor(currLED, floorArray [currLED][1],floorArray [currLED][2], floorArray [currLED][3]);
  }
    
    currentRow = currentRow+1;
    if (currentRow == 5) {
      currentRow = 4;
    }

    strip.show(); 
    ledUpdate(ledState);
        
  

  
}

void removeABadStep()
{
  // HOW THE HELL AM I GOING TO DO THIS????
    
    // LED Locations.
    // Current Good Row Location is: ((currentRow*5)+(GS[currentRow])+1); //
    // Next Row "3" is centered around:  (((currentRow+1)*5)+(GS[currentRow])+1); //
    // Actual Good next Row Location is: (((currentRow+1)*5)+(GS[currentRow+1])+1);
    // Randomize 1 of 3, if it's the same as GoodNextRow, then Randomize again.
    //
    // example.
    // NextRow3Center = (((currentRow+1)*5)+(GS[currentRow])+1);    // e.g. spot 17
    // randomloss = random((NextRow3Center-1),(NextRow3Center+1));  //eg output should be random between 16 and 18. 
    // ActualGoodNextLocation =  (((currentRow+1)*5)+(GS[currentRow+1])+1);
    // If (randomloss == ActualGoodNextLocation) {Randomize again;
    // 
    //
    Serial.println("Remove one of the blocks ahead!");

    
    
    if (currentRow == 0){
      // clear the row then light up the correct one, and two next to it. (takes 5 to 3)
      // 
      // Now wipe the row ahead
      for (byte i = 0; i < 10; i = i + 1) {
      int PixelToDark =  (i+1); // 
      floorArray [PixelToDark][1]=0;
      floorArray [PixelToDark][2]=0;
      floorArray [PixelToDark][3]=0;
      }

      // Now light up the good one +1 and -1
      // GS[0] is the good one.
      if (GS[0] < 2){
        for (byte i = 0; i < 6; i = i + 1) {
        int PixelToLight =  (i+1); // 
        floorArray [PixelToLight][1]=leifsRed;
        floorArray [PixelToLight][2]=leifsGreen;
        floorArray [PixelToLight][3]=leifsBlue;
      }
      }
      else if (GS[0] == 2) {
        // light up the middle 3
        for (byte i = 2; i < 8; i = i + 1) {
        int PixelToLight =  (i+1); // 
        floorArray [PixelToLight][1]=leifsRed;
        floorArray [PixelToLight][2]=leifsGreen;
        floorArray [PixelToLight][3]=leifsBlue;
      }
      }
      else if (GS[0] > 2) {
        for (byte i = 4; i < 10; i = i + 1) {
        int PixelToLight =  (i+1); // 
        floorArray [PixelToLight][1]=leifsRed;
        floorArray [PixelToLight][2]=leifsGreen;
        floorArray [PixelToLight][3]=leifsBlue;
      }
      }
      }

    else {
      currentRow = currentRow-1; // added because the +1 is done in another function.
      int actualNextGS = (((currentRow+1)*5)+(GS[currentRow+1])+1);
      int nextRow3Center = (((currentRow+1)*5)+(GS[currentRow])+1);
      int randomLoss = actualNextGS;
      while (randomLoss == actualNextGS) { // check to make sure you arent going to remove the actualNextGS. 
        randomLoss = random(nextRow3Center-1, nextRow3Center+2); // Run the random - higher needs to be +1 as it's exclusive.
        Serial.print("Random Loss Try: ");
        Serial.println(randomLoss);
      }
      Serial.print("next row correct one: ");
      Serial.println(actualNextGS);
      Serial.print("One to remove");
      Serial.println(randomLoss);  
  
      int PixelToDark = randomLoss;
    
     
      floorArray [PixelToDark*2][1]=0;
      floorArray [PixelToDark*2][2]=0;
      floorArray [PixelToDark*2][3]=0;
      floorArray [(PixelToDark*2)-1][1]=0;
      floorArray [(PixelToDark*2)-1][2]=0;
      floorArray [(PixelToDark*2)-1][3]=0;
      currentRow = currentRow+1;
    }

    
    strip.show(); 
    ledUpdate(ledState);
  
}
