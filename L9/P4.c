//Might not be the most efficient solution, my goal was to use divide-et-impera as much as possible
//reads array from "array.txt" file, array can be written under any form as long as lines are separated by '\n'

#include<stdio.h>
#include<stdlib.h>
//#include<unistd.h>


//adapted interpol that returns position of largest element that is smaller than search token, if token isn't found
//*(pos+1) is a tag that is == 1 if solution is found, == 0 otherwise
int* Interpol(int *arr, int l, int r, int tok,int lastPos)
{
    int *pos=(int*)malloc(2*sizeof(int));
	if (r >= l && tok>=arr[l] &&tok<=arr[r]) {
		
		*pos = (tok - arr[l])*(r - l) / (arr[r] - arr[l]) + l;
        //printf("pos=%d\n",*pos);
		if (tok == arr[*pos]){
            
            *(pos+1)=1;
            
			return pos;
        }
		if (tok < arr[*pos])
			return Interpol(arr, l, *pos - 1, tok,*pos);
		if (tok > arr[*pos])
			return Interpol(arr, *pos + 1, r, tok,*pos);
	}
    if(tok>arr[r])
        *pos=r;
    else
    *pos=lastPos;
    *(pos+1)=0;
	return pos;
}

//interpol search that searches for element in 'col' column of array
int ColInterpol(int **arr,int l, int r, int col,int tok)
{
    int pos;
	if (r >= l && tok>=arr[l][col] &&tok<=arr[r][col]) {
		
		pos = (tok - arr[l][col])*(r - l) / (arr[r][col] - arr[l][col]) + l;

		if (tok == arr[pos][col])
			return pos;
		if (tok < arr[pos][col])
			return ColInterpol(arr, l, pos - 1, col, tok);
		if (tok > arr[pos][col])
			return ColInterpol(arr, pos + 1, r, col, tok);
	}
	return -1;
}

//helper function to run InterpolCollumn searches
//could easily implement multithreading
void Start(int **arr, int n, int m, int tok)
{
    int startP,endP,*ans=(int*)malloc(2*sizeof(int)),i;
    ans=Interpol(*arr,0,m-1,tok,0);
    if(*(ans+1)==1){
        printf("true, on position 1-%d\n",*ans+1);
        exit(0);
    }
    endP=*ans+1;
    ans=Interpol(*(arr+n-1),0,m-1,tok,0);
    if(*(ans+1)==1){
        printf("true, on position %d-%d\n",n,*ans+1);
        exit(0);
    }
    startP=*ans+1;
    *ans=-1;
    while(startP<=endP && *ans==-1){            //not divide-et-impera whoops
        *ans=ColInterpol(arr,0,n,startP,tok);
        startP++;
    }
    if(*ans!=-1)
        printf("true, on position %d-%d\n",*ans+1,startP);
    else
        printf("false\n");
}


//reads array from file, ignores any other characters apart from numbers
void readArr(int **arr,FILE* f, int *n,int *m)
{
    int i=0,j=0,**temp;
    char c;

    c=getc(f);
    while(c!=EOF){

        if(c=='\n'){
            i++;
            if(*m!=j && i>1){
                printf("ERROR: lines must be the same length(line:%d)\n",i);
                exit(1);
            }
            *m=j;
            j=0;
            
        }
        else if(c>='0' && c<='9'){
                fseek(f,-1,SEEK_CUR);
            fscanf(f," %d",&arr[i][j]);
            j++;
        }
        //printf("%c",c);
        c=getc(f);

    }
    *n=i;
    for(i=0;i<*n;i++){
        *temp=(int*)realloc(*(arr+i),*m*sizeof(int));
        if(temp==NULL){
            perror("realloc");
            exit(-1);
        }
        *(arr+i)=*temp;
    }
    temp=(int**)realloc(arr,*n*sizeof(int*));
    if(temp==NULL){
            perror("realloc");
            exit(-1);
        }
    arr=temp;

}

void printArr(int **arr, int n, int m)
{
    int i,j;
    printf("n=%d m=%d\n",n,m);
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
            printf("%d ",arr[i][j]);
        printf("\n");
    }

}

int main()
{
    char *cwd="/home/moro/Documents/TP-Lab/L9",c;
    int tok;
    //chdir(cwd);//REMOOOVEE THIS
    FILE *f=fopen("array.txt","r");
    int **arr,i,n,m,*ans=(int*)malloc(2*sizeof(int));
    if(f==NULL)
        perror("fopen");
    arr=(int**)malloc(100*sizeof(int*));
    for(i=0;i<100;i++)
        *(arr+i)=(int*)malloc(100*sizeof(int*));
    readArr(arr,f,&n,&m);
    printArr(arr,n,m);
    printf("Enter element:\n");
    scanf("%d",&tok);
    Start(arr,n-1,m-1,tok);
    return 0;
}