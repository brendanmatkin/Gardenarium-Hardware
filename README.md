Gardenarium-Hardware
====================

Arduino code for the Drive-In arcade

Includes all version and prototypes.

Final installed versions: 
* concession_master_04 (UNO)
	* popcorn machine
	* candy vending machine
* controller_master_04 (TESSNY 3.1)
	* steering wheel as mouse (horn as space bar)
	* joystick as joystick
	* pop vender control (Processing sketch OSC_TO_SERIAL)

All other sketches have been folded into one of the previous two. 

OSC_to_Serial is a processing sketch to receive OSC from Unity and send Serial to TEENSY (for pop vender).

SCRIPTS folder contains UNITY C# scripts to send OSC data (for pop vender).