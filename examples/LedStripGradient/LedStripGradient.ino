/* LedStripGradient: Example Arduino sketch that shows
 * how to control an Addressable RGB LED Strip from Pololu.
 *
 * To use this, you will need to plug an Addressable RGB LED
 * strip from Pololu into pin 12.  After uploading the sketch,
 * you should see a pattern on the LED strip that fades from
 * green to pink and also moves along the strip.
 */

#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 60
rgb_color colors[LED_COUNT];

void setup()
{
}

void loop()
{
  // Update the colors.
  byte time = millis() >> 2;
  for (uint16_t i = 0; i < LED_COUNT; i++)
  {
    byte x = time - 8*i;
    colors[i] = rgb_color(x, 255 - x, x);
  }

  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);

  delay(10);
}
