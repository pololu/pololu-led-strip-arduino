This is an Arduino library for driving the addressable RGB LED strips from
Pololu.

It allows complete control over the color of an arbitrary number of LEDs.
This does bit-banging with inline assembly.
 
Running on a 16 MHz Arduino, this library takes about 1.5 ms to update 30 LEDs
(1 meter).  Interrupts must be disabled during that time, so any
interrupt-based library can be negatively affected by this function.
