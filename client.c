#include "server.h"

int main(void)
{
    // Create Graph
    Graph* g = file();

    //display(g);

    // Create Heap
    Heap* h = create_heap(g->n);

    g = Dijkstra(g, h);

    get_paths(g);
}