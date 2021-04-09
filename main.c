#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE* fp=fopen("./adjacencylist.txt","r");
    
    int v;
    fscanf(fp,"%d\n",&v);
    printf("%d\n",v);
    
    int cur,dst,weight;
    int flag=1;
    for(int i=0;i<v && flag;i++)
    {
        if(!feof(fp)){
            fscanf(fp,"%d",&cur);
            printf("%d\t",cur);
            int dst,wt;
            while(fgetc(fp)!='\n' && !feof(fp))
            {   
                                
                fseek(fp,-1,SEEK_CUR);
                fscanf(fp,"%d %d",&dst,&wt);
                printf("\t%d,%d",dst,wt);
            }
            printf("\n");
        }
        else{break;}
        
    }
    
}

/*
*/