#pragma once

#include <Arduino.h>

#if defined(__AVR__)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define __enable_irq sei
#define __disable_irq cli

#if !(F_CPU == 8000000 || F_CPU == 16000000 || F_CPU == 20000000)
#error "On an AVR, this version of the PololuLedStrip library only supports 8, 16 and 20 MHz."
#endif

#elif defined(__arm__)

#if !(F_CPU == 84000000)
#error "On an ARM, this version of the PololuLedStrip library only supports 84 MHz."
#endif

#endif

namespace Pololu
{
  #ifndef _POLOLU_RGB_COLOR
  #define _POLOLU_RGB_COLOR
  typedef struct rgb_color
  {
    unsigned char red, green, blue;
    rgb_color() {};
    rgb_color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {};
  } rgb_color;
  #endif

  class PololuLedStripBase
  {
    public:
    static bool interruptFriendly;
    void virtual write(rgb_color *, unsigned int count) = 0;
  };

  template<unsigned char pin> class PololuLedStrip : public PololuLedStripBase
  {
    public:
    void virtual write(rgb_color *, unsigned int count);
  };

  #if defined(__AVR_ATmega32U4__)
  // ATmega32U4-based boards such as the Arduino Leonardo

  const unsigned char pinBit[] =
  {
    2, 3, 1, 0, 4, 6, 7, 6,  // Pins 0-7
    4, 5, 6, 7, 6, 7,        // Pins 8-13
    3, 1, 2, 0,              // Pins 14-17
    7, 6, 5, 4, 1, 0,        // Pins 18-23
    4, 7, 4, 5, 6, 6,        // Pins 24-29
  };

  const unsigned char pinAddr[] =
  {
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTE),

    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTC),

    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),

    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),

    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTD),
  };

  #elif defined(__AVR__) && !defined(NUM_DIGITAL_PINS) || NUM_DIGITAL_PINS == 20
  // ATmega168/328-based boards such as the Arduino Uno or Baby Orangutan B-328

  const unsigned char pinBit[] =
  {
    0, 1, 2, 3, 4, 5, 6, 7,  // PORTD
    0, 1, 2, 3, 4, 5,        // PORTB
    0, 1, 2, 3, 4, 5, 6,     // PORTC
  };

  const unsigned char pinAddr[] =
  {
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
  };

  #elif defined(__AVR__) && NUM_DIGITAL_PINS == 70
  // ATmega2560-based boards such as the Arduino Mega 2560

  const unsigned char pinBit[] =
  {
    0, 1, 4, 5, 5, 3, 3, 4, 5, 6,
    4, 5, 6, 7, 1, 0, 1, 0, 3, 2,
    1, 0, 0, 1, 2, 3, 4, 5, 6, 7,
    7, 6, 5, 4, 3, 2, 1, 0, 7, 2,
    1, 0, 7, 6, 5, 4, 3, 2, 1, 0,
    3, 2, 1, 0, 0, 1, 2, 3, 4, 5,
    6, 7, 0, 1, 2, 3, 4, 5, 6, 7,
  };

  const unsigned char pinAddr[] =
  {
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTG),
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTJ),
    _SFR_IO_ADDR(PORTJ),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTG),
    _SFR_IO_ADDR(PORTG),
    _SFR_IO_ADDR(PORTG),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
  };

  #endif

  template<unsigned char pin> void __attribute__((aligned(16))) PololuLedStrip<pin>::write(rgb_color * colors, unsigned int count)
  {
    #if defined(__AVR__)
    digitalWrite(pin, LOW);
    pinMode(pin, OUTPUT);

    #elif defined(__arm__)
    Pio * port = g_APinDescription[pin].pPort;
    uint32_t pinValue = g_APinDescription[pin].ulPin;
    PIO_SetOutput(port, pinValue, LOW, 0, 0);

    #endif

    __disable_irq();   // Disable interrupts temporarily because we don't want our pulse timing to be messed up.

    while(count--)
    {
      // Send a color to the LED strip.
      // The assembly below also increments the 'colors' pointer,
      // it will be pointing to the next color at the end of this loop.
      #if defined(__AVR__)
      asm volatile(
        "ld __tmp_reg__, %a0+\n"         // Advance pointer from red to green.
        "ld __tmp_reg__, %a0\n"          // Read the green component and leave the pointer pointing to green.
        "rcall send_led_strip_byte%=\n"  // Send green component.
        "ld __tmp_reg__, -%a0\n"         // Read the red component and leave the pointer at red.
        "rcall send_led_strip_byte%=\n"  // Send green component.
        "ld __tmp_reg__, %a0+\n"         // Advance pointer from red to green.
        "ld __tmp_reg__, %a0+\n"         // Advance pointer from green to blue.
        "ld __tmp_reg__, %a0+\n"         // Read the blue component and leave the pointer on the next color's red.
        "rcall send_led_strip_byte%=\n"  // Send blue component.
        "rjmp led_strip_asm_end%=\n"     // Jump past the assembly subroutines.

        // send_led_strip_byte subroutine:  Sends a byte to the LED strip.
        "send_led_strip_byte%=:\n"
        "rcall send_led_strip_bit%=\n"  // Send most-significant bit (bit 7).
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"  // Send least-significant bit (bit 0).
        "ret\n"

        // send_led_strip_bit subroutine:  Sends single bit to the LED strip by driving the data line
        // high for some time.  The amount of time the line is high depends on whether the bit is 0 or 1,
        // but this function always takes the same time (2 us).
        "send_led_strip_bit%=:\n"
#if F_CPU == 8000000
        "rol __tmp_reg__\n"                      // Rotate left through carry.
#endif
        "sbi %2, %3\n"                           // Drive the line high.
#if F_CPU != 8000000
        "rol __tmp_reg__\n"                      // Rotate left through carry.
#endif

#if F_CPU == 16000000
        "nop\n" "nop\n"
#elif F_CPU == 20000000
        "nop\n" "nop\n" "nop\n" "nop\n"
#endif

        "brcs .+2\n" "cbi %2, %3\n"              // If the bit to send is 0, drive the line low now.

#if F_CPU == 8000000
        "nop\n" "nop\n"
#elif F_CPU == 16000000
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
#elif F_CPU == 20000000
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n"
#endif

        "brcc .+2\n" "cbi %2, %3\n"              // If the bit to send is 1, drive the line low now.

        "ret\n"
        "led_strip_asm_end%=: "
        : "=b" (colors)
        : "0" (colors),         // %a0 points to the next color to display
          "I" (pinAddr[pin]),   // %2 is the port register (e.g. PORTC)
          "I" (pinBit[pin])     // %3 is the pin number (0-8)
      );

      #elif defined(__arm__)
      asm volatile(
        "ldrb r12, [%0, #1]\n"    // Load green.
        "lsls r12, r12, #24\n"    // Put green in MSB of color register.
        "ldrb r3, [%0, #0]\n"     // Load red.
        "lsls r3, r3, #16\n"
        "orrs r12, r12, r3\n"     // Put red in color register.
        "ldrb r3, [%0, #2]\n"     // Load blue.
        "lsls r3, r3, #8\n"
        "orrs r12, r12, r3\n"     // Put blue in LSB of color register.
        "rbit r12, r12\n"         // Reverse the bits so we can use right rotations.
        "adds  %0, %0, #3\n"      // Advance pointer to next color.
    
        "mov r3, #24\n"           // Initialize the loop counter register.

        "send_led_strip_bit%=:\n"
        "str %[val], %[set]\n"            // Drive the line high.
        "rrxs r12, r12\n"                 // Rotate right through carry.

        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"

        "it cc\n" "strcc %[val], %[clear]\n"  // If the bit to send is 0, set the line low now.

        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"

        "it cs\n" "strcs %[val], %[clear]\n"  // If the bit to send is 1, set the line low now.

        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"

        "sub r3, r3, #1\n"                // Decrement the loop counter.
        "cbz r3, led_strip_asm_end%=\n"   // If we have sent 24 bits, go to the end.
        "b send_led_strip_bit%=\n"

        "led_strip_asm_end%=:\n"

      : "=r" (colors)
      : "0" (colors),
        [set] "m" (port->PIO_SODR),
        [clear] "m" (port->PIO_CODR),
        [val] "r" (pinValue)
      : "r3", "r12", "cc"
      );

      #endif

      if (PololuLedStripBase::interruptFriendly)
      {
        // Experimentally on an AVR we found that one NOP is required after the SEI to actually let the
        // interrupts fire.
        __enable_irq();
        asm volatile("nop\n");
        __disable_irq();
      }
    }
    __enable_irq();         // Re-enable interrupts now that we are done.
    delayMicroseconds(80);  // Send the reset signal.
  }

}

using namespace Pololu;
