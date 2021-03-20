//Nu imi place solutia asta, maine am sa incerc sa uploadez o varianta acceptabila

#include<stdio.h>
#include<stdlib.h>

int top=-1,top2=-1;
#define varname(name) #name
#define citire(x) printf("%s=",varname(x)); scanf("%d",&x)
#define default -1
void push(int*stack, int n)
{
    int val;
    //if stack isn't full
    if(top>=99){
        printf("Stack overflow");
        exit(1);
    }else{
        top++;
        *(stack+top)=n;
    }
}

int peek(int*stack)
{
    return stack[top];
}

int pop(int *stack)
{
    int n; //optional
    if(top==-1){
        printf("Stiva este goala ");
        return 1;
    }
    n=*(stack+top);
    *(stack+top)=default;
    top--;
    //stack=(int*)realloc(stack,(top+1)*sizeof(int)); cum refacem stiva, nu este cazul sa eliberam memoria
    return n;
}

int isPrime(int n)
{
    int i;
    if(n<2)
        return 0;
    for(i=2;i*i<=n;i++)
        if(n%i==0)
            return 0;

    return 1;

}
int toBin(int n)
{
    int rez=0,i,k = 0, msb = 1 << (8 * sizeof(int) - 1);
    
    for (i = 0; i < 32; i++) {
		if ((n << i)  & msb || k != 0) {
            k++; 
            rez*=10;
            if((n<<i)&msb){
                
                rez++;
                }
        }
    }
    return rez;
}

int afisBin(int n)
{
    int i;
    for(i=0;i<32;i++)
        if((n>>i)&1)
            printf("1");
        else
            printf("0");
    printf("\n");
}

void popTranslate(int *stack1, int*stack2)
{
    int i;
    if(top==-1){
        printf("Stiva este goala");
        return;
    }
    for(i=0;i<=50;i++){
        //printf("-%d-",*(stack1+top));
         if(isPrime(*(stack1+top))){
            top2++;
            *(stack2+top2)=toBin(*(stack1+top));
        }
        pop(stack1);
    }
}

void rebuildSt(int*stack)
{
    top=-1;
    int i;
    for(i=0;i<=50;i++){
        
        if(!isPrime(i)){
            //printf("%d ",i);
            push(stack,i);
        }
    }
}
int main()
{
    int *stack=(int*)malloc(100*sizeof(int)), *primeStack=(int*)malloc(100*sizeof(int));
    int i,*temp;
    for(i=0;i<=50;i++)
        push(stack,i);


    
    
    printf("\n");
    popTranslate(stack,primeStack);
    rebuildSt(stack);
    //printf("%d",top2);
    printf("Prime stack: ");
    while(top2){
        printf("%d ",*(primeStack+top2));
        top2--;
    }
    printf("\nOriginal stack: ");
    while(top){
        printf("%d ",peek(stack));
        pop(stack);
    }
    return 0;
}