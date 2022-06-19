#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>

#include "include/ioPins.h"
#include "include/powerFunctions.h"
#include "include/LedRing.h"


// ----------------------------------------------------------------------------
// TIMERS
// ----------------------------------------------------------------------------

// Power-Off when button is pressed for (n) sec
#define POWEROFF_TIME 4000
RBD::Timer timer_PowerOff;

// Initial hold-lock and step-factor 
// (to lower the initial value while the button is pressed)
#define BUTTON_HOLD_TIME 50
#define BUTTON_HOLD_STEPUPFACTOR 1.05
RBD::Timer timer_ButtonHold;

// ----------------------------------------------------------------------------
// BUTTONS
// ----------------------------------------------------------------------------

// input pullup enabled by default
RBD::Button button_Mode(BUTT_MODE);
RBD::Button button_Down(BUTT_DOWN);
RBD::Button button_Up(BUTT_UP);

// ----------------------------------------------------------------------------
// LED RING
// ----------------------------------------------------------------------------

LedRing ringObject(RING_SIZE, RING_DATA_PIN);

// ----------------------------------------------------------------------------

void resetButtonHoldTimer( boolean fullReset = false ) {
    if ( fullReset ) {
        timer_ButtonHold.setTimeout(BUTTON_HOLD_TIME);
    }
    else {
        unsigned long newTime = timer_ButtonHold.getTimeout() / BUTTON_HOLD_STEPUPFACTOR;
        timer_ButtonHold.setTimeout( newTime );
    }
    timer_ButtonHold.restart();
}

void testRing() {
    // Fill along the length of the strip in various colors...
    ringObject.colorWipe(Adafruit_NeoPixel::Color( 255,   0,   0)    , 20); // Red
    ringObject.colorWipe(Adafruit_NeoPixel::Color(  0,  255,   0)    , 20); // Green
    ringObject.colorWipe(Adafruit_NeoPixel::Color(  0,    0, 255)    , 20); // Blue
    ringObject.colorWipe(Adafruit_NeoPixel::Color( 255, 255, 255, 0) , 20); // White
    ringObject.colorWipe(Adafruit_NeoPixel::Color(  0,   0,   0,  0) , 20);
    delay(200);
}

void setup() {
    powerInit();
    
    timer_PowerOff.setTimeout(POWEROFF_TIME);
    resetButtonHoldTimer( true );

    ringObject.init(BRIGHTNESS_START);
    testRing();
}

void shutDownProcess() {
    ringObject.colorWipe( Adafruit_NeoPixel::Color(0, 0, 0), 100 );
    ringObject.neoPixelObject->setBrightness(0);
    ringObject.neoPixelObject->show();
    delay(1000);
    powerOff();
}

void buttonsRead() {

    // Standard "Mode" action
    if ( button_Mode.onReleased() ) {
        ringObject.nextMode();
    }

    // Power controll
    if ( button_Mode.onPressed() ) {
        timer_PowerOff.restart();
    }
    else if ( button_Mode.isPressed() ) {
        if ( timer_PowerOff.isExpired() ) {
            shutDownProcess();
        }
    }

    // Brightness controll
    if ( button_Up.isPressed() && timer_ButtonHold.isExpired() ) {
        ringObject.increaseBrightness();
        resetButtonHoldTimer();
    }
    else if ( button_Down.isPressed() && timer_ButtonHold.isExpired() ) {
        ringObject.decreaseBrightness();
        resetButtonHoldTimer();
    }
    else if ( button_Up.onReleased() || button_Down.onReleased() ) {
        resetButtonHoldTimer( true );
    }
}

void loop() {

    buttonsRead();

    // ringObject.rainbowTest(0, 1);
    ringObject.processMode();
}