#include"led.h"
#include "stm32f1xx.h"

#define GPIOCEN (1U<<4)
#define LED_PIN (1U<<13)

void led_init(void) {

	/* Enable CLK for LED Port (Port C)*/
	RCC->APB2ENR |= GPIOCEN;

	/* Configure LED Pin(PC13) as output*/

	//Output mode, max speed 2 MHz
	GPIOC->CRH &= ~(1U << 20);
	GPIOC->CRH |= (1U << 21);

	// General purpose output Open-drain
	GPIOC->CRH &= ~(1U << 22);
	GPIOC->CRH &= ~(1U << 23);

}

void led_on(void) {

	/* Turn LED Pin HIGH */
	GPIOC->ODR |= LED_PIN;
}

void led_off(void) {

	/* Turn LED Pin LOW*/
	GPIOC->ODR &= ~LED_PIN;
}

void led_toggle(void) {

	/* Toggle the state of LED Pin(PC13)*/
}
