#include <avr/io.h>
#include <util/delay.h>

#define PIN_OUT PINC0
#define PIN_OUT4 PINC4
#define PIN_OUT5 PINC5
#define PIN_IN PINC1

int main() {

  // set sbg output
  DDRC |= _BV(PIN_OUT) | _BV(PIN_OUT4) | _BV(PIN_OUT5);
  PORTC &= ~(_BV(PIN_OUT) | _BV(PIN_OUT4) | _BV(PIN_OUT5));

  // set sbg input dg pullup
  DDRC &= ~(_BV(PIN_IN));
  PORTC |= _BV(PIN_IN);

  // DDRC = 0b00000001;

  // while (1) {
  //
  // }

  for (;;) {
    // PORTC |= _BV(PIN_OUT);
    // _delay_ms(500);
    // PORTC &= ~_BV(PIN_OUT);
    // _delay_ms(500);

    PORTC ^= _BV(PIN_OUT) | _BV(PIN_OUT4);

    if (bit_is_clear(PINC, PIN_IN)) {
      PORTC |= _BV(PIN_OUT5);
      loop_until_bit_is_set(PINC, PIN_IN);
      PORTC &= ~_BV(PIN_OUT5);
    }
    _delay_ms(500);
  }

  return 0;
}
