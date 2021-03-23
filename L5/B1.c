#include<stdio.h>
#include<stdlib.h>


//daca introducem forma inversata intr-o stiva, outputul va fi in
//in ordinea normala, deoarece afisarea incepe la capatul stivei(top)
int top=-1;

void push(int *stack, int x)
{
    if(top>=32){
        fprintf(stderr,"%s","Stack overflow\n");
        exit(1);
    }
    *(stack+(++top))=x;
}

void dec2bin(int x, int *norm, int *inv)
{
    int i,count=0;
    unsigned int msb=1<<(8*sizeof(int)-1);
   
    for(i=0;i<32;i++){ 
        if((x>>i)&1==1)
            *(inv+i)=1;
        else
            *(inv+i)=0;
            
        if((x<<i)&msb)
            *(norm+i)=1;
        else
            *(norm+i)=0;
    }
    
}

//only "calculates" normal form and pushes it to stack
void dec2stack(int x, int *stack)
{
    int i,count=0;
    unsigned int msb=1<<(8*sizeof(int)-1);
   
    for(i=0;i<32;i++){    
        if(i%4==0 && i)
            printf(" ");
            
        if((x<<i)&msb){
            printf("1");
            push(stack,1);
        }
        else{
            printf("0");
            push(stack,0);
        }
    }
    
}

void printV(int *v)
{
    int i;
    for(i=0;i<32;i++){
        if(i%4==0 && i)
            printf(" ");
        printf("%d",*(v+i));
        }
    printf("\n");
}

void scanV(int *v,int n)
{
    int i;
    for(i=0;i<n;i++){
        printf("Elem %d= ",i+1);
        scanf("%d",(v+i));
    }
}

int get(int *stack);
void printStack(int *stack);

int main()
{
    int *norm,*inv, *vect;
    int *stack,opt;
    unsigned int n,x,i,c1=0,c2=0;
    
    printf("n=");
    scanf("%d",&n);
    vect=(int*)malloc(n*sizeof(int));
    
    scanV(vect,n);
    do{
        printf("---------------------\n");
        printf("Choose option:\n1.Actually calculate normal and inverted form and print\n2.Only calculate inverted form, save to stack and print\n0.EXIT\n");
        scanf("%d",&opt);
        switch(opt){
        case 0:

        free(vect);
        if(c1){    
            free(norm);
            free(inv);
        }
        if(c2)
            free(stack);
        
        case 1:
        c1=1;            //would be cleaner to write function for printing
        norm=(int*)malloc(32*sizeof(int));
        inv=(int*)malloc(32*sizeof(int));
        for(i=0;i<n;i++){
            dec2bin(*(vect+i),norm,inv);
            printf("---------------------\n");
            printf("Elementul v[%d]=%d\n",i,*(vect+i));
            printf("Norm= ");
            printV(norm);
            printf("Inv=  ");
            printV(inv);
            
        }
        case 2:
        c2=1;
        stack=(int*)malloc(32*sizeof(int));
        for(i=0;i<n;i++){
             printf("---------------------\n");
            printf("Elementul v[%d]=%d\n",i,*(vect+i));
            printf("Norm= ");
            dec2stack(*(vect+i),stack);
            printf("\nInv=  ");
            printStack(stack);
        }

        }
    }while(opt);
    return 0;
}


int get(int *stack) //function to retrieve top element of stack
{
    return *(stack+(top--));
}


void printStack(int *stack)
{
    int i;
    for(i=0;i<32;i++)
        if(i%4==0 && i){
            printf(" ");
            printf("%d",get(stack));
        }
        else
            printf("%d",get(stack));
    printf("\n");
}