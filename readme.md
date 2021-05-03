# TerrainTronics-Caernarfon-Castle

![Image of Caernarfon Castle and the Small Circuit Board](readmeimages/1.png)

## Introduction

The TerrainTronics Caernarfon Castle board is designed to bring interaction to your terrain. The Caernarfon castle offers:
- Ability to drive 3x Servo Motors
- Infra-Red Remote Control Receiver
- Neopixel (WS281x) Addressable LED's

Onboard is the ability to drive 3 Servo Motors for moving gates, doors and other light bits of terrain, work with 3 LED's directly, and address a long chain of others, to, for example, Change all the lights on your terrain RED when the situation changes, and with an IR Reciever, so you can use any old remote control to send messages to your terrain to respond. 

This makes it the ultimate tool for a DM (Dungeon Master) or GM (Games Master) to make their worlds interactive, to create puzzles with real, visible outcomes - prizes or punishments!

Code examples are constantly being developed and added here. 

**Please Note** - a Wemos D1 Mini board is required to control the Caernarfon Castle board. The Wemos D1 Mini is a small microcontroller board that has a standardized small form factor, wifi capability (if you want to use it) and the ability for it to be programmed using the Arduino programming environment. Whilst installing the Arduino programming environment is required to configure your setup - you can avoid the need for actual programming by copy/pasting some of the examples here.


## Pinout of the board

![Image of Caernarfon Castle Board with annotations for each connector](readmeimages/2.png)

The Caernarfon Castle board is delivered without the pins having been soldered, however, you should find the pins in the package. This is to allow you to populate whichever pins are needed for the functionality that you are working towards, or, if system height is a concern, to solder wires directly into the holes.

The strips on the left and right hand side of the board are mandatory, to be used to stack and connect to a Wemos D1 Mini. Most Wemos D1 Mini boards are sold without soldered connectors either. In my experience it's easier to put female headers on the Wemos D1, then downard facing male connectors on the Caernarfon board. 

### Servo's
For motors that can turn an arm between 0 and 180 degrees, servo motors can be used. Servo motors have been used in model aircraft and train sets for years. They are quite easy to use, as you set the angle of deflection needed, and the servo motor will turn to that angle, and using it's own internal feedback, hold that position. The controller, or your software doesn't need to be concerned about measuring or holding the angle etc - simply tell the servo (using code) where to turn to - and it just does!
In the demo code, it's used as a gate to hold a boulder from rolling down and hurting the adventurers.

3 servo motors can be connected to the Caernarfon Castle board and can be addressed in Wemos D1 Arduino code on pins D5, D6 and D7. A library called Servo.h (a standard Arduino library) is used and can be downloaded from the internal GUI.

Servo's can be connected on to the 3-pin strips in the middle of the board. They should be connected as SIGNAL-POWER-GND. Most servo's are colour coded in Orange (Signal), Red (Power), Brown/Black (Ground). I've had some success with SG90 Servo's. They are the smallest kind on Amazon, but very usable.

### LED's
The board has a WS2811 onboard. This is a chip that the wemos d1 board talks to with LED values. It has 4 outputs. 3 of them are for LED's and one (DOUT) is used to send on to the next in the chain. Such a daisy chain of LED's can pull a lot of current (power), so you may need an external 5V power supply that can provide enough current. For a handful of LED's, you should have no trouble.


###Servo Motors



![Internal Image of an LED (source Wikipedia)](readmeimages/2.png)

### To function normally, LED’s need a few things 
- High enough VOLTAGE across them, to switch them on. 

![Image of LED color and voltage required](readmeimages/3.png)
- Current limiting, because once they switch on, they look like a short circuit and will burn up without something to limit the current.
- Wired the right way ‘round. The long leg goes to the positive side of your circuit, and short side goes to the negative. Wiring them in backwards will mean they won’t light up, but they should not be damaged.

Most LED’s need to be limited to about 20mA (milli Amps – that’s one thousandths of an Amp!). Any more than this, and your common 5mm diameter LED will burn up and fail.

The LED’s used in your room lights etc can tolerate higher Currents, and shine brighter, but ultimately, they are still low voltage devices.
For more on Voltage and Current, check out this video: https://youtu.be/mFjnooXosdU

## LED's are normally wired with a resistor!

![Traditional LED cicruit](readmeimages/4.png)

Conwy Castle board does a clever trick and replaces the resistor with a transistor that is externally controlled, so that 4 channels are controlled together. (see Schematic and Theory of operation)

## LED Brightness vs Current
LED brightness is measured in Millicandela. LED’s are specified for Millicandela (mcd) at 20mA typically. An Orange and Green LED, if they are both specified for 2000mcd @ 20mA will be equally as bright if you drive the same current through them, even though they drop a different voltage.
 
![Typical Kit of LED's from Amazon](readmeimages/5.png)
In the kit above, you can see that the yellow and blue will be perfectly matched with 20mA, and the Red will be pretty close too! However, Green and White will be quite a bit brighter and would be better driven from a different Conwy board.
**THAT** is why we prefer to drive LED’s with constant current circuits, not constant voltage.

## Connecting LED’s to the Conwy Castle board

![Where to connect LED's to the Conwy Castle board](readmeimages/6.png)

Conwy Castle uses standard 0.1” / 2.54mm pitch header pins to connect to LED’s. As the current limiting component is actually integrated in the board you only need to connect the two pins directly to the LED. The board takes care of the current limiting and the brightness control.
Connection can be done with a wire wrapping tool, Soldering or Dupont Jumper wires.
I rather like wire wrap for this part of the board, as it’s a strong connection, easily done away from the workbench without a soldering iron, and frankly, if they can send a person to space using wire-wrap technology, then we can build terrain with it.


## Power Supply Options
### USB Wall power and USB Power Banks
Conwy comes with a Micro-USB connector already on it. This should be enough to drive all LED types. However, most LED’s don’t pull enough power to keep USB Power Banks switched on. (they think there’s nothing to power, so they go to sleep). This can be solved by soldering in one of the power resistors included in the pack.
Most USB Wall Powered units don’t do this. So this resistor can be omitted. In use, the Resistor will become warm, as it is dissipating 1/2W of power.
In the pack should be two resistors and some solder, just in case you don’t have any to hand.

![Adding the power resistor to draw enough power to keep battery packs switches on](readmeimages/7.png)

### Alkaline Battery Packs
AA and AAA battery packs are quite common in terrain building. Some of them even come with power switches integrated into them. For use with LED’s it’s suggested to use 3 Alkaline batteries in Series (so that the total voltage is 3x 1.5V = 4.5V). White and Blue LED’s need more than 3V to function.

![Classic Alkaline battery holder - AA or AAA](readmeimages/8.png)

As such, 2x AA or AAA batteries will struggle to light them up. For applications with other colors, it is possible that 2x AA batteries could be used – be sure to test on your bench first!
AA batteries will typically have about 2000mAH of capacity. If your LED’s are pulling 10mA each, then you should be able to get <200 hours for an LED. Divide down as you add more LED’s or draw more current.
Wiring a battery pack into the Conwy Castle board is quite easy. Solder the RED + from the pack to one side of the Power Resistor footprint, and wire the BLACK – to the other side as shown in the diagram below.

![Wiring Batteries directly to Conwy](readmeimages/9.png)

### Coin Cell Batteries
CR2032 batteries are quite common in “Throwies” and electronic tea lights. These are simple circuits, where the brightness of the LED is set by the battery itself. CR2032 batteries are limited in the amount of current they can output. This current limit helps with LED’s.
However, where they fall apart is when you try to drive multiple LED’s in parallel. The inbuilt resistance in them limits the current to be delivered to the LED’s.

![Traditional CR2032 Coin Battery](readmeimages/10.png)
 
### Lithium Ion Batteries

Lithium Ion batteries typically come in two types. Protected and Unprotected variants. These are typically 3.7V, and require a special circuit to protect them (this is usually on the battery). These batteries have a lot of power capacity in a small space. Care should be taken not to puncture them or expose them to high temperatures.
•	They require special charging circuits to charge from USB. (search Amazon for TP4056 Charger)
•	Protection Circuits prevent overheating/explosions caused by short circuits or the battery running too low. We love protection circuits. Some charging boards come with them integrated too. 2 circuits are even better than 1!

![Two types of Lithium Ion Batteries - Protected and Unprotected](readmeimages/11.png)


Hooking up a battery, charger circuit and a Conwy castle board can be seen below
 
![Battery, Charger and a pair of Conwy boards](readmeimages/12.png)
•	The battery is only connected to the charge board. It should be connected to the B+ and B- points. 
•	Out+ from the charger board goes to one side of the switch. 
•	The Common (middle) pin of the switch then goes to the + side of the resistor footprint on the Conwy board. 
•	OUT- from the charger board goes to the Negative side of the board.

Multiple Conwy boards can share the same OUT+ and OUT- from the charger board.
The big resistor typically used for USB Power Bank’s isn’t required with lithium ion batteries. They continue to provide power, even if the amount of current being drawn it low.

## Adding a switch

### USB
In the USB Powerbank use case, many of them already come with a switch, if not – I’m really quite fond of these in-line switch cables. Available on Amazon.

![USB Micro cable with an inline switch](readmeimages/13.png)
 
### Battery Packs (Alkaline, Lithium Ion, Coincell etc)
For battery packs without the included switch, I’m quite fond of simple slide switches. (Amazon search “Slide switch solder lug”. They are easily sourced, reliable and easy to solder to. The holes and shape allow them to be mounted to 3d printed frames easily. 
 
![Traditional slide switch](readmeimages/14.png)
 
## Schematic and Theory of Operation
![Wiring Batteries directly to Conwy](readmeimages/15.png)
The board functions a current source and 4 current mirrors.
R1,R2 and Q1 sets the reference current in the circuit.
Q2 through Q5 then mirror that current if they can. So an LED connected between the +5V (or your battery positive voltage) and the Drain (the top) of the transistor Q2-Q5 will switch on, then only allow the same amount of current through it that goes through Q1. E.g. if Q1 is set up for 10mA, then regardless of the color of the LED, only 10mA will be passed through it.

As mentioned in section 1 – each color LED drops a different voltage, but many are rated for the same brightness at a specific current. 
 
 
