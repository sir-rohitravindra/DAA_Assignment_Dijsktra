/*Adjcency List implementation */
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

/*implemntation of Heap data stuct credits gfg */
typedef struct heapNode
{
    int  v;
    int wt;
    int parentele;

}heapNode;
 
// Structure to represent a min heap
typedef struct minHeap
{    
    int capacity; //capacity of heap (array repn)
    int size;  // Heap nodes in the heap at that instace
    int *pos;  // This is needed for decreaseKey() 
    heapNode **array;

}MinHeap;


/*functions to handle adj list*/

graph* createGraph(int);
node* createNode(int,int);
void createLink(graph*,int,int,int);
void printGraph(graph*);

/*functions to handle min heap*/

heapNode* newheapNode(int,int);
MinHeap* createMinHeap(int);
void heapify(struct minHeap*,int);
struct heapNode* returnRoot(struct minHeap*);
void decreaseKey(struct minHeap*,int, int);
void swapHeapNodes(heapNode**,heapNode**);
int isEmpty(struct minHeap*);
int isInMinHeap(struct minHeap *, int);

/*functions to implement dijkstra*/

void dijkstra(graph*,int);
void printSolution(int[],int,int[],int);
void printPath(int[],int);
