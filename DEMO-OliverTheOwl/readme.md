
# Oliver the Owl - Made by Terraintronics

![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/9bKIzAbPux4/0.jpg)(https://www.youtube.com/watch?v=9bKIzAbPux4)

Oliver was inspired by WallyDM's Prismatic Owl puzzle.

The entire scene is powered by an 18650 Battery and Charger, available from TerrainTronics (https://www.tindie.com/products/32915/)

The USB Output of the board is connected to Oliver himself, using a USB cable and a hole in the floor.
A Direct 5V output from the board drives a Wemos D1 Mini that has a Harlech Castle 8ch LED Driver on top for driving the LED's that are around the terrain itself.

In the base, along with the battery is the Wemos D1 + Harlech, then each of yellow flickering LED's are connected to it. The setup code is simple and available on this gituhub folder.

## Oliver's Construction

![Olivers Construction](https://github.com/Audio-Rochey/Terrain-Tronics-Caernarfon-Castle/blob/33f060bcf8da8b28d8984dd2b496be7f77d98333/DEMO-OliverTheOwl/pictures/Screenshot%202023-11-28%20205111.png)


Lightburn laser cutter files for Oliver are available from the special URL you receive when you buy from Terraintronics.

His base has a circular ring of WS2812 RGB LED's. They are soldered with wirewrap wire, then wire wrapped to a Caernarfon board.

The Caernarfon board connects is Servo Signal 1 and 2 pins to an L9110 Motor Driver Module from Amazon. That provides the right signals for the motor.

The motor is designed to run from 3.3V, so we need to drop the 5V from the USB on the Wemos D1 to 3.3V on the motor. The Wemos D1 already has a voltage regulator onboard, but I didn't want to risk pulling to much power and causing the Wemos D1 to crash! So an AMS1117 regulator module (again, Amazon was used).

> Written with [StackEdit](https://stackedit.io/).
