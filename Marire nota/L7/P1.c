#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct fold{
    int dim;
    char *name;
    struct fold **subs;
}fd;

//returns random number in [1,mx]
int randm(int mx)
{
    return rand()%mx+1;
}

void PRINT(fd *root, int n);
void prit(fd *root);


//creates vect with n unrepetitive random numbers
void randmVect(int n, int *v)
{
    int temp,i,j,iv;
  //  v=(int*)malloc((n+1)*sizeof(int));

    for(i=0;i<n;i++)
        *(v+i)=i;
    iv=randm(n)-1;
    
    //same adapted Fisher-Yates algorithm as in SolveUtil()
    for(i=n-1;i>=0;i--){
        
        j=randm(n)-1;
        
        temp=*(v+i);
        *(v+i)=*(v+j);
        *(v+j)=temp;
        //wanted to add more 0's (placed pseudo-randomly) without adding too much complexity
        //this is still stupidly complex for the task
        if((j%2==0 && iv%2==0 || j%2!=0 && iv%2!=0)&&iv){ 
            *(v+j)=0;
            iv--;   
        }
    }
}

unsigned addFiles(fd* child,fd* files, int start, int end)
{
    char *term={".txt.bin.log.dat.bat.doc"}; //6 possible terminations (0,4,8,12,..,20,...24) call (randm(6)-1)*4
    char *letters="abcdefghijklmnopqrstuvwxyz";
    int *v=(int*)malloc(10*sizeof(int)),i,j=0,k;
    unsigned total_size=0;
    if(end==start)
        return 0;
    
    
    for(i=start;i<end;i++){
        //names files
        (files+i)->name=(char*)malloc(7*sizeof(char));
        (files+i)->dim=randm(2000);//size in bytes
        total_size+=(files+i)->dim;
        for(k=0;k<3;k++)
            (files+i)->name[k]=*(letters+randm(25));
        (files+i)->name[3]='\0';
        strncat((files+i)->name,(term+(randm(6)-1)*4),4);//appends termination to name
        
        if(start==0)
            (files+i)->subs=NULL;
        child->subs[i]=(files+i);
        
    }
    return total_size;
    
}


int length(int n)
{
    int k=0;
    if(n==0)
        return 1;
    while(n){
        k++;
        n/=10;
    }
    return k;
}

void back(fd *file,int layers)
{
    if(layers<1){
        int n=randm(11)-1;
        if(n==0)
            return;
        file->subs=(fd**)malloc((n+1)*sizeof(fd*));
        fd*child=(fd*)malloc((n+1)*sizeof(fd));
        file->dim=addFiles(file,child,0,n);
        return;
    }
    int n=randm(5),i,j,max=randm(11)-1;
    int *v=(int*)malloc((n+1)*sizeof(int));
    char *letters="abcdefghijklmnopqrstuvwxyz";//alphabet array for random names
    fd *child=(fd*)malloc((n+max+1)*sizeof(fd));
    file->subs=(fd**)malloc((n+max+1)*sizeof(fd*));
    
    //initializes child and adds it to parent's list of children
    for(i=0;i<n;i++){
        (child+i)->dim=0;
        (child+i)->name=(char*)malloc(4*sizeof(char));
        for(j=0;j<3;j++)
            (child+i)->name[j]=*(letters+randm(25));
        (child+i)->name[3]='\0';
        (child+i)->subs=NULL;
        file->subs[i]=(child+i);//devin aceiasi adresa, la final este suficient sa apelam free(file->subs)
    }
    addFiles(file,child,n,n+max);//could also call (file+n,child+n,n+max) 

    randmVect(n,v);
    for(i=0;i<n;i++)
        if(*(v+i)!=0)
            back(child+*(v+i),layers-1); //recur to add next layer of children(randomly picked folders)
    i=0;
    while(file->subs[i]){               //backtrack to calculate folder sizes
        file->dim+=file->subs[i]->dim;
        i++;
    }
}


fd* SolveUtil(int *size)
{
    int i,j,n=randm(10),temp;
    int randA[n+1];
    char *letters={"abcdefghijklmnopqrstuvwxyz"};
    fd *file=(fd*)malloc(n*sizeof(fd));
    fd sub;
    //initializes 'root' folders
    for(i=0;i<n;i++){
        (file+i)->dim=0;
        (file+i)->name=(char*)malloc(4*sizeof(char));
        for(j=0;j<3;j++)
            (file+i)->name[j]=*(letters+randm(25));
        (file+i)->name[3]='\0';
        printf("%s ",(file+i)->name);
        
    }
    

    //efficient way of creating non-reptitive random numbers
    //or at least the best i could do within C, but hey limitations inspire creativity
    for(i=0;i<n;i++)
        randA[i]=i;
    //adapted Fisher-Yates shuffle
    for(i=n-1;i>=0;i--){
        j=randm(n)-1;
        temp=randA[i];
        randA[i]=randA[j];
        randA[j]=temp;
    }
    
    printf("n=%d\n",n);

    for(i=0;i<n;i++){
        back(file+randA[i],randm(5));
    }
    printf("\n============ROOT_FOLDER============\nfolder->subfolders                | FILES--SIZE\n                                  |\nsize->sizes                       |\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
    //ar putea fi apelat in main
    PRINT(file,n);    
    
    *size=n;
    return file;
}

void freeMem(fd*root)
{
    if(root==NULL)
        return;
    int i=0;
    while(root->subs[i]){
        free(root->subs[i]->name);
        i++;
    }
    free(root->subs);
    freeMem(root+1);
    free(root);
}


int main()
{
    fd* root;
    int size,i,j=0;

    srand((unsigned)time(NULL));//time in seconds since 1970(epoch) as seed
    
    root=SolveUtil(&size);
   // printf("\n  %p  ",root);
    
  
    
    //free memory
    free(root->subs);//this is most likely wrong but i can't check for mem leaks(visual studio code lacks a memory tracking tool)
    free(root);        
    
    return 0;    
        
}

void PRINT(fd* root, int n)
{
    int i,size=0;
    for(i=0;i<n;i++){
        printf("================%s================\n",(root+i)->name);
        size+=(root+i)->dim;
        prit(root+i);
    }
    //if length of size>6 print in mb, if length of size>3 print in kb (megabytes and kilobytes to be specific)
    if(length(size)>6)
        printf("\nTOTAL SIZE=%g (Mb)\n",(float)size/1000000);
    if(length(size)>3)
        printf("\nTOTAL SIZE=%g (Kb)\n",(float)size/1000);
    else
    printf("\nTOTAL SIZE=%d (bytes)\n",size);
}

void prit(fd *root)
{
    
    int i=0,n,j=0,count=0;
    if(root->subs==NULL)
        return;
    if(strlen(root->subs[0]->name) > 5){//daca folderul nu are alte foldere in el, ci doar fisiere
        printf("%s%*s",root->name,33,"| ");
        count=35;
    }
    else
        printf("%s-> ",root->name);
    while(root->subs[i]){
        j=0;
        if(i>0)
        if(strlen(root->subs[i]->name)>5 &&strlen(root->subs[i-1]->name)<5){
            printf("%*s ",28-count+1,"|");
            count=35;

        }
        


        if(strlen(root->subs[i]->name)>5){
            printf("%s--%d(bytes) ",root->subs[i]->name,root->subs[i]->dim);
            count+=length(root->subs[i]->dim)+16+5;
        }
        else{
        printf("%s ",root->subs[i]->name);
        count+=4;
        }
        if(count>=99){
            printf("\n%*s",36,"| ");
            count=35;
        }
        i++;
    }
    printf("\n");
    i=0;count=0;
    printf("%d-> ",root->dim);
    count+=length(root->dim)+3;
    while(root->subs[i] && strlen(root->subs[i]->name)<5){
        printf("%d ",root->subs[i]->dim);
        count+=length(root->subs[i]->dim)+1;
        i++;
    }
    
    printf("%*s",35-count,"|");
    printf("\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|\n");
    n=i;
    for(i=0;i<n;i++)
        prit(root->subs[i]);
}
