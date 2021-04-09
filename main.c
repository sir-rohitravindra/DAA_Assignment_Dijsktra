#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    int wt;
    struct node* next;

}node;

typedef struct list
{    
    struct node* head;
    
}list;

typedef struct graph
{
    int v;
    struct list* array;
    
}graph;

graph* createGraph(int V)
{
    graph* new = (graph*)malloc(sizeof(graph));
    new->v = V;
 
    new->array = (list*)malloc(V * sizeof(list));
 
    for (int i = 0; i < V; ++i)
        new->array[i].head = NULL;
 
    return new;
}


node* createNode(int adj,int weight)
{
    node* new=(node*)malloc(sizeof(node));
    new->data=adj;
    new->wt=weight;
    new->next=NULL;
    return new;
}
 

void createLink(graph* graph, int src,int dest,int weight)
{    
    node* new=createNode(dest,weight);
    new->next = graph->array[src].head;
    graph->array[src].head = new;
        
}

int main()
{
    FILE* fp=fopen("./adjacencylist.txt","r");
    if(fp!=NULL)
    {
        int v;
        fscanf(fp,"%d\n",&v);
        printf("%d\n",v);
        graph* mygraph=createGraph(v);
        
        int cur,dst,weight;
        
        for(int i=0;i<v && !feof(fp);i++)
        {
            
            fscanf(fp,"%d",&cur);
            printf("%d\t",cur);
            int dst,wt;
            while(fgetc(fp)!='\n' && !feof(fp))
            {                            
                fseek(fp,-1,SEEK_CUR);
                fscanf(fp,"%d %d",&dst,&wt);
                printf("\t%d,%d",dst,wt);
                createLink(mygraph,cur,dst,wt);
            }
            printf("\n");
            
            
        }

    }
    
    
}
