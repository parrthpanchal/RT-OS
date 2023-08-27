
#ifndef __OS_KERNEL_H__
#define __OS_KERNEL_H__

#include "stm32f1xx.h"


#define MAX_NUM_OF_THREADS	4
#define STACK_SIZE		100

struct tcb {
	uint32_t *stack_ptr;
	struct tcb *nextPt;
};

typedef struct tcb tcb_t;


uint8_t os_kernel_add_threads(void (*)(void),void (*)(void),void (*)(void));
void os_kernel_init(void);
void os_thread_stack_init(uint8_t);

#endif
