# LedRingLamp
Arduino based, single-controller LED (ring type) lamp.\
Sorry, I don't have hardware schematics for this. 

# Requirements
1. [Arduino-Makefile](https://github.com/sudar/Arduino-Makefile) \
Note: Read the [readme](https://github.com/sudar/Arduino-Makefile#readme). 

2. Extra libraries
- [Adafruit_NeoPixel.h](https://github.com/adafruit/Adafruit_NeoPixel)
- [RBD_Timer.h](https://github.com/alextaujenis/RBD_Timer)
- [RBD_Button.h](https://github.com/alextaujenis/RBD_Button)

# Configuration
- Edit variables at [Makefile](Makefile)

# Building and uploading
```shell
make
make upload
make clean
```
