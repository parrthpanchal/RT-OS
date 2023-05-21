#include"led.h"


#define GPIOCEN (1U<<4)
#define LED_PIN (1U<<13)

void vLEDInit(void) {

	/* Enable CLK for LED Port (Port C)*/
	RCC->APB2ENR |= GPIOCEN;

	/* Configure LED Pin(PC13) as output*/

	//Output mode, max speed 2 MHz
	GPIOC->CRH &= ~(1U<<20);
	GPIOC->CRH |= (1U<<21);

	// General purpose output Open-drain
	GPIOC->CRH &= ~(1U<<22);
	GPIOC->CRH &= ~(1U<<23);

}


void vLEDOn(void) {

	/* Turn LED Pin HIGH */
	GPIOC->ODR |= LED_PIN;
}


void vLEDOff(void) {

	/* Turn LED Pin LOW*/
	GPIOC->ODR &= ~LED_PIN;
}


void vLEDToggle(void) {

	/* Toggle the state of LED Pin(PC13)*/
}
