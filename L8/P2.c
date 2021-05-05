#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int sort(const void* a,const void* b)
{
    return *(char*)a-*(char*)b;
}

void swap(char *a,char*b)
{
    char temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

//could also use backtracking to find next perm but that would be less efficient 
//function to find next permutation in O(n) time 
int nextPerm(char * string)
{
    int n=strlen(string);
    int i=n-1,j;
    //printf("%")
    while(i>0 && *(string+i)<*(string+i-1))//finds predecesor to largest decreasing suffix(pivot)
        i--;
    if(i==0)
        return 0;//reached last permutation
    j=n-1;
    while(*(string+j)<=*(string+i-1))//finds rightmost element that is larger than pivot
        j--;
    n--;
    //printf("%d--%d\n",i,j);
    swap((string+j),(string+i-1));//swaps pivot with element found before
    qsort(string+i,(size_t)n-i,(size_t)sizeof(char),sort);//sorts rest of string
    return 1;
}



int main()
{
    char *lex=(char*)malloc(10*sizeof(char));
    size_t rest=10,length;
    int i;
    length=getline(&lex,&rest,stdin);//could also use fgets
    
    length-=1;
   
    printf("Permutations:\n ");
    printf("%s ",lex);
    while(nextPerm(lex))
        printf("%s ",lex);
    
    return 0;

}