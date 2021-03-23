#include<stdio.h>
#include<stdlib.h>

int isFull(int *top)
{
    if(*top>=7)
        return 1;
    return 0;
}

int isEmpty(int *top)
{
    if(*top==-1)
        return 1;
    return 0;
}

int peek(int *stack,int *top)
{
    return *(stack+*top);
}

void push(int *stack, int*top, int x)
{
    if(isFull(top)){
        printf("Stack is full");
        exit(1);
    }
    *top+=1;
    *(stack+*top)=x;
}

void pop(int *stack,int *top)
{
    *(stack+*top)=-1;
    *top-=1;
}

void readSt(int *stack, int*top)
{
    int i,x;
    printf("Introduceti 7 elemente de tip int:\n");
    for(i=0;i<7;i++){
        scanf("%d",&x);
        push(stack,top,x);
    }
}

void printSt(int *stack,int *top)
{
    while(*top){
       printf("%d ", peek(stack,top)); 
        pop(stack,top);
    }
}
int main()
{
    int *stack, *top=(int*)malloc(sizeof(int));
    stack=(int*)malloc(7*sizeof(int));
    readSt(stack,top);
    printSt(stack,top);
    
    return 0;
}