#include<stdint.h>
#include "os_kernel.h"



tcb_t tcb_queue[NUM_OF_THREADS];
tcb_t *current_thread;


/* Each thread will have a stack of 400 bytes */
uint32_t thread_stack[NUM_OF_THREADS][STACK_SIZE];
uint32_t num_of_threads = 0;



void os_thread_stack_init(uint8_t i) {

	tcb_queue[i].stack_ptr = &thread_stack[i][STACK_SIZE - 16];


	/* Set T bit in PSR to operate in thumb mode */
	thread_stack[i][STACK_SIZE - 1] = (1U << 21); /* xPSR */

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

uint8_t os_kernel_add_thread(void (*thread_func)(void)) {

	/* Disable global interrupts */
	__disable_irq();



	/* Enable global interrupts */
	__enable_irq();

	return 0;
}

void os_kernel_init(void) {

}

