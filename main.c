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

//////
typedef struct MinHeapNode
{
    int  v;
    int wt;
}heapNode;
 
// Structure to represent a min heap
typedef struct MinHeap
{
     
    // Number of heap nodes present currently
    int size;    
   
    // Capacity of min heap
    int capacity; 
   
    // This is needed for decreaseKey()
    int *pos;   
    heapNode **array;
}MinHeap;
 
// A utility function to create a
// new Min Heap Node
heapNode* newheapNode(int v,int wt)
{
    heapNode* new =(heapNode*)malloc(sizeof(heapNode));
    new->v = v;
    new->wt = wt;
    return new;
}
 
// A utility function to create a Min Heap
MinHeap* createMinHeap(int capacity)
{
    MinHeap* minHeap =(struct MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =(struct MinHeapNode**)malloc(capacity *sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(heapNode** a,heapNode** b)
{
    heapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap,
                                  int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->wt <
         minHeap->array[smallest]->wt )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->wt <
         minHeap->array[smallest]->wt )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        heapNode *smallestNode =
             minHeap->array[smallest];
        heapNode *idxNode =
                 minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
                         &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if
// the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract
// minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap*
                                   minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root =
                   minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode =
         minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasy wt value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap* minHeap,
                         int v, int wt)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its wt value
    minHeap->array[i]->wt = wt;
 
    // Travel up while the complete
    // tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->wt <
           minHeap->array[(i - 1) / 2]->wt)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =
                                      (i-1)/2;
        minHeap->pos[minHeap->array[
                             (i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], 
                 &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
int isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return 1;
   return 0;
}
 
// A utility function used to print the solution
void printArr(int wt[], int n)
{
    printf("Vertex   wtance from Source\n");
    for (int i = 1; i < n-1; ++i)
        printf("%d \t\t %d\n", i, wt[i]);
}
 
// The main function that calulates
// wtances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(graph* graph, int src)
{
     
    // Get the number of vertices in graph
    int V = graph->v;
   
    // wt values used to pick
    // minimum weight edge in cut
    int wt[V];    
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all
    // vertices. wt value of all vertices
    for (int v = 0; v < V; ++v)
    {
        wt[v] = INT_MAX;
        minHeap->array[v] = newheapNode(v,wt[v]);
        minHeap->pos[v] = v;
    }
 
    // Make wt value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] =newheapNode(src, wt[src]);
    minHeap->pos[src]   = src;
    wt[src] = 0;
    decreaseKey(minHeap, src, wt[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the followin loop,
    // min heap contains all nodes
    // whose shortest wtance
    // is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with
        // minimum wtance value
        struct MinHeapNode* minHeapNode =
                     extractMin(minHeap);
       
        // Store the extracted vertex number
        int u = minHeapNode->v;
 
        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their wtance values
        node* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->data;
 
            // If shortest wtance to v is
            // not finalized yet, and wtance to v
            // through u is less than its
            // previously calculated wtance
            if (isInMinHeap(minHeap, v) &&
                      wt[u] != INT_MAX &&
              pCrawl->wt + wt[u] < wt[v])
            {
                wt[v] = wt[u] + pCrawl->wt;
 
                // update wtance
                // value in min heap also
                decreaseKey(minHeap, v, wt[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    // print the calculated shortest wtances
    printArr(wt, V);
}

int main()
{
    FILE* fp=fopen("./adjacencylist.txt","r");
    if(fp!=NULL)
    {
        int v;
        fscanf(fp,"%d\n",&v);
        //printf("%d\n",v);
        graph* mygraph=createGraph(v+1);
        
        int cur,dst,weight;
        
        for(int i=0;i<v && !feof(fp);i++)
        {
            
            fscanf(fp,"%d",&cur);
            //printf("%d",cur);
            int dst,wt;
            while(fgetc(fp)!='\n' && !feof(fp))
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
    
    
}
