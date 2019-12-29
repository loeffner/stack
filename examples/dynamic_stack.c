#include <stdlib.h>
#include <stdio.h>
#include "../src/stack.h"

int main(int argc, char **argv)
{
    int i;
    int *popped;

    /* Initialize the static stack dynamically */
    STACK_HANDLE head = stack_init(-1);
    if(head)
    {
        /* Insert data: thirty integer pointers */
        for(i = 90; i < 120; i++)
        {
            int *data = (int*)malloc(sizeof(int));
            if(data)
            {
                *data = i;
                data = stack_push(head, (void*)data);
                if(data == STACK_OVERFLOW_ERROR)
                    printf("STACK OVERFLOW ERROR!\n");
                else
                    printf("Stacksize: %i\n", stack_getSize(head));
            }
            else
                printf("Memory Allocation Error while allocating the integer data! %p\n", data);  
        }
        /* remove the data from the stack */
        while(!stack_isEmpty(head))
        {
            popped = (int*)stack_pop(head);
            printf("size: %i\n", stack_getSize(head));
            printf("popped: %i\n", *popped);
            free(popped);
        }

        /* free the allocated memory */
        stack_free(head);
    }
    else
    {
        printf("STACK_HANDLE allocation failed.\n");
    }
    
    return 0;
}