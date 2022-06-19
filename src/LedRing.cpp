#include "../include/LedRing.h"

#include <Adafruit_NeoPixel.h>

LedRing::LedRing(uint16_t neoPixelSize, uint16_t neoPixelDataPin, neoPixelType ringType) 
{
    this->neoPixelObject = new Adafruit_NeoPixel(neoPixelSize, neoPixelDataPin, ringType);

    this->currentMode = 0;
    this->resetModeInternals();
}

LedRing::~LedRing()
{
    delete this->neoPixelObject;
}

void LedRing::nextMode() 
{
    this->currentMode++;
    this->resetModeInternals();
}

void LedRing::processMode() 
{
    switch (this->currentMode)
    {
    case 0:
        this->mode_rainbowTest();
        break;

    case 1:
        this->mode_smoothFadeThrough();
        break;

    case 2:
        this->mode_colorIterate1();
        break;

    case 3:
        this->mode_colorIterate2();
        break;
    
    default:
        // unkown mode / reset mode
        this->currentMode = 0;
        this->processMode();
        break;
    }
}

void LedRing::resetModeInternals() 
{
    this->savedHue = 0;
    this->submode  = 0;
    this->savedInt = 0;
}

void LedRing::init(uint8_t startBrightness) 
{
    this->neoPixelObject->begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    this->neoPixelObject->show();  // Turn OFF all pixels ASAP
    this->neoPixelObject->setBrightness(startBrightness); 
    this->pixelBrightness = startBrightness;
}

void LedRing::increaseBrightness(uint16_t BrightnessStep) 
{
    short int newBrightness = this->pixelBrightness + BrightnessStep;
    if (newBrightness < 255) {
        this->pixelBrightness = newBrightness;
        this->neoPixelObject->setBrightness( this->pixelBrightness );
        this->neoPixelObject->show();
    }
}

void LedRing::decreaseBrightness(uint16_t BrightnessStep) 
{
    short int newBrightness = this->pixelBrightness - BrightnessStep;
    if (newBrightness > 0) {
        this->pixelBrightness = newBrightness;
        this->neoPixelObject->setBrightness(this->pixelBrightness);
        this->neoPixelObject->show();
    }
}

void LedRing::colorWipe(uint32_t color, int wait) 
{
    for(int i=0; i < (int) this->neoPixelObject->numPixels(); i++) {
        this->neoPixelObject->setPixelColor(i, color);
        this->neoPixelObject->show();
        delay(wait);
    }
}

void LedRing::mode_rainbowTest() 
{
    int rainbowLoops=1;

    // Hue of first pixel runs 'rainbowLoops' complete loops through the color
    // wheel. Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to rainbowLoops*65536, using steps of 256 so we
    // advance around the wheel at a decent clip.
    for(uint32_t firstPixelHue = 0; firstPixelHue < (uint32_t) rainbowLoops*65536; firstPixelHue += 256) {

        for(int i=0; i < (int) this->neoPixelObject->numPixels(); i++) { // For each pixel in strip...

            // Offset pixel hue by an amount to make one full revolution of the
            // color wheel (range of 65536) along the length of the strip
            // (strip.numPixels() steps):
            uint32_t pixelHue = firstPixelHue + (i * 65536L / this->neoPixelObject->numPixels());

            // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
            // optionally add saturation and value (brightness) (each 0 to 255).
            // Here we're using just the three-argument variant, though the
            // second value (saturation) is a constant 255.
            this->neoPixelObject->setPixelColor(i, this->neoPixelObject->gamma32(this->neoPixelObject->ColorHSV(pixelHue, 255, 255)));
        }

        this->neoPixelObject->show();
    }
}

void LedRing::mode_smoothFadeThrough() 
{
    // Info from AdaFruit:
    // "Color wheel has a range of 65536 but it's OK if we roll over"
    if ( this->savedHue < 65536 ) {
        this->savedHue += 1;
    }
    else {
        this->savedHue = 0;
    }
    
    
    for(int i=0; i < (int) this->neoPixelObject->numPixels(); i++) { // For each pixel in strip...
        this->neoPixelObject->setPixelColor( i, this->neoPixelObject->gamma32( 
            this->neoPixelObject->ColorHSV(this->savedHue, 255, 255)
        ));
    }

    this->neoPixelObject->show();
}

void LedRing::mode_colorIterate1() 
{
    // HSV Limit protector
    if ( this->savedHue > 65536 ) {
        this->savedHue = 0 + this->savedHue;
    }

    // Pixel iterator
    for(int i=0; i < (int) this->neoPixelObject->numPixels(); i++) { // For each pixel in strip...
        this->neoPixelObject->setPixelColor( i, this->neoPixelObject->gamma32( 
            this->neoPixelObject->ColorHSV(this->savedHue++, 255, 255)
        ));
    }

    this->neoPixelObject->show();
}

void LedRing::mode_colorIterate2() 
{
    // HSV Limit protector
    this->savedHue++;
    if ( this->savedHue > 65536 ) {
        this->savedHue = this->savedHue;
    }

    // pixel iterator
    int pixelNum = this->savedInt;
    if ( pixelNum < (int) this->neoPixelObject->numPixels() ) {
        pixelNum++;
    }
    else {
        pixelNum = 0;
    }

    // count opposite pixel
    int oppositePixel = this->neoPixelObject->numPixels() - pixelNum;
    
    // set new pixel color
    uint32_t newColor = this->neoPixelObject->ColorHSV(
        this->savedHue+=1000, 255, 255
    );
    this->neoPixelObject->setPixelColor(pixelNum, newColor);
    this->neoPixelObject->setPixelColor(oppositePixel, newColor);
    
    // save data for next the loop
    this->savedInt = pixelNum;
    this->neoPixelObject->show();

    // wait before new iteration
    delay(150);
}
