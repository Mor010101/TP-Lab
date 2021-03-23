//La nivel de bit?
// daca am vrea sa determinam daca numarul are scrierea in binar palindrom
// ar trebui compus numarul folosindu-ne de cifre * 10^n

#include<stdio.h>
#include<stdlib.h>


void push(int *stack,int *top, int x)
{
    if(*top>=6){
        fprintf(stderr,"%s %d","Stack overflow--top was ", *top);
        exit(1);
    }
    *(stack+(++*top))=x;
}

void readSt(int *stack,int *top,int n)
{
    int i,x;
    printf("Dati elementele stivei:\n");
    for(i=0;i<n;i++){
        scanf("%d",&x);
        push(stack,top,x);
    }
}

//something between peek and pop, also doesn't reset elements 
int get(int *stack, int *top)
{
    *top-=1;
    return *(stack+*top+1);
} 

void psh2stack(int *stack1, int*stack2, int *top1, int *top2)
{
    int aux;
    while(*top1>=0){
        if(*top2>=6){
            fprintf(stderr,"%s %d","Stack overflow--top was ", *top2);
            exit(1);
        }
        
        aux=get(stack1,top1);
        printf("%d ",aux);
        
        
        push(stack2,top2,aux);
    }
}

int stackCmp(int *stack1, int *stack2, int *top1, int *top2)
{
    while(*top1){
        if(get(stack1,top1)!=get(stack2,top2)){
            return 0;
        }
    }
    return 1;
}
int main()
{
    int *stack,*stack2, *top1=(int*)malloc(sizeof(int)), *top2=(int*)malloc(sizeof(int));
    int n; *top1=-1;*top2=-1;
    printf("n=");
    scanf("%d",&n);
    stack=(int*)malloc(n*sizeof(int));
    stack2=(int*)malloc(n*sizeof(int));

    readSt(stack,top1,n);
    
    
    psh2stack(stack,stack2,top1,top2);//pushes elements of first stack to second stack
    *top1=n-1;
    if(stackCmp(stack,stack2,top1,top2)==0) //compares stacks
        printf("Numarul nu este palindrom\n");
    else
        printf("Numarul este palindrom\n");
    

    free(stack);
    free(stack2);
    free(top1);
    free(top2);
    return 0;
    
}