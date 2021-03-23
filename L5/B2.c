#include<stdio.h>
#include<stdlib.h>

#define varname(name) #name
#define citireD(x) printf("%s=",varname(x)); scanf("%d",&x)
int top=-1;

void push(int *stack, int x, int n)
{
    if(top>n){
        fprintf(stderr,"%s", "Stack overflow\n");
        exit(1);
    }
    *(stack+(++top))=x;
}

void citireSt(int *stack, int n)
{
    int i,x;
    printf("Introduceti numerele: ");
    for(i=0;i<n;i++){
        scanf("%d",&x);
        push(stack,x,n);
    }
}
int get(int *stack) //function to retrieve top element of stack
{
    return *(stack+(top--));
}

void afisareMod(int *stack, int c)
{
    int msb=1<<c;//again, not actually msb
    int el;
    while(top){
        el=get(stack);
        if(el&msb)
            printf("%d ",el);
    }
    printf("\n");
}
int main()
{
    int *stack,n,c;
    citireD(c);
    citireD(n);
    stack=(int*)malloc(n*sizeof(int));
    citireSt(stack,n);
    afisareMod(stack,c);
    free(stack);
    return 0;
}