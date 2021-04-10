#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int rng(int lim)
{
   // printf("%d ",rand());
    return rand()%lim;

}


int placeBombUtil(char v[10][10],int col,int nr)
{
    int i=0;
    if(nr==0)
        return 1;
    for(i=rng(10);i<10;i++)
        if(v[i][col]!='*'){
            v[i][col]='*';//places bomb on board

            if (placeBombUtil(v,rng(10),nr-1))//recur to place rest of bombs
                return 1;
            //if we cant place bomb, backtrack
            v[i][col]='0';
        }
    return 0;//if we can't place bombs return 0

}

int placeHelper(char v[10][10],int nr)
{
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<10;j++){
            if(v[i][j]!='*'){
                v[i][j]='*';
                nr--;
            }
            if(nr==0)
                return 1;
        }
    return 0;
}

void initTable(char table[10][10])
{
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<10;j++)
            table[i][j]='0';
}

void printTable(char table[10][10])
{
    int i,j,k=0;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            printf("%c ",table[i][j]);
            if(table[i][j]=='*')
                k++;
        }
    printf("\n");
    }
    printf("Nr of bombs=%d\n",k);
}

void writeCells(char table[10][10],int i, int j)
{
    int k,l;
    if(table[i][j]=='*'){
    for(k=i-1;k<=i+1;k++)
        if(k<=9)
        for(l=j-1;l<=j+1;l++)
            if(l<=9)
            if(l!=j || k!=i) 
                if(table[k][l]!='*')
                    table[k][l]++;
    }else
        return;
}

int assignCellValues(char table[10][10],int col)
{
    int i;
    if(col<0)
        return 1;
    for(i=0;i<10;i++)
        writeCells(table,i,col);
        if(assignCellValues(table,col-1))
            return 1;
}

int main()
{
    char table[10][10];
    int n,alt=-1;
    clock_t timp;
    
    srand((unsigned)time(NULL));//initializes pseudo random number using time as seed
    initTable(table);
    printf("n=");
    scanf("%d",&n);
    
    if(n>90){
        alt=n-90;
        n=90;
        
        if(n>100){
            printf("n must be <100!\n");
            exit(1);
        }
    }

    timp=clock();
    placeBombUtil(table,9,n); printf("\n");
    
    if(alt!=-1)     
        placeHelper(table,alt);

    timp=clock()-timp;
    printTable(table);
    assignCellValues(table,9);
    printf("\n");
    printTable(table);

    printf("\nruntime=%g\n",(double)timp/CLOCKS_PER_SEC);
    return 0;
}