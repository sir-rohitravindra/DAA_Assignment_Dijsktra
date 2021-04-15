#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "./PES1UG19CS393_H.h"

//utility function to setup and return a graph struct ptr
graph* createGraph(int V)
{
    graph* new = (graph*)malloc(sizeof(graph));
    new->v = V;
 
    new->array = (list*)malloc(V * sizeof(list));
 
    for (int i = 0; i < V; ++i)
    {
        new->array[i].head = NULL;
    }    
    return new;
}

//utility function to malloc and return a adj list node
node* createNode(int adj,int weight)
{
    node* new=(node*)malloc(sizeof(node));
    new->data=adj;
    new->wt=weight;
    new->next=NULL;
    return new;
}
 
//utility fn to add an edge 
//the edge is added in the reverse direction as per this 
//implementation of dijkstra
void createLink(graph* graph, int src,int dest,int weight)
{    
    node* new=createNode(src,weight);
    new->next = graph->array[dest].head;
    graph->array[dest].head = new;
        
}

//utility fn to print the graph 
//for debugging
void printGraph(graph* g)
{
    for(int i=0;i<g->v;i++)
    {
        printf("Node %d:",i);
        node* cur=g->array[i].head;

        while(cur!=NULL)
        {
            printf("(%d,%d)->",cur->data,cur->wt);
            cur=cur->next;
        }
        printf("\n");
    }
}


// A utility function to create and return a min heap node 
heapNode* newheapNode(int v,int wt)
{
    heapNode* new =(heapNode*)malloc(sizeof(heapNode));
    new->v = v;
    new->wt = wt;
    return new;
}
 
// A utility function to create and return a new minHeap
MinHeap* createMinHeap(int capacity)
{
    MinHeap* minHeap =(struct minHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =(struct heapNode**)malloc(capacity *sizeof(struct heapNode*));
    return minHeap;
}

//function to rectify the min heap after each deletion
void heapify(struct minHeap* minHeap,int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size && minHeap->array[left]->wt < minHeap->array[smallest]->wt)
    { 
        smallest = left;
    }
 
    if (right < minHeap->size && minHeap->array[right]->wt < minHeap->array[smallest]->wt)
    {
        smallest = right;
    }
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        heapNode *smallestNode = minHeap->array[smallest];
        heapNode *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapHeapNodes(&minHeap->array[smallest],&minHeap->array[idx]);
 
        heapify(minHeap, smallest);
    }
}

 
//Function to swap to heap nodes
void swapHeapNodes(heapNode** n1,heapNode** n2)
{
    heapNode* temp = *n1;
    *n1 = *n2;
    *n2 = temp;
} 


//utility function to check if heap empty to terminate the dijkstra loop.
int isEmpty(struct minHeap* minHeap)
{
    return minHeap->size == 0;
}

//utility function to return the root element(here the minmum element in the min heap) 
struct heapNode* returnRoot(struct minHeap* minHeap)
{
    if (isEmpty(minHeap))
    {
        return NULL;

    }       
 
    // Store the root node
    struct heapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct heapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    minHeap->size=minHeap->size - 1;
    heapify(minHeap, 0);
 
    return root;
}

//Function to decrease the distance values of heap nodes.
void decreaseKey(struct minHeap* minHeap,int v, int wt)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its wt value
    minHeap->array[i]->wt = wt;
 
    while (i && minHeap->array[i]->wt < minHeap->array[(i - 1) / 2]->wt)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapHeapNodes(&minHeap->array[i],&minHeap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}

//check if node is in the min heap.
int isInMinHeap(struct minHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
    {
        return 1;
    }
    return 0;
}
 
//utility function to print the path
void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j] == - 1)
        return;
    printf("%d ", j);
    printPath(parent, parent[j]);
}

// A utility function used for outputting
void printSolution(int wt[], int n,int parent[],int src)
{   
    for (int i = 1; i < n-1; i++)
    {
        
        if(wt[i]!=INT_MAX)
        {
            printf("%d ",i);        
            printPath(parent, i);
            printf("%d %d\n",src,wt[i]);
        }
        else
        {
            printf("%d NO PATH\n",i);
        }
    }
}

/*The driver function which performs the dijkstras algorithm on the graph */
void dijkstra(graph* graph, int src)
{     
    // Get the number of vertices in graph
    int V = graph->v;
    int wt[V];  //stores distances of the nodes from source.  

    int parent[V];  //stores the parent ele of each node.

    struct minHeap* minHeap = createMinHeap(V);

    //initilizations.
    for (int v = 0; v < V; ++v)
    {
        wt[v] = INT_MAX;
        minHeap->array[v] = newheapNode(v,wt[v]);
        minHeap->pos[v] = v;
    }
    parent[src] = -1;
 
    // Make wt value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] =newheapNode(src, wt[src]);
    minHeap->pos[src]   = src;
    wt[src] = 0;
    decreaseKey(minHeap, src, wt[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;

    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct heapNode* minHeapNode = returnRoot(minHeap);
       
        // Store the extracted vertex number
        int u = minHeapNode->v;
 
        node* cur = graph->array[u].head;
        while (cur != NULL)
        {
            int v = cur->data;
 
            if (isInMinHeap(minHeap, v) &&
                      wt[u] != INT_MAX &&
              cur->wt + wt[u] < wt[v])
            {
                wt[v] = wt[u] + cur->wt;
 
                // update distance value in min heap
                decreaseKey(minHeap, v, wt[v]);
                parent[v] = u;
            }
            cur = cur->next;
        }
    }
 
    // print the calculated shortest distances
    printSolution(wt, V,parent,src);
}