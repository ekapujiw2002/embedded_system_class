#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>

#define PIN_LED PINC0
#define PIN_SW PIND2
#define PIN_SW2 PIND3
#define PIN_SW3 PIND7

uint8_t volatile cnt = 0;

ISR(INT0_vect) {
  PORTC ^= _BV(PIN_LED);

  cnt++;
}
// ISR(INT1_vect) { PORTC ^= _BV(PIN_LED); }
ISR_ALIAS(INT1_vect, INT0_vect);

ISR(PCINT2_vect) {
  // if (bit_is_set(PIND, PIN_SW3)) {
  //   PORTC |= _BV(PIN_LED);
  // } else {
  //   PORTC &= ~_BV(PIN_LED);
  // }
  PORTC ^= _BV(PIN_LED);
}

int main() {

  DDRB = 0xff;
  PORTB = 0;

  DDRC |= _BV(PIN_LED);
  PORTC &= ~_BV(PIN_LED);

  DDRD &= ~(_BV(PIN_SW) | _BV(PIN_SW2) | _BV(PIN_SW3));
  PORTD |= (_BV(PIN_SW) | _BV(PIN_SW2) | _BV(PIN_SW3));

  EICRA |= _BV(ISC01) | _BV(ISC11);
  EIMSK |= _BV(INT0) | _BV(INT1);
  EIFR |= _BV(INTF0) | _BV(INTF1);

  PCICR |= _BV(PCIE2);
  // PCIFR |= _BV(PCIF2);
  PCMSK2 |= _BV(PCINT23);

  sei();

  for (;;) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      PORTB = (cnt & 0x0f);
      if (cnt == 10) {
        cnt = 0;
      }

      // _delay_ms(100);
    }

    _delay_ms(20);
  }

  return 0;
}
