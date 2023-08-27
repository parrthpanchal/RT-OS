#include<stdint.h>
#include "os_kernel.h"
#include "tick_timer.h"

#define PENDSV_PRIORITY 0xFFU
#define PENDSV_PRIORITY_REG 10U

tcb_t tcb_queue[MAX_NUM_OF_THREADS];
tcb_t* current_thread;

/* Each thread will have a stack of 400 bytes */
uint32_t thread_stack[MAX_NUM_OF_THREADS][STACK_SIZE];

void os_thread_stack_init(uint8_t i) {

	tcb_queue[i].stack_ptr = &thread_stack[i][STACK_SIZE - 16];

	/* Set T bit in PSR to operate in thumb mode */
	thread_stack[i][STACK_SIZE - 1] = (1U << 24); /* xPSR */
	thread_stack[i][STACK_SIZE - 3] = 0xAAAAAAAA; /* LR (R14) */
	thread_stack[i][STACK_SIZE - 4] = 0xAAAAAAAA; /* R12 */
	thread_stack[i][STACK_SIZE - 5] = 0xAAAAAAAA; /* R3 */
	thread_stack[i][STACK_SIZE - 6] = 0xAAAAAAAA; /* R2 */
	thread_stack[i][STACK_SIZE - 7] = 0xAAAAAAAA; /* R1 */
	thread_stack[i][STACK_SIZE - 8] = 0xAAAAAAAA; /* R0 */
	thread_stack[i][STACK_SIZE - 9] = 0xAAAAAAAA; /* R11 */
	thread_stack[i][STACK_SIZE - 10] = 0xAAAAAAAA; /* R10 */
	thread_stack[i][STACK_SIZE - 11] = 0xAAAAAAAA; /* R9 */
	thread_stack[i][STACK_SIZE - 12] = 0xAAAAAAAA; /* R8 */
	thread_stack[i][STACK_SIZE - 13] = 0xAAAAAAAA; /* R7 */
	thread_stack[i][STACK_SIZE - 14] = 0xAAAAAAAA; /* R6 */
	thread_stack[i][STACK_SIZE - 15] = 0xAAAAAAAA; /* R5 */
	thread_stack[i][STACK_SIZE - 16] = 0xAAAAAAAA; /* R4 */

}

uint8_t os_kernel_add_threads(void (*thread0_func)(void),void (*thread1_func)(void),void (*thread2_func)(void)) {

	/* Disable global interrupts */
	__disable_irq();
	tcb_queue[0].nextPt = &tcb_queue[1];
	tcb_queue[1].nextPt = &tcb_queue[2];
	tcb_queue[2].nextPt = &tcb_queue[0];

	os_thread_stack_init(0);
	thread_stack[0][STACK_SIZE - 2] = (uint32_t)thread0_func;

	os_thread_stack_init(1);
	thread_stack[1][STACK_SIZE - 2] = (uint32_t)thread1_func;

	os_thread_stack_init(2);
	thread_stack[2][STACK_SIZE - 2] = (uint32_t)thread2_func;

	current_thread=&tcb_queue[0];

	/* Enable global interrupts */
	__enable_irq();

	return 1;
}

uint8_t os_scheduler_launch(void) {

	/*Load address of currentPt into R0*/
	__asm("LDR R0,=current_thread");

	/*Load r2 from address equals r0,i.e r2 =currentPt*/
	__asm("LDR R2,[r0]");

	/*Load Cortex-M SP from address equals R2,i.e. SP = current_thread->stackPt*/
	__asm("LDR  SP,[R2]");

	/*Restore r4,r5,r6,r7,r8,r9,r10,r11*/
	__asm("POP {R4-R11}");

	/*Restore r12*/
	__asm("POP {R12}");

	/*Restore r0,r1,r2,r3*/
	__asm("POP	{R0-R3}");

	/*Skip LR */
	__asm("ADD  SP,SP,#4");

	/*Create a new start location by popping LR*/
	__asm("POP {LR}");

	/*Skip PSR by adding 4 to SP*/
	__asm("ADD  SP,SP,#4");

	/*Enable global interrupts*/
	__asm("CPSIE	I");

	/*Return from exception*/
	__asm("BX	LR");
}

void os_kernel_init(void) {

	// Configure the tick timer
	__disable_irq();
	tick_timer_init();
	NVIC_SetPriority(SysTick_IRQn,15);
	os_scheduler_launch();
}


__attribute__((naked)) void SysTick_Handler(void) {

	/*SUSPEND CURRENT THREAD*/

	/*Disable global interrupts*/
	__asm("CPSID	I");

	/*Save r4,r5,r6,r7,r8,r9,r10,11*/
	__asm("PUSH  {R4-R11}");

	/*Load address of current_thread into r0*/
	__asm("LDR R0, =current_thread");

	/*Load r1 from address equals r0, i.e. r1 =currentPt*/
	__asm("LDR R1,[R0]");

	/*Store Cortex-M SP at address equals r1, i.e Save SP into tcb */
	__asm("STR SP,[R1]");

	/*CHOOSE NEXT THREAD*/

	/*Load r1 from a location 4bytes above address r1, i.e r1 = current_thread->next*/
	__asm("LDR R1,[R1,#4]");

	/*Store r1 at address equals r0, i.e currentPt =  r1*/
	__asm("STR	R1,[R0]");

	/*Load Cortex-M SP from address equals r1, i.e SP =  current_thread->stackPt*/
	__asm("LDR SP,[R1]");

	/*Restore r4,r5,r6,r7,r8,r9,r10,11*/
	__asm("POP {R4-R11}");

	/*Enable global interrupts*/
	__asm("CPSIE	I");

	/*Return from exception and restore r0,r1,r2,r3,r12,lr,pc,psr */
	__asm("BX	LR");
}
