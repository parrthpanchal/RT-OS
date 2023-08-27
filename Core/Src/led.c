#include"led.h"
#include "stm32f1xx.h"

#define GPIOCEN (1U<<4)
#define GPIOAEN (1U<<2)
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

void config_ext_leds(void) {

	/* Enable CLK for PortA*/
	RCC->APB2ENR |= GPIOAEN;

	/* PA11 and PA12 pin config */
	GPIOA->CRH &= ~(1U << 12);
	GPIOA->CRH |= (1U << 13);
	GPIOA->CRH &= ~(1U << 14);
	GPIOA->CRH &= ~(1U << 15);

	GPIOA->CRH &= ~(1U << 16);
	GPIOA->CRH |= (1U << 17);
	GPIOA->CRH &= ~(1U << 18);
	GPIOA->CRH &= ~(1U << 19);
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
