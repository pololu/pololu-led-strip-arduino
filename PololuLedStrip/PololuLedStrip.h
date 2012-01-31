#ifndef _POLOLU_LED_STRIP_H
#define _POLOLU_LED_STRIP_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Arduino.h>

namespace Pololu
{
  #ifndef _POLOLU_RGB_COLOR
  #define _POLOLU_RGB_COLOR
  typedef struct rgb_color
  {
    unsigned char red, green, blue;
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

  template<unsigned char pin> void PololuLedStrip<pin>::write(rgb_color * colors, unsigned int count)
  {
    digitalWrite(pin, LOW);
    pinMode(pin, OUTPUT);

    cli();   // Disable interrupts temporarily because we don't want our pulse timing to be messed up.
    while(count--)
    {
      // Send a color to the LED strip.
      // The assembly below also increments the 'colors' pointer,
      // it will be pointing to the next color at the end of this loop.
      asm volatile(
        "rcall send_led_strip_byte%=\n"  // Send red component.
        "rcall send_led_strip_byte%=\n"  // Send green component.
        "rcall send_led_strip_byte%=\n"  // Send blue component.
        "rjmp led_strip_asm_end%=\n"     // Jump past the assembly subroutines.

        // send_led_strip_byte subroutine:  Sends a byte to the LED strip.
        "send_led_strip_byte%=:\n"
        "ld __tmp_reg__, %a0+\n"      // Read the next color brightness byte and advance the pointer
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
        "sbi %2, %3\n"                           // Drive the line high.
        "rol __tmp_reg__\n"                      // Rotate left through carry.
        "nop\n" "nop\n" "nop\n" "nop\n"
        "brcs .+2\n" "cbi %2, %3\n"              // If the bit to send is 0, drive the line low now.    
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
        "nop\n" "nop\n"
        "brcc .+2\n" "cbi %2, %3\n"              // If the bit to send is 1, drive the line low now.
        "nop\n"
        "ret\n"
        
        "led_strip_asm_end%=: "
        : "=b" (colors)
        : "0" (colors),         // %a0 points to the next color to display
          "I" (pinAddr[pin]),   // %2 is the port register (e.g. PORTC)
          "I" (pinBit[pin])     // %3 is the pin number (0-8)
      );
      
      // Experimentally we found that one NOP is required after the SEI to actually let the
      // interrupts fire.
      if (PololuLedStripBase::interruptFriendly)
      {
        sei();
        asm volatile("nop\n");
        cli();
      }
    }
    sei();   // Re-enable interrupts now that we are done.
    _delay_us(15);  // Hold the line low for 15 microseconds to send the reset signal.
  }

}

using namespace Pololu;

#endif