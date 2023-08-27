#include<stdio.h>
#include<stdint.h>
#include "led.h"
#include "uart.h"
#include "tick_timer.h"
#include "os_kernel.h"
#include "stm32f1xx.h"


void thread1(void) {

	 while(1) {
		 for (int i=0; i<1000; i++);
		 GPIOA->ODR |= LED_R;

		 for (int i=0; i<1000; i++);
		 GPIOA->ODR &= ~LED_R;
	 }

}

void thread2(void) {

	 while(1) {
		 for (int i=0; i<100000; i++);
		 GPIOA->ODR |= LED_G;

		 for (int i=0; i<100000; i++);
		 GPIOA->ODR &= ~LED_G;
	 }
}

void thread3(void) {

	while(1) {

		 for (int i=0; i<1000000; i++);
		 GPIOC->ODR |= LED_B;

		 for (int i=0; i<1000000; i++);
		 GPIOC->ODR &= ~LED_B;
	}

}

int main(){

	led_init();
	config_ext_leds();

	os_kernel_add_threads(thread1,thread2,thread3);
	os_kernel_init();

	while(1) {


	}

}
