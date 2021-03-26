#include<stdio.h>
#include<stdlib.h>


//pushes elem into stack as long as top<stackLim
void push(int *stack, int*top, int stackLim,int elem)
{
    if(*top>stackLim){
        fprintf(stderr,"%s","Stack overflow");
        exit(1);
    }
    *top+=1;
    *(stack+*top)=elem;
}

//Pop that returns top element from stack, doesn't delete values or reallocates memory
int peekPop(int *stack,int *top)
{
    if(*top==-1){
        printf("Stiva este goala");
        exit(1);
    }
    *top-=1;
    return *(stack+*top+1);
}
//saves binary form of n into stack, also prints binary form of n
void dec2bin(int n, int*stack, int*top)
{
    int i,msb16=1<<(4*sizeof(int)-1),isPop=0;
    for(i=0;i<16;i++){
        if(n<<i & msb16){
            isPop=1;
            printf("1");
            push(stack,top,sizeof(stack),1);
        }
        else if(isPop==1){
            printf("0");
            push(stack,top,sizeof(stack),0);
        }
    }
}
//returns 1 if stack is palindrome
int checkStack(int*stack,int *top)
{
    int i=0;
    while(*top){
        if(*(stack+i)!=*(stack+*top))
            return 0;
        i++; peekPop(stack,top);
    }
    return 1;
}

void printStack(int*stack,int*top)
{
    int cpt=*top;
    while(*top!=-1)
        printf("%d",peekPop(stack,top));
    *top=cpt;
}

void freeMem(int*stack1,int*top1,int*stack2,int*top2)
{
    free(stack1);
    free(stack2);
    free(top1);
    free(top2);
}
int main()
{
    int *stack1,*stack2=(int*)malloc(16*sizeof(int)),n=0;
    int *top1=(int*)malloc(sizeof(int)),*top2=(int*)malloc(sizeof(int)),cn;
    *top1=-1;*top2=-1;
    do{
        printf("n=");
        if(n>65535)
            printf("Numarul trebuie sa fie < 65535\n");
        scanf("%d",&n);
    }while(n>65535);
    cn=n;    
    stack1=(int*)malloc(5*sizeof(int));
    while(n){
        *top1+=1;
        *(stack1+*top1)=n%10;
        n/=10;
    }
    printf("%d = ",cn); dec2bin(cn,stack2,top2); printf(" (binary) - ");
    if(checkStack(stack1,top1)==1 && checkStack(stack2,top2)==1)
        printf("PALINDROM\n");
    else
        printf("nu este palindrom\n");
    freeMem(stack1,top1,stack2,top2);
    return 0;
}