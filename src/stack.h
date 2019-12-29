#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>

#ifndef NULL
#define NULL ((void*)0)
#endif /* NULL */

#define STACK_MEM_ERROR NULL
#define STACK_OVERFLOW_ERROR NULL
#define STACK_EMPTY_ERROR NULL

#define STACK_CAPACITY_INITIAL 16
#define STACK_CAPACITY_MULTIPLIER 2

/* struct to manage a static stack */
typedef struct stack_t
{
    int top;
    unsigned int capacity;
    unsigned int dynamic;
    void **stack;
} Stack;

typedef Stack* STACK_HANDLE;


/* initialize and free the stack */
STACK_HANDLE stack_init(int);
void *stack_free(STACK_HANDLE);
/* get information */
int stack_isEmpty(STACK_HANDLE);
int stack_isFull(STACK_HANDLE);
int stack_getSize(STACK_HANDLE);
int stack_getCapacity(STACK_HANDLE);
/*  interact */
void *stack_push(STACK_HANDLE, void*);
void *stack_pop(STACK_HANDLE);
void *stack_peek(STACK_HANDLE);
void stack_swap(STACK_HANDLE, STACK_HANDLE);

#endif /* _STACK_H_ */