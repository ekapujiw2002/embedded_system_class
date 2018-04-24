#include <avr/io.h>
#include <util/delay.h>

// proto fucntion
void delay_timer0(const uint16_t delay_us_value);
void timer0_ctc();

/**
 * delay dengan timer0
 * @param delay_us_value delay dalam mikrodetik
 */
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
 * timer0 ctc mode
 */
void timer0_ctc() {
  // freq = xtal / (2*n*(1+ocr0a))
  // freq = 1khz
  // xtal = 16MHz
  // n = 64
  // ocr0a = (16Mhz/(2*64*1Khz)) - 1 = 124
  DDRD |= _BV(PIND5) | _BV(PIND6);
  OCR0A = 124;
  OCR0B = 124;
  TCCR0A = _BV(COM0A0) | _BV(COM0B0) | _BV(WGM01);
  TCCR0B = _BV(CS01) | _BV(CS00);
}

void timer0_fast_pwm_mode_3() {
  // freq = xtal / (N*TOP)
  DDRD |= _BV(PIND5) | _BV(PIND6);
  OCR0A = 128;
  OCR0B = 64;
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(CS02) | _BV(CS00);
}

void timer0_fast_pwm_mode_3_freq5khz() {
  // freq = xtal / (N*TOP)
  DDRD |= _BV(PIND5) | _BV(PIND6);
  OCR0A = 49;
  OCR0B = 25;
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(WGM02) | _BV(CS01) | _BV(CS00);
}

void timer0_phase_correct_pwm() {
  DDRD |= _BV(PIND5) | _BV(PIND6);
  OCR0A = 128;
  OCR0B = 64;
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);
  TCCR0B = _BV(CS02) | _BV(CS00);
}

void timer0_phase_correct_pwm_mode5() {
  DDRD |= _BV(PIND5) | _BV(PIND6);
  OCR0A = 49;
  OCR0B = 25;
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);
  TCCR0B = _BV(WGM02) | _BV(CS01) | _BV(CS00);
}

/**
 * delay dengan timer1
 * @param delay_us_value delay dalam mikrodetik
 */
void delay_timer1(const uint32_t delay_us_value) {

  uint16_t tcnt1_val = 65536 - (delay_us_value * (F_CPU / 1000000) / 1024);

  TCCR1A = 0;
  TIFR1 |= _BV(TOV1);
  TCCR1B = _BV(CS10) | _BV(CS12);
  TCNT1 = tcnt1_val;
  loop_until_bit_is_set(TIFR1, TOV1);
  TCCR1B = 0;
}

void timer1_ctc_mode12() {
  DDRB |= _BV(PINB1) | _BV(PINB2);
  ICR1 = 14;
  TCCR1A = _BV(COM1A0) | _BV(COM1B0);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS12) | _BV(CS10);
}

void timer1_ctc_mode4() {
  DDRB |= _BV(PINB1) | _BV(PINB2);
  OCR1A = 14;
  OCR1B = 0;
  TCCR1A = _BV(COM1A0) | _BV(COM1B0);
  TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);
}

void timer1_phase_and_freq_correct_pwm() {
  DDRB |= _BV(PINB1) | _BV(PINB2);
  ICR1 = 7999;
  OCR1A = 4000;
  OCR1B = 4000;
  TCCR1A = _BV(COM1A1) | _BV(COM1B1);
  TCCR1B = _BV(WGM13) | _BV(CS10);
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

  // timer0_ctc();
  // timer0_fast_pwm_mode_3();
  // timer0_fast_pwm_mode_3_freq5khz();
  // timer0_phase_correct_pwm();
  // timer0_phase_correct_pwm_mode5();
  // timer1_ctc_mode12();
  // timer1_ctc_mode4();
  // OCR1B = 7;
  // OCR1A = 5;
  timer1_phase_and_freq_correct_pwm();

  for (;;) {
    // PORTB ^= _BV(PINB0);
    // delay_timer1(1000);

    // TCNT0 = 100;
    // TCCR0A = 0;
    // TIFR0 |= _BV(TOV0);
    // TCCR0B = _BV(CS00) | _BV(CS02);
    // loop_until_bit_is_set(TIFR0, TOV0);
    // TCCR0B = 0;

    // _delay_us(10000);
    // delay_timer0(150);

    // OCR0A = 128;
    // OCR0B = 64;
    // _delay_ms(1000);
    // OCR0A = 64;
    // OCR0B = 192;
    // _delay_ms(1000);

    // OCR0A = 49;
    // _delay_ms(5000);
    // OCR0A = 24;
    // _delay_ms(5000);

    _delay_ms(3000);
    ICR1 = 2999;
    _delay_ms(3000);
    ICR1 = 15999;

  }

  return 0;
}
