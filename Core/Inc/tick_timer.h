#ifndef __TICK_TIMER_H__
#define  __TICK_TIMER_H__


void tick_timer_init(void);
void SysTick_Handler(void);
uint32_t get_tick(void);
void delay(uint32_t);


#endif
