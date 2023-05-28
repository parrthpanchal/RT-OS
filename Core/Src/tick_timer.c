#include<stdint.h>
#include "tick_timer.h"
#include "stm32f1xx.h"

#define PRE_LOAD 8000000U
#define CTRL_EN (1U << 0)
#define CTRL_CLK_SRC (1U << 2)
#define CTRL_TICKINT (1U << 1)
#define CTRL_COUNT (1U << 16)
#define INC_TICK() (current_tick += tick_freq)
#define MAX_DELAY 0xFFFFFFFFU

volatile uint32_t current_tick = 0;
volatile uint32_t current_tick_p = 0;
uint32_t tick_freq = 1;


void delay(uint32_t delay) {

	uint32_t tick_start = get_tick();
	uint32_t wait = delay;

	if(wait < MAX_DELAY) {

		wait += tick_freq;
	}

	while((get_tick() - tick_start) < wait){}

}

void tick_timer_init(void) {

	SysTick->LOAD = PRE_LOAD - 1;

	/* Clear Systick current value reg */
	SysTick->VAL = 0;

	/* Select CLK source as internal for systick */
	SysTick->CTRL |= CTRL_CLK_SRC;

	/* Enable tick INT */
	SysTick->CTRL |= CTRL_TICKINT;

	/* Enable systick timer */
	SysTick->CTRL |= CTRL_EN;

	/* Enable global INT */
	__enable_irq();
}

uint32_t get_tick(void) {

	__disable_irq();
	current_tick_p = current_tick;
	__enable_irq();

	return current_tick_p;
}

void SysTick_Handler(void) {

	INC_TICK();

}
