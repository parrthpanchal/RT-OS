#include <stdint.h>
#include "uart.h"
#include "stm32f1xx.h"

#define SYS_CLK 8000000U
#define APB2_CLK SYS_CLK
#define UART1_BAUDRATE 115200U

#define CR1_TE (1U << 3)
#define CR1_UE (1U << 13)
#define UART1_EN (1U << 14)
#define GPIOA_EN (1U << 2)
#define SR_TXE (1U << 7)

#define COMPUTE_BR(pclk,br) ((pclk + (br/2U)) / br)
#define IS_TDR_EMPTY() (USART1->SR & SR_TXE)

int __io_putchar(int ch) {

	uart_tx(ch);
	return ch;
}

void uart_init(void) {

	/* Enable clock access for GPIOA */
	RCC->APB2ENR |= GPIOA_EN;

	/* Set PA9 and PA10 to alternate function mode */
	GPIOC->CRH &= ~(1U << 4);
	GPIOC->CRH |= (1U << 5);
	GPIOC->CRH |= (1U << 6);
	GPIOC->CRH |= (1U << 7);
	AFIO->MAPR2 &= ~(1U << 2);

	/* Enable the clock for UART1*/
	RCC->APB2ENR |= UART1_EN;

	/* Configure Baud rate */
	USART1->BRR = COMPUTE_BR(APB2_CLK, UART1_BAUDRATE);
	/* Enable Tx for USART1 */
	USART1->CR1 |= CR1_TE;

	/* Enable USART1 */
	USART1->CR1 |= CR1_UE;

}

void uart_tx(uint8_t data) {

	/* Wait till TDR gets empty */
	while (!IS_TDR_EMPTY()) {
	}

	/* Write the data into the TDR */
	USART1->DR = data;

}

