

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


/* Initial ideea was to use the input to create binary tree, found a slightly better alternative
   left the code here in case i forget how to create binary trees
  */

/*
typedef struct nod{
    int data;
    struct nod *left;
    struct nod *right;
}node;

 //adds new node to tree, returns new node address
node *addNode(int data)
{
    node* p=(node*)malloc(sizeof(node));
    p->data=data;
    //sets children to NULL
    p->left=NULL;
    p->right=NULL;
    return p;
}
d
 */

/* void printTree(node *root)
{
    
    printTree(root->left);
    printf("%d",root->data);
    printTree(root->right);
} */

/* 
node *makeTree(int *v, node *root,int i)
{
    //base case for recursion
    if(i<*(v-1)){
        node *temp=addNode(*(v+i));
        root=temp;
        root->left=makeTree(v,root->left,2*i+1);
        root->right=makeTree(v,root->right,2*i+2);
    }
    return root;
} */

int global_max=0;

void readVect(int *v, int *indx)
{
    FILE *f;
    int i=1,ind=0,*temp,x; char c='0';
    f=fopen("tree.txt","r");            
    if(f==NULL){
        perror("fopen()");
        exit(1);
    }
    fscanf(f,"%d",&x);
    
    while(c!=EOF){
        c=getc(f);
        *(v+i)=x;
        *(indx+i)=ind;
          //  printf("%d ",*(v+i));
            i++;
        if(c=='\n')
            ind++;  
        fscanf(f,"%d",&x);
    }
    if(ftell(f)==0){
        printf("File is empty! Please insert tree in 'tree.txt'\n");
        exit(1);
    }
   temp=(int*)realloc(v,i*sizeof(int));
   if(temp==NULL)
        perror("realloc()");
    else
        v=temp;
    
   temp=(int*)realloc(indx,i*sizeof(int));
   if(temp==NULL)
        perror("realloc()");
    else
        indx=temp;

   *v=i-1;
   *indx=*(indx+i-1);//stashing max level in first int

   for(i=0;i<=*indx+1;i++)//sets "leaves" of tree to -1; kind of a lazy workaround but it works
        *(indx+*v+i+1)=-1;

    fclose(f);
}

//naive backtrack implementetion... recursion is my achilles heel 
int maxPath(int *v, int *ind, int poz,int sum)
{
    
    if(*(ind+poz)==-1){//this is why the leaves were set to -1
        return 0;           
    } 
    
    sum+=*(v+poz);
    if(sum>global_max)
        global_max=sum;
    maxPath(v,ind , poz+*(ind+poz)+1,sum);//left side 
    maxPath(v,ind , poz+*(ind+poz)+2,sum);//right side   
}

//puts cwd in *str and prints cwd if successful, otherwise prints error 
void getdir(char *str, unsigned int str_size)
{
    
     if(getcwd(str,str_size)==NULL){
        perror("getcwd()");
        exit(1);
    }else
        printf("Current working dir: %s\n",str);
}
//reads directory path and sets it as new working dir
int changeDir(char cwd[])
{
    
    /* printf("New woking dir path= ");
    scanf("%s",cwd); */
    if(chdir(cwd)!=0){
        perror("chdir()");
        return -1;
        }
    getdir(cwd,256);
    return 0;
}


int main()
{
   
    char cwd[256]="/home/moro/Documents/TP-Lab/L6";
    int* vect=(int*)malloc(201*sizeof(int)), * layer=(int*)malloc(201*sizeof(int));
    int max=0;
    *vect=201;//stores length in first int    
    
    changeDir(cwd);/*COMMENT THIS FUNCTION OUT,    ubuntu doesn't set current working directory to the dir in which the .c file is located,
                                                   using this makes working with files easier*/
 
    readVect(vect,layer);
    vect+=1; layer+=1;

    maxPath(vect,layer,0,0);
    printf("max=%d",global_max);
    
    free(vect-1); free(layer-1);
    return 0;
}