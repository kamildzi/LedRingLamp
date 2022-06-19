#ifndef LEDRING_H
#define LEDRING_H

#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS_STEP  1
#define BRIGHTNESS_START 50


class LedRing
{
private:
    uint8_t pixelBrightness;

    // Current Mode Internals
    uint8_t currentMode;
    uint32_t savedHue;
    char16_t submode;
    int savedInt;

public:
    // NeoPixel led object
    Adafruit_NeoPixel* neoPixelObject;

    /**
     * (Description copied from AdaFruid) 
     * @param ringSize Number of pixels in NeoPixel strip
     * @param ringDataPin Arduino pin number (must be valid)
     * @param ringType Pixel type flags, add together as needed: 
     *   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs) 
     *   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers) 
     *   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products) 
     *   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2) 
     *   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products) 
     */
    LedRing(uint16_t neoPixelSize, uint16_t neoPixelDataPin, neoPixelType ringType = NEO_GRB + NEO_KHZ800);
    ~LedRing();

    /**
     * Switch the mode
     */
    void nextMode();

    /**
     * Trigger current mode function
     */
    void processMode();

    /**
     * Reset mode memory
     */
    void resetModeInternals();

    /**
     * Init the NeoPixel Object
     * @param startBrightness 0 (min) - 255 (max)
     */
    void init(uint8_t startBrightness);

    /**
     * Increase the brightness
     */
    void increaseBrightness(uint16_t BrightnessStep = BRIGHTNESS_STEP);

    /**
     * Decrease the brightness
     */
    void decreaseBrightness(uint16_t BrightnessStep = BRIGHTNESS_STEP);

    /**
     * ~~ SO: AdaFruit desc ~~ 
     * Fill strip pixels one after another with a color. Strip is NOT cleared
     * first; anything there will be covered pixel by pixel. Pass in color
     * (as a single 'packed' 32-bit value, which you can get by calling
     * strip.Color(red, green, blue) as shown in the loop() function above),
     * and a delay time (in milliseconds) between pixels. 
     * ~~ EO: AdaFruit desc ~~
     * 
     * @param color use `Adafruit_NeoPixel::Color(r,g,b)` to select the color
     * @param wait wait time
     */    
    void colorWipe(uint32_t color, int wait = 0);

    void mode_rainbowTest();

    void mode_smoothFadeThrough();

    void mode_colorIterate1();

    void mode_colorIterate2();
};

#endif