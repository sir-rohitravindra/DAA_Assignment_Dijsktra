#include <stdlib.h>
#include <stdio.h>
#include "./PES1UG19CS393_H.h"

int main()
{
    FILE* fp=fopen("./adjacencylist.txt","r");
    if(fp!=NULL)
    {
        int v;
        fscanf(fp,"%d\n",&v);
        //printf("%d\n",v);
        graph* mygraph=createGraph(v+1);
        
        int cur;
        
        for(int i=0;i<v && !feof(fp);i++)
        {
            
            fscanf(fp,"%d",&cur);
            //printf("%d",cur);
            int dst,wt;
            while(!feof(fp) && fgetc(fp)!='\n')
            {                            
                fseek(fp,-1,SEEK_CUR);
                fscanf(fp,"%d %d",&dst,&wt);
                //printf("\t%d,%d",dst,wt);
                createLink(mygraph,cur,dst,wt);
            }
            //printf("\n");
            
        }
        //printf("\n#########################\n");
        //printGraph(mygraph);

        dijkstra(mygraph,v);


        fclose(fp);
    }

    else
    {
        printf("Please include the adjacency list input file in this working directory\n");
    }
    
    
}
