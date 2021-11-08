#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


#include "Stack.h"

/*
    Create a stack of given capacity.  It initializes size of
    stack as 0

    Parameters:
    unsigned int capacity -> value that will be the size of stack

    Return:
    Stack* -> a pointer to created stack in memory
*/
Stack* createStack(unsigned capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (float*)malloc(stack->capacity * sizeof(float));
    return stack;
}
 

/*
    Check if stack is full

    Parameters:
    Stack* stack -> reference to the stack

    Return:
    int -> flag that indicates true or false (0 for false, and true otherwise)
*/
int isFull(Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 

/*
    Check if stack is empty

    Parameters:
    Stack* stack -> reference to the stack

    Return:
    int -> flag that indicates true or false (0 for false, and true otherwise)
*/
int isEmpty(Stack* stack)
{
    return stack->top == -1;
}
 

/*
    Inserts a item in the stack

    Parameters:
    Stack* stack -> reference to the stack
    flaot item -> item to be inserted on top of stack
*/
void push(Stack* stack, float item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    //printf("%f pushed to stack\n", item);
}
 

/*
    Remove an item from stack.  It decreases top by 1

    Parameters:
    Stack* stack -> reference to the stack
    
    Return:
    int -> item from top of stack
*/
float pop(Stack* stack)
{
    if (isEmpty(stack))
        return (float)INT_MIN;
    return stack->array[stack->top--];
}
 

/*
    Return top from the stack without removing it

    Parameters:
    Stack* stack -> reference to the stack
    
    Return:
    int -> item from top of stack
*/
float peek(Stack* stack)
{
    if (isEmpty(stack))
        return (float)INT_MIN;
    return stack->array[stack->top];
}