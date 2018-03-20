#include <avr/io.h>
#include <util/delay.h>

#include <usart-lib.h>

/**
 * main program
 * @return main program start here
 */
int main() {

  /*
  init serial port 0
   */
  USART_InitFast(BAUD_9600, COM_CH0);
  // USART_Transmit('*', COM_CH0);
  // uint8_t dx = USART_Receive(COM_CH0);
  // USART_Transmit(dx, COM_CH0);
  USART_Transmit_String("SERIAL PORT DEMO\r\n2018\r\n", COM_CH0);

  USART_SetStdout();
  // printf("%04d\r\n", dx);

  int8_t dx = 0;
  char buf_rx[21], buf_tx[20];

  for (;;) {
    // printf("%4d\r\n", dx++);
    // _delay_ms(100);
    USART_Transmit_String("\r\nID : ", COM_CH0);
    USART_Receive_String(buf_rx, sizeof(buf_rx), COM_CH0);
    USART_Transmit_String("\r\nID SET TO ", COM_CH0);
    USART_Transmit_String(buf_rx, COM_CH0);
  }
  return 0;
}
