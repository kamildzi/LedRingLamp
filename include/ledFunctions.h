#ifndef LED_FUNCTIONS_HPP
#define LED_FUNCTIONS_HPP

#include "Adafruit_NeoPixel.h"

#define BRIGHTNESS_STEP  10
#define BRIGHTNESS_START 50

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(Adafruit_NeoPixel &ring, uint32_t color, int wait) {
  for(int i=0; i<ring.numPixels(); i++) {
    ring.setPixelColor(i, color);
    ring.show();
    delay(wait);
  }
}

void rainbowFade2White(Adafruit_NeoPixel &ring, int wait, int rainbowLoops, int whiteLoops) {
  int fadeVal=0, fadeMax=100;

  // Hue of first pixel runs 'rainbowLoops' complete loops through the color
  // wheel. Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to rainbowLoops*65536, using steps of 256 so we
  // advance around the wheel at a decent clip.
  for(uint32_t firstPixelHue = 0; firstPixelHue < rainbowLoops*65536;
    firstPixelHue += 256) {

    for(int i=0; i<ring.numPixels(); i++) { // For each pixel in strip...

      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      uint32_t pixelHue = firstPixelHue + (i * 65536L / ring.numPixels());

      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the three-argument variant, though the
      // second value (saturation) is a constant 255.
      ring.setPixelColor(i, ring.gamma32(ring.ColorHSV(pixelHue, 255, 255)));
    }

    ring.show();
    delay(wait);

    if(firstPixelHue < 65536) {                              // First loop,
      if(fadeVal < fadeMax) fadeVal++;                       // fade in
    } else if(firstPixelHue >= ((rainbowLoops-1) * 65536)) { // Last loop,
      if(fadeVal > 0) fadeVal--;                             // fade out
    } else {
      fadeVal = fadeMax; // Interim loop, make sure fade is at max
    }
  }

//   for(int k=0; k<whiteLoops; k++) {
//     for(int j=0; j<256; j++) { // Ramp up 0 to 255
//       // Fill entire strip with white at gamma-corrected brightness level 'j':
//       ring.fill(ring.Color(0, 0, 0, ring.gamma8(j)));
//       ring.show();
//     }
//     delay(1000); // Pause 1 second
//     for(int j=255; j>=0; j--) { // Ramp down 255 to 0
//       ring.fill(ring.Color(0, 0, 0, ring.gamma8(j)));
//       ring.show();
//     }
//   }

//   delay(500); // Pause 1/2 second
}


#endif // LED_FUNCTIONS_HPP
