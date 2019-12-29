/* 
Tower of Hanoi is a mathematical puzzle. 
It consists of three poles and a number of disks of different sizes which can slide onto any poles. 
The puzzle starts with the disk in a neat stack in ascending order of size in one pole,
the smallest at the top thus making a conical shape. 
The objective of the puzzle is to move all the disks from one pole (say ‘source pole’)
to another pole (say ‘destination pole’)
with the help of the third pole (say auxiliary pole).

The puzzle has the following two rules:

      1. You can’t place a larger disk onto smaller disk
      2. Only one disk can be moved at a time
*/

#include <stdio.h>
#include "../src/stack.h"

#define NR_DISKS 3

/* Function to print the performed action */
void print_action(char s, char d, int *disk)
{
    printf("Moved Disk %d from %c to %c\n", *disk, s, d);
}

/* Visualize towers */
void print_towers(STACK_HANDLE src, STACK_HANDLE dest, STACK_HANDLE aux, char s, char d, char a)
{
    int i;
    printf("\n");
    for(i = NR_DISKS - 1; i >= 0; i--)
    {
        if(src->top >= i)
            printf("%d", *(int*)src->stack[i]);
        else
            printf("|");
        printf("\t");
        if(aux->top >= i)
            printf("%d", *(int*)aux->stack[i]);
        else
            printf("|");
        printf("\t");
        if(dest->top >= i)
            printf("%d", *(int*)dest->stack[i]);
        else
            printf("|");
        printf("\n");
    }
    printf("%c\t%c\t%c\n", s, a, d);
}

/* Function to implement legal movement between two towers */
void moveDisk(STACK_HANDLE src, STACK_HANDLE dest, char s, char d)
{  
    /* When src is empty */
    if (stack_isEmpty(src) && !stack_isEmpty(dest))  
    {  
        stack_push(src, stack_pop(dest));  
        print_action(d, s, stack_peek(src));  
    }  
  
    /* When dest is empty */
    else if (stack_isEmpty(dest) && !stack_isEmpty(src))  
    {  
        stack_push(dest, stack_pop(src));  
        print_action(s, d, stack_peek(dest));  
    }  
  
    /* When top disk of src > top disk of dest */
    else if (*(int*)stack_peek(src) > *(int*)stack_peek(dest))  
    {      
        stack_push(src, stack_pop(dest));
        print_action(d, s, stack_peek(src));  
    }  
  
    /* When top disk of src < top disk of dest */
    else if (*(int*)stack_peek(dest) > *(int*)stack_peek(src))
    {  
        stack_push(dest, stack_pop(src));
        print_action(s, d, stack_peek(dest));  
    }
}  

int main(void)
{
    STACK_HANDLE src, dest, aux;
    int i, total_num_of_moves;  
    char s = 'S', d = 'D', a = 'A';  
 
    src = stack_init(NR_DISKS);
    dest = stack_init(NR_DISKS);
    aux = stack_init(NR_DISKS);
 
    /* If number of disks is even, then interchange destination pole and auxiliary pole */
    if (NR_DISKS % 2 == 0)  
    {  
        char temp = d;  
        d = a;  
        a = temp;  
    }  
    total_num_of_moves = NR_DISKS * NR_DISKS - 1;  
  
    /* Larger disks will be pushed first */
    for (i = NR_DISKS; i > 0; i--)  
    {
        int *disk = malloc(sizeof(int*));
        *disk = i;
        stack_push(src, disk);  
    }

    for (i = 1; i <= total_num_of_moves; i++)  
    {  
        print_towers(src, dest, aux, s, d, a);
        if (i % 3 == 1)  
        {
            moveDisk(src, dest, s, d);  
        }
        else if (i % 3 == 2)  
        {
            moveDisk(src, aux, s, a);  
        }
        else if (i % 3 == 0)  
        {
            moveDisk(aux, dest, a, d);  
        }
    } 
    print_towers(src, dest, aux, s, d, a); 
    return 0;
}