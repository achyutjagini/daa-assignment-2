#include "server.h"

Graph* initialise(int size)
{
    // Create a graph
    Graph* g = (Graph *)malloc(sizeof(Graph));

    g->n = size;
    g->graph = malloc(size * sizeof(Node));

    // Initialise each node to NULL
    for (int i = 0; i < size; i ++)
    {
        g->graph[i].head = NULL;
        g->graph[i].prev = 0;
        g->graph[i].dist = INT_MAX;
    }

    return g;
}

Head insert(Head head, int id, int weight)
{
    // Create node with id and weight
    Node* new = malloc(sizeof(Node));
    new->id = id;
    new->weight = weight;
    new->next = NULL;
    new->dist = INT_MAX;
    new->prev = 0; // Setting to 0 as nodes start from 1, 0 indicates no previous node in the path

    // If that particular list is empty
    if (head.head == NULL)
    {
        head.head = new;
    }
    else
    {
        Node* temp = head.head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        // Now at last node, next node will be new node
        temp->next = new;
    }
    return head;
}

Graph* file(void)
{
    // Read data from file
    FILE* fp;

    fp = fopen("test.txt", "r");

    // If file pointer is null, return
    if (fp == NULL)
    {
        return NULL;
    }

    size_t size = 100;

    // Create string to display
    char* test = malloc(100 * sizeof(char));
    int x;

    x = getline(&test, &size, fp);

    // Here test is first line, which is number of vertices in graph
    Graph* g = initialise(atoi(test) + 1); // Adding 1 so can refer with vertex ids instead of converting to indices

    // Iterate through all connections from a given vertix
    while (x = getline(&test, &size, fp) != -1)
    {
        // First token received is the one all have connections to (reversing edges)
        char* token = strtok(test, " ");
        int node = atoi(token);

        int weight;
        int vertex;

        // Now for every given vertex, need to iterate to get pairs of connecting vertex and corresponding weight
        while (token != NULL)
        {
            // Get vertex token
            token = strtok(NULL, " ");

            // Just check for if token is NULL
            if (token == NULL)
            {
                break;
            }

            vertex = atoi(token);

            // Get weight token
            token = strtok(NULL, " ");

            // Just check for if token is NULL
            if (token == NULL)
            {
                break;
            }

            weight = atoi(token);

            // Inserting to graph
            g->graph[vertex] = insert(g->graph[vertex], node, weight);
        }
    }

    return g;
}

void display(Graph* g)
{
    // Temp to traverse through each list
    Node* temp;

    printf("Length: %d\n", g->n);

    for (int i = 1; i < g->n; i ++)
    {
        printf("\nHead: %d ", i);

        temp = g->graph[i].head;

        if (temp == NULL)
        {
            printf("No outgoing connections");
        }
        else
        {
            while (temp != NULL)
            {
                printf("Vertex: %d Weight: %d ", temp->id, temp->weight);
                temp = temp->next;
            }
        }
    }
    printf("\n");
}

Heap* create_heap(int size)
{
    // Create heap
    Heap* h = (Heap* )malloc(sizeof(Heap));

    // Assign size
    h->n = size - 1;

    // Allocate memory for array
    h->heap = malloc((h->n + 1) * sizeof(Node));

    // As all distances are infinity, order does not matter in heap

    for (int i = 0; i < h->n; i ++)
    {
        // Assigning the id
        h->heap[i].id = i + 1;
        // Assigning the distance
        h->heap[i].dist = INT_MAX;
        // Assigning the previous vertex in the path
        h->heap[i].prev = 0;
    }

    return h;
}

Heap* delete(Heap* h, int* del)
{
    *del = h->heap[0].id;

    // Copy next element to previous element
    for (int i = 0; i < (h->n - 1); i ++)
    {
        h->heap[i] = h->heap[i + 1];
    }

    // Update length
    h->n --;

    return h;
}

Heap* update(Heap* h)
{
    // Sort based on dist
    // Implemented using bubble sort for ease of coding

    Node temp;// Temp node for swapping

    for (int i = 0; i < h->n - 1; i ++)
    {
        int swaps = 0;
        
        for (int j = 0; j < (h->n - i - 1); j ++)
        {
            if (h->heap[j].dist > h->heap[j + 1].dist)
            {
                temp = h->heap[j];
                h->heap[j] = h->heap[j + 1];
                h->heap[j + 1] = temp;

                swaps ++;
            }
        }

        if (swaps == 0)
        {
            break;
        }
    }
    return h;
}

Paths* initialise_paths(int size)
{
    Paths* p = malloc(sizeof(Paths));

    // Number of vertices
    p->n = size;

    p->paths = malloc(p->n * sizeof(Path));

    for (int i = 0; i < p->n; i ++)
    {
        p->paths[i].dist = 0;
        p->paths[i].head = malloc(sizeof(Node));
        p->paths[i].head->id = i + 1;
    }

    return p;
}

Heap* dist_update(Heap* h, int id, int dist)
{
    // Search for node in heap
    for (int i = 0; i < h->n; i ++)
    {
        if (h->heap[i].id == id)
        {
            h->heap[i].dist = dist;
            break;
        }
    }

    h = update(h);

    return h;
}

Graph* Dijkstra(Graph* g, Heap* h)
{
    // Source vertex is vertex with greatest id
    int source = g->n - 1;

    // Update dist of source vertex to 0, initially it is the last element in the heap
    h->heap[h->n - 1].dist = 0;
    g->graph[h->heap[h->n - 1].id].dist = 0;

    // Update heap to reflect this
    h = update(h);

    // List of vertices whose shortest path has been found
    int v[g->n];
    for (int i = 1; i < g->n; i ++)
    {
        v[i] = 0;
    }

    // Update that source vertex's shortest path has been found
    v[g->n - 1] = 1;

    // Node which has been removed from heap
    int del;

    Node* n;

    // Iterate through all vertices
    for (int i = 1; i < (g->n - 1); i ++)
    {
        // Get element at start of priority queue
        h = delete(h, &del);

        // Mark vertix as visited
        v[del] = 1;

        // Temp variable to get outgoing connections
        Node* temp = g->graph[del].head;

        while (temp != NULL)
        {
            if ((g->graph[del].dist + temp->weight) < (g->graph[temp->id].dist))
            {
                // Update dist
                g->graph[temp->id].dist = g->graph[del].dist + temp->weight;
                // Update dist in heap
                h = dist_update(h, temp->id, g->graph[temp->id].dist);
                // Update previous vertex
                g->graph[temp->id].prev = del;
            }
            temp = temp->next;
        }
    }

    return g;
}

Node* insert_path(Node* head, int id)
{
    // Create node to be added
    Node* new = malloc(sizeof(Node));
    new->id = id;
    new->next = NULL;

    // If first node
    if (head == NULL)
    {
        head = new;
    }
    else
    {
        // Temp node for traversal
        Node* temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
    }
    return head;
}

int* reset(int* arr, int size)
{
    for (int i = 1; i < size; i ++)
    {
        arr[i] = 0;
    }
    return arr;
}


void get_paths(Graph* g)
{
    Paths* p = malloc(sizeof(Paths));

    p->paths = malloc((g->n - 1) * sizeof(Node));

    // Source
    int source = g->n - 1;

    int* arr = malloc(source * sizeof(int));

    // Initialise paths with first node as the node itself (only those that have paths)
    for (int i = 1; i < source; i ++)
    {
        // If a path exists, add to paths array
        if (g->graph[i].prev != 0)
        {
            Node* new = malloc(sizeof(Node));
            new->id = i;
            new->next = NULL;
            p->paths[i].head = new; 
        }
        else
        {
            p->paths[i].head = NULL;
        }
    }

    // Iterate over and add path
    for (int i = 1; i < source; i ++)
    {
        // Keeps track of prev element
        int prev = g->graph[i].prev;

        arr = reset(arr, source);
        int j = 0;

        // If it has a path
        if (prev != 0)
        {
            while (prev != source)
            {
                arr[j] = prev;
                j ++;
                // Go back to previous node
                prev = g->graph[prev].prev;
            }
            arr[j] = prev;
        }

        int k = 0;

        while (k <= j && (arr[j] == source))
        {
            p->paths[i].head = insert_path(p->paths[i].head, arr[k]);
            k ++;
        }
    }
    
    // Print paths

    // Temp variable for traversal
    Node* temp;

    for (int i = 1; i < source; i ++)
    {
        temp = p->paths[i].head;
        if (temp == NULL)
        {
            printf("%d NO PATH\n", i);
        }
        else
        {
            printf("%d ", i);

            while (temp != NULL)
            {
                printf("%d ", temp->id);
                temp = temp->next;
            }
            printf("%d\n", g->graph[i].dist);
        }
    }
}