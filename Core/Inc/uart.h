#ifndef __UART_H__
#define __UART_H__


void uart_init(void);
void uart_tx(uint8_t data);
uint8_t uart_rx(uint8_t* data);

#endif
