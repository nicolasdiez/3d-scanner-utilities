# 3d-scanner-utilities

# This repo contains all the Windows API utilities that the Lucida 3D scanner needs to work on a laptop:
- COM Detect Class: used to identify in which COM port of the laptop is the Arduino microcontroler connected
- Wifi Handler Class: to permit that the radio wifi adapters of the laptop can be dissabled while the 3D scanner is working, and re-enabled when the 3D scanner finishes its job
- Power Plan Class: used to activate the high performance power plan of the laptop while the 3D scanner is working, and re-establish the user´s former power plan when the scanner finished. Also warns about insufficiente memory requirements for 3D scanning.
