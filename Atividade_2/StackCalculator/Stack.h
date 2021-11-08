
#ifndef STACK_H_
#define STACK_H_

typedef struct
{
    int top;
    unsigned capacity;
    float* array;
}Stack;

Stack* createStack(unsigned capacity);
int isFull(Stack* stack);
int isEmpty(Stack* stack);
void push(Stack* stack, float item);
float pop(Stack* stack);
float peek(Stack* stack);

#endif /* STACK_H_ */