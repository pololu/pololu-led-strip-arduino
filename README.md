# Arduino library for addressable RGB LED strips from Pololu

Version: 4.2.0<br>
Release date: 2017-03-20<br>
[![Build Status](https://travis-ci.org/pololu/pololu-led-strip-arduino.svg?branch=master)](https://travis-ci.org/pololu/pololu-led-strip-arduino)<br>
[www.pololu.com](https://www.pololu.com/)

[![Image](https://a.pololu-files.com/picture/0J4995.1200.jpg?e4ec28a3e9151b2e8f015c6cc6a4efab)](https://www.pololu.com/picture/view/0J4995)

## Summary

This is a library for the Arduino for controlling these addressable
RGB LED products from Pololu:

* [Addressable RGB 30-LED Strip, 5V, 1m &#40;SK6812)](https://www.pololu.com/product/2526)
* [Addressable RGB 60-LED Strip, 5V, 2m &#40;SK6812)](https://www.pololu.com/product/2527)
* [Addressable RGB 150-LED Strip, 5V, 5m &#40;SK6812)](https://www.pololu.com/product/2528)
* [Addressable RGB 60-LED Strip, 5V, 1m &#40;SK6812)](https://www.pololu.com/product/2529)
* [Addressable RGB 120-LED Strip, 5V, 2m &#40;SK6812)](https://www.pololu.com/product/2530)
* [Addressable High-Density RGB 72-LED Strip, 5V, 0.5m &#40;SK6812)](https://www.pololu.com/product/2531)
* [Addressable RGB 30-LED Strip, 5V, 1m &#40;WS2812B)](https://www.pololu.com/product/2546)
* [Addressable RGB 60-LED Strip, 5V, 2m &#40;WS2812B)](https://www.pololu.com/product/2547)
* [Addressable RGB 150-LED Strip, 5V, 5m &#40;WS2812B)](https://www.pololu.com/product/2548)
* [Addressable RGB 60-LED Strip, 5V, 1m &#40;WS2812B)](https://www.pololu.com/product/2549)
* [Addressable RGB 120-LED Strip, 5V, 2m &#40;WS2812B)](https://www.pololu.com/product/2550)
* [Addressable High-Density RGB 72-LED Strip, 5V, 0.5m &#40;WS2812B)](https://www.pololu.com/product/2551)
* [Addressable Through-Hole 5mm RGB LED with Diffused Lens, WS2811 Driver (10-Pack)](https://www.pololu.com/product/2535)
* [Addressable Through-Hole 8mm RGB LED with Diffused Lens, WS2811 Driver (10-Pack)](https://www.pololu.com/product/2536)
* [Adafruit 16 WS2812 LED NeoPixel Ring](https://www.pololu.com/product/2537)
* [Adafruit 24 WS2812 LED NeoPixel Ring](https://www.pololu.com/product/2538)
* [Adafruit 15 WS2812 LED NeoPixel 1/4-Ring](https://www.pololu.com/product/2539)
* [Adafruit 5&times;8 WS2812 LED NeoPixel Shield for Arduino](https://www.pololu.com/product/2772)
* [Addressable RGB 30-LED Strip, 5V, 1m &#40;High-Speed TM1804)](https://www.pololu.com/product/2543)
* [Addressable RGB 60-LED Strip, 5V, 2m &#40;High-Speed TM1804)](https://www.pololu.com/product/2544)
* [Addressable RGB 150-LED Strip, 5V, 5m &#40;High-Speed TM1804)](https://www.pololu.com/product/2545)

This library is optimized for the SK6812 and WS2812B, so it transmits
colors in green-red-blue order.

If you have a WS2811 LED or a high-speed TM1804 LED strip, please note
that its red and green channels are swapped relative to the SK6812 and
WS2812B, so you will need to swap those channels in your code. You
might prefer to use
[version 2.1.0](https://github.com/pololu/pololu-led-strip-arduino/releases/tag/2.1.0)
of the library, which does not require you to swap red and green in
your code.

This version of the library does not support the older low-speed
TM1804 LED strips.  If you want to control those, we recommend using
[version 1.2.0](https://github.com/pololu/pololu-led-strip-arduino/releases/tag/1.2.0),
which runs slower but can work with any of the low-speed TM1804 LED
strips, high-speed TM1804 strips, SK6812 strips, WS2812B strips, or
WS2811 LEDs.

This library allows complete control over the color of an arbitrary
number of LED strips with an arbitrary number of LEDs.  Each LED can
be individually controlled, and LED strips can be chained together.

## Supported platforms

This library and the examples are designed to work with the Arduino
IDE versions 1.0 and 1.5 and probably will not work with earlier
versions.

This library currently supports any board based on the ATmega168,
ATmega328P, ATmega32U4, or ATmega2560 which runs at 8 MHz, 16 MHz, or
20 MHz.  This includes the
[A-Star 32U4 boards](https://www.pololu.com/category/149/a-star-programmable-controllers),
the [Arduino Uno](https://www.pololu.com/catalog/product/2191), the
older Arduino Duemilanovae, the
[Baby Orangutan B-328](https://www.pololu.com/catalog/product/1220),
the [Orangutan SV-328](https://www.pololu.com/catalog/product/1227),
the [Arduino Leonardo](https://www.pololu.com/catalog/product/2192),
the [Arduino Micro](https://www.pololu.com/product/2188), and the
[Arduino Mega](https://www.pololu.com/catalog/product/1699).  Not all
pins on the Arduino Mega are supported (see below).

This library also supports the
[Arduino Due](https://www.pololu.com/catalog/product/2193), which is
based on the ATSAM3X8E.

## Getting started

### Hardware

The addressable RGB LED strips can be purchased on Pololu's website
using the links above.

The LED strip's input connector has two pins that should be connected
to the Arduino.  The LED strip's ground will need to be connected to
one of the Arduino's GND pins, and the LED strip's signal input line
will be need to be connected to one of the Arduino's I/O lines.  Our
example sketches assume the signal line is connected to pin 12.  These
connections can be made using two
[Male-Female Premium Jumper Wires](https://www.pololu.com/catalog/category/67),
with the female ends plugging into the LED strip.

You will also need to connect a suitable power supply to the LED strip
using one of the power connectors.  The power supply must be at the
right voltage and provide enough current to meet the LED strip's
requirements.

### Software

If you are using version 1.6.2 or later of the
[Arduino software (IDE)](https://www.arduino.cc/en/Main/Software), you can use
the Library Manager to install this library:

1. In the Arduino IDE, open the "Sketch" menu, select "Include Library", then
   "Manage Libraries...".
2. Search for "PololuLedStrip".
3. Click the PololuLedStrip entry in the list.
4. Click "Install".

If this does not work, you can manually install the library:

1. Download the
   [latest release archive from GitHub](https://github.com/pololu/pololu-led-strip-arduino/releases)
   and decompress it.
2. Rename the folder "pololu-led-strip-arduino-xxxx" to "PololuLedStrip".
3. Drag the "PololuLedStrip" folder into the "libraries" directory inside your
   Arduino sketchbook directory. You can view your sketchbook location by
   opening the "File" menu and selecting "Preferences" in the Arduino IDE. If
   there is not already a "libraries" folder in that location, you should make
   the folder yourself.
4. After installing the library, restart the Arduino IDE.

## Examples

Several example sketches are available that show how to use the
library. You can access them from the Arduino IDE by opening the
"File" menu, selecting "Examples", and then selecting "PololuLedStrip". If
you cannot find these examples, the library was probably installed
incorrectly and you should retry the installation instructions above.

### LedStripGradient

This example code sketch lights up the LED strip with a moving
gradient pattern.  You can open this example sketch by selecting
File->Examples->PololuLedStrip->LedStripGradient.  Click the "Upload"
button to load it onto your board.

### LedStripRainbow

This example is like LedStripGradient, but makes a rainbow pattern
instead.  You can open this example sketch by selecting
File->Examples->PololuLedStrip->LedStripRainbow.  Click the "Upload"
button to load it onto your board.

### LedStripColorTester

This example code sketch allows you to type colors into the Serial
Monitor and see them on the LED strip.  You can open this example by
selecting File->Examples->PololuLedStrip->LedStripColorTester.  Click
the "Upload" button to load it onto your board.  See the comments in
the code for more information on how to use it.

## Timing details

This library takes about 1.1 ms to update 30 LEDs (1 meter).  The LED
strips use a high speed one-wire protocol with relatively strict
timing requirements, so this library disables interrupts to ensure
reliable color transmission.  Unfortunately, disabling the interrupts
causes problems in other libraries that uses interrupts, such as the
`Serial` library and the functions like `millis()` that keep track of
time.

This library provides an `interruptFriendly` option that can let it
coexist with interrupt-based libraries.  When this option is enabled,
the library will temporarily enable interrupts after each color is
sent, about every 36 microseconds.  If you can keep all of your
interrupts short enough, then this option should allow this library to
work in conjunction with your interrupt-based libraries.  However, if
you have an interrupt enabled that takes longer than about 38
microseconds for the SK6812, 5 microseconds for the WS2812B, or 8
microseconds for the TM1804, then this interrupt will sometimes cause
an extra long low pulse to emitted, which will be interpreted by the
LED strip as a reset command.  This can cause visible flickering in
the LED strip.  By default, many common Arduinos such as the Arduino
Uno have an interrupt that runs every millisecond and takes longer
than 8 microseconds, so this option will give bad results unless you
disable that interrupt.  To turn on the `interruptFriendly` option,
add this line to your `setup()` function:

    PololuLedStripBase::interruptFriendly = true;

Because the library disables interrupts by default, it can cause the
timekeeping functions of your Arduino to miss ticks.  As a result, the
Arduino's time, which can be accessed from functions like `millis()`,
will appear to be running slower than usual.  In our demo code, we get
around this by adding a 10 millisecond delay at the end of the `loop`
function; this ensures that the Arduino will only spend a minority of
its time updating the LED strip and therefore limits how much the
timekeeping will be affected.

## Documentation

### rgb_color

The library defines a type named `rgb_color` which can be used to
represent colors.  The type is defined like this:

    typedef struct rgb_color
    {
      unsigned char red, green, blue;
    } rgb_color;

The fields `red`, `green`, and `blue` are numbers between 0 and 255
and represent the brightness of the red, green, and blue color
components respectively.

### PololuLedStrip&lt;pin&gt;

The libary defines a template class named `PololuLedStrip<pin>`.  The
`pin` template parameter is an `unsigned char` and should be the
number of the Arduino pin that the LED strip's data input line is
connected to.  For ATmega2560-based boards such as the Arduino Mega,
only the following pins are usable: 0&ndash;5, 10&ndash;13,
18&ndash;41, and 50&ndash;61 (ports A through G).  This template class
inherits from the abstract class `PololuLedStripBase`, which is useful
if you want to have pointers to LED strip objects.

This class has no constructor except the default one.  This class has
one function:

- `void write(rgb_color * colors, unsigned int count)` <br> Writes the
  specified colors to the LED strip.  The `colors` parameter should be
  a pointer to an array of `rgb_color` structs in RAM.  The `count`
  parameter is the number of colors to write.  The first color in the
  array will be written to the LED closest to the data input
  connector.  To update all the LEDs in the LED strip, `count` should
  be equal to or greater than the number of LEDs in the strip.  If
  `count` is less than the number of LEDs in the strip, then some LEDs
  near the end of the strip will not be updated.  This function
  disables interrupts temporarily.  This function pauses for over 10
  us at the end before returning to allow the colors to take effect.

### PololuLedStripBase

- `static bool interruptFriendly;` <br> This option defaults to
  `false`.  Setting this to `true` changes the behavior of the `write`
  function, making it enable interrupts after each color is sent,
  about every 36 microseconds.  See the discussion above.

## Chaining LED strips together

No special code is required to chain LED strips together.  An X-meter
LED strip chained to a Y-meter LED strip can be controlled in exactly
the same way as a single (X+Y)-meter LED strip.

## Version history

* 4.2.0 (2017-03-20): Added a constructor for rgb_color that takes the three color values and changed the examples to use it.  Added `keywords.txt`, which is used by the Arduino IDE for syntax highlighting.
* 4.1.1 (2017-01-16): Fixed library.properties "url" field.
* 4.1.0 (2016-11-03): Changed the reset time from 50&nbsp;&mu;s to 80&nbsp;&mu;s to support the SK6812.
* 4.0.0 (2016-08-22): Updated library to work with the Arduino Library Manager.
* 3.2.0 (2014-08-27): Added support for AVRs running at 8 MHz (thanks odewdney).
* 3.1.2 (2014-06-10): Fixed a bug in the HSV-to-RGB conversion in the LedStripRainbow example.
* 3.1.1 (2014-01-07): Changed the examples to use `uint16_t` instead of `byte` for `i`, making it easier to expand them beyond 254 LEDs.
* 3.1.0 (2013-12-19): Added the LedStripXmas example.
* 3.0.0 (2013-11-20): Switched the red and the green channels and increased the reset time so that this library will work nicely with the new WS2812 and WS2182B LED strips.  The high-speed TM1804 LED strips still work if you switch red and green in your code.
* 2.1.0 (2013-11-11): Added the LedStripRainbow example.
* 2.0.0 (2013-10-07): Dropped support for the older, slower LED strips in order to make the library faster.
* 1.2.0 (2013-10-07): Changed the timing so that this library will work the new high-speed strips but also keep working with the old low-speed strips.
* 1.1.0 (2012-12-17): Added support for ATmega32U4-based boards such as the Arduino Leonardo.  Added support for ARM-based boards such as the Arduino Due.
* 1.0.0 (2012-03-09): Original release.
