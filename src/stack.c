/* This data structure only handles (void) pointers. The user has to take care of managing them
 * Currently an error code is indistinguishable from a void* data e.g. in stack_pop.
 * TODO: fix this. Idea: Let the user provide a storage location for the result and return a bool (or int)
 * TODO: malloc on the variable name
 */

#include "stack.h"

/* create a handle and allocate an array of void pointers, if capacity <= 0 memory will be dynamically allocated*/
STACK_HANDLE stack_init(int capacity)
{
    STACK_HANDLE stack = malloc(sizeof(Stack));
    if(stack)
    {
        if(capacity <= 0)
        {
            stack->capacity = STACK_CAPACITY_INITIAL;
            stack->dynamic = 1;
        }
        else
        {
            stack->capacity = capacity;
            stack->dynamic = 0;
        }
        stack->top = -1;

        stack->stack = malloc(stack->capacity * sizeof(void*));
        if(!stack->stack)
        {
            free(stack);
            stack = STACK_MEM_ERROR;
        }
    }
    return stack;
}

/* free all allocated memory */
void *stack_free(STACK_HANDLE stack)
{
    free(stack->stack);
    free(stack);
    return NULL;
}

/* returns true if the stack is empty */
int stack_isEmpty(STACK_HANDLE stack)
{
    return stack->top == -1;
}

/* returns true if the stack is full, if dynamic stack more memory will be allocated at the next push */
int stack_isFull(STACK_HANDLE stack)
{
    return stack->top == stack->capacity - 1;
}

/* returns the size of the stack */
int stack_getSize(STACK_HANDLE stack)
{
    return stack->top + 1;
}

/* returns the capacity of the stack */
int stack_getCapacity(STACK_HANDLE stack)
{
    return stack->capacity;
}

/* adds an element to the stack and returns the pointer to it; 
   if stack is full returns STACK_OVERFLOW_ERROR or dynamically allocates more memory*/
void *stack_push(STACK_HANDLE stack, void *data)
{
    void **temp;
    void *ret = STACK_OVERFLOW_ERROR;
    int new_capacity;

    if(!stack_isFull(stack))
    {
        ret = data;
        stack->stack[++(stack->top)] = data;
    }
    else
    {
        if(stack->dynamic)
        {
            new_capacity = stack->capacity * STACK_CAPACITY_MULTIPLIER;
            temp = realloc(stack->stack, new_capacity * sizeof(void*));
            if(!temp)
            {
                ret = STACK_MEM_ERROR;
                /* Resizing failed, stack did not grow */
            }
            else
            {
                stack->stack = temp;
                stack->capacity = new_capacity;
                ret = stack_push(stack, data);
            }
        }
    }
    return ret;
}

/* removes the last element from the stack and returns it;
   if stack is empty return STACK_EMPTY_ERROR */
void *stack_pop(STACK_HANDLE stack)
{
    void **temp;
    void *top = STACK_EMPTY_ERROR;
    int new_capacity;
    if(!stack_isEmpty(stack))
    {
        top = stack->stack[stack->top];
        stack->stack[(stack->top)--] = NULL;
        if(stack->top < stack->capacity / (2 * STACK_CAPACITY_MULTIPLIER))
        {
            new_capacity = stack->capacity / STACK_CAPACITY_MULTIPLIER;
            temp = realloc(stack->stack, new_capacity * sizeof(void*));
            if(!temp)
            {
                /* Resizing failed, stack still usable */
            }
        }
    }
    return top;
}

/* returns the last element from the stack;
   if stack is empty returns STACK_EMPTY_ERROR */
void *stack_peek(STACK_HANDLE stack)
{
    if(!stack_isEmpty(stack))
        return stack->stack[stack->top];
    else
        return STACK_EMPTY_ERROR;
}

/* swap the last two elements from two stacks */
void stack_swap(STACK_HANDLE a, STACK_HANDLE b)
{
    if(stack_isEmpty(a) && !stack_isEmpty(b))
    {
        stack_push(a, stack_pop(b));
    }
    else if(stack_isEmpty(b) && !stack_isEmpty(a))
    {
        stack_push(b, stack_pop(a));
    }
    else if(!stack_isEmpty(b) && !stack_isEmpty(a))
    {
        void *temp;
        temp = stack_pop(b);
        stack_push(b, stack_pop(a));
        stack_push(a, temp);
    }
}