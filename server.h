#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Node struct
typedef struct Node
{
    // Having vertex ID
    int id;
    // Weight of connection
    int weight;
    // Next pointer
    struct Node* next;
    // Distance of path
    int dist;
    // ID of previous vertex
    int prev;
} Node;

// Node header
typedef struct Head
{
    Node* head;
    int prev; // To hold id of previous vertex in graph
    int dist; // Distance of shortest path
} Head;

// Adjlist
typedef struct Graph
{
    int n;
    Head* graph;
} Graph;

// Heap
typedef struct Heap
{
    int n;
    Node* heap;
} Heap;

// Path (created for easy output generation)
typedef struct Path
{
    Node* head;
    int dist; 
} Path;

// Array of paths (for all except source vertex)
typedef struct Paths
{
    int n; // Number of vertices
    Path* paths;
} Paths;

// Function to initialise a graph
Graph* initialise(int size);

// Function to do file handling
Graph* file(void);

// Inserting graphs to adj list
Head insert(Head head, int id, int weight);

// Displaying graph
void display(Graph* g);

// Creation of heap
Heap* create_heap(int size);

// Used to remove element from priority queue
Heap* delete(Heap* h, int* del);

// Used to update priority queue
Heap* update(Heap* h);

// Used to update distances in priority queue
Heap* dist_update(Heap* h, int id, int dist);

// Initialising path struct
Paths* initialise_paths(int size);

Graph* Dijkstra(Graph* g, Heap* h);

// To get the paths
void get_paths(Graph* g);

// Insert to paths
Node* insert_path(Node* head, int id);

// Used to reset paths array
int* reset(int* arr, int size);