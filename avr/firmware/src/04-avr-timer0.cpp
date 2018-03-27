#include <avr/io.h>
#include <util/delay.h>

void delay_timer0(const uint16_t delay_us_value) {

  uint16_t tcnt0_val = 256 - (delay_us_value * (F_CPU / 1000000) / 1024);
  // if (tcnt0_val<256) {
  //   //kalkulasi untuk psc lain
  // }

  TCCR0A = 0;
  TIFR0 |= _BV(TOV0);
  TCCR0B = _BV(CS00) | _BV(CS02);
  TCNT0 = tcnt0_val;
  loop_until_bit_is_set(TIFR0, TOV0);
  TCCR0B = 0;
}
/**
 * main program
 * @return main program start here
 */
int main() {

  // setup timer0
  // delay = 10ms
  // psc = 1024
  // nilai tcnt0 = 100
  // mode normal

  DDRB |= _BV(PINB0);

  for (;;) {
    PORTB ^= _BV(PINB0);

    // TCNT0 = 100;
    // TCCR0A = 0;
    // TIFR0 |= _BV(TOV0);
    // TCCR0B = _BV(CS00) | _BV(CS02);
    // loop_until_bit_is_set(TIFR0, TOV0);
    // TCCR0B = 0;

    // _delay_us(10000);
    delay_timer0(150);
  }

  return 0;
}
