#include<stdio.h>
#include<stdlib.h>

int top=-1;

int VerifCond(int x)
{
    if(x<=255)
        return 1;
    else
        return 0;

}

void push(int *stack, int x)
{
    if(top>8){
        printf("Stack overflow");
        exit(1);
    }
    *(stack+(++top))=x;
}

int get(int *stack) //function to retrieve top element of stack
{
    return *(stack+(top--));
}

//returns count of 1's
int dec2binS(int x, int *stack)
{
    int i,count=0;
    for(i=0;i<8;i++) //numarul este maxim 255 = 1111 1111
        if((x>>i)&1==1){
            push(stack,1);
            count++;
            }
        else
            push(stack,0);
    return count;
}

int maxNum(int count)
{
    int num=0, msb=1<<7, i; //not actually msb, force of habit to name it that
    for(i=0;i<8;i++){
        if(count>0){
            num=num^msb;
        }
    msb>>=1;
    count--;
    }
    return num;
}

void printStack(int *stack)
{
    int i;
    for(i=0;i<8;i++)
        if(i%4==0 && i){
            printf(" ");
            printf("%d",get(stack));
        }
        else
            printf("%d",get(stack));
    
}

int main()
{
    int i,x=0,count;
    int *stack=(int*)malloc(9*sizeof(int));
    do{
        if(VerifCond(x)==0)
            printf("X trebuie sa fie <= 255\n");
    printf("x=");scanf("%d",&x);
    }while(VerifCond(x)==0);

    count=dec2binS(x,stack);
    printf("Stack initial= ");
    printStack(stack);       
    printf("\n");

    x=maxNum(count);
    
    dec2binS(x,stack);
    printf("Valoare maxima= ");
    printStack(stack);
    printf("  in zecimal= %d\n",x);
    return 0;
}