
# Terrain Tronics Gauntlet Challenge!

The contents of this directory go along with a video from 

## Features

- 50 RGB LED's in an array of 25 cells, each with 2 RGB LED's in them.
- Ir Remote control for the DM that can:
* Reset the playfield with a random, hidden path
* Remove 1 of 3 options (if DM wants to challenge players with a riddle, skillcheck etc)
* Step to the next row.


## What's in this directory?

- Arduino code to run on the WemosD1 Mini. (ino file, bin file etc). The BIN file can be uploaded, AS IS, using the TerrainTronics upload tool.
- SVG / Lightburn files for the foam and wood parts to be cut out.
- 3D printable files (STL) for parts of the bridge, and the "pizzaswitchandsimpleUSBconnector"


## How does all this work?
![](https://github.com/Audio-Rochey/Terrain-Tronics-Caernarfon-Castle/blob/4aec2eabd1f5332a5f59a078c7698883c2515f22/Demo-FallingFloors/images/gauntletbd.jpg)

### Brains and Lights
The playfield is made up of a string of RGB LED's (WS2812B RGB LED's), easily available from Amazon. I picked 60 per Meter, so that a pair of them roughly takes 30mm, close enough to the typical D&D 25.4mm spacing.

The brain is the Arduino compatible Wemos D1 Mini. Based on the infamous ESP8266 Wifi processor, the D1 Mini has a lot of power, a lot of capabilities, small form factor and fairly priced on Amazon.

On top, acting as an interface to the IR Remote control receiver and the interface to the RGB LED's is a Caernarfon Castle PCB board from TerrainTronics. It comes pre-assembled and tested, the only work you have to do is soldering the pins you want to connect to the Wemos D1 Mini.

I typically set the Wemos D1 with Female Headers and use the Caernarfon board with Male headers pointing down into the Wemos D1.
You'll also need to add headers for the NPX Output connector. (NeoPixel - a nerdy term for those RGB LED's) and the IR Receiver.

### Power
I had more fun trying to work out the power tree of this darn thing!
I used a rechargable Lithium Ion battery in my build. If I did it again, I would look for a battery that could support at least 2000mAH. (milli amp hours).

The Chinese electronic module makers have started selling "charge/discharge boards" - these are awesome because they handle all the battery charging concerns. You bring in 5V (from, say, a USB source), you connect your battery (typically a 3.7Volt) and it has an integrated booster, to kick in the 3.7V up to 5V.

WS2812B RGB LED's all require 5V supplies. They are a nuisance! :)

- The USB input connector is always connected to the Charge/Discharge board. That makes sure that even if the lights are off, you can charge the terrain.
- The power switch sits between the output of the CH/Disch board and the Wemos D1 Mini/Caernarfon combination.

## Software

The Arduino IDE is used for developing the software, if you want to tweak it or use it with a different remote control.
You'll need to download the following files:
### 

 - [Caernarfon-FloorPanelProto.ino](https://github.com/Audio-Rochey/Terrain-Tronics-Caernarfon-Castle/blob/main/Demo-FallingFloors/Caernarfon-FloorPanelProto.ino)
 - [buttonfunctions.h](https://github.com/Audio-Rochey/Terrain-Tronics-Caernarfon-Castle/blob/main/Demo-FallingFloors/buttonfunctions.h)
 - [buttonfunctions.ino](https://github.com/Audio-Rochey/Terrain-Tronics-Caernarfon-Castle/blob/main/Demo-FallingFloors/buttonfunctions.ino)

Setting up the Arduino IDe to support the Wemos D1 Mini can be seen in this video: https://www.youtube.com/watch?v=TgE-Op0UvxE

The software is fairly understandable, but if you're struggling, you're welcome to find terraintronics on facebook and ask any questions on the facebook group.

## Physical Build

Lightburn files for laser engraving are in this directory, along with SVG conversions of them. The disc is actually 300mm in diameter, a little less than 12 inches.





> Written with [StackEdit](https://stackedit.io/).
