#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_VERTICES 6

const char nodeNames[] = {'u', 'v', 'w', 'x', 'y', 'z'};

typedef struct Vertex {
    int id; // 0 to 5
    char status; // 'W', 'G', 'B'
     /** White: unvisited 
     *  Gray: explored but not finished
     *  Black: finished
     */
    int predecessor;
    int discovery_time;
    int finish_time;
} Vertex;

typedef struct Graph {
    int adj[NUM_VERTICES][NUM_VERTICES]; // adjacency matrix
    Vertex* vertices[NUM_VERTICES];
} Graph;

Graph* createGraph() {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    memset(G->adj, 0, sizeof(G->adj));
    for (int i = 0; i < NUM_VERTICES; i++) {
        G->vertices[i] = (Vertex*)malloc(sizeof(Vertex));
        G->vertices[i]->id = i;
        G->vertices[i]->status = 'W';
        G->vertices[i]->predecessor = -1;
    }
    return G;
}

void addEdge(Graph* G, int u, int v) {
    G->adj[u][v] = 1;
}

void dfs_visit(Graph* G, int u, int* time) {
    (*time)++;
    G->vertices[u]->discovery_time = *time;
    G->vertices[u]->status = 'G';

    for (int v = 0; v < NUM_VERTICES; v++) {
        if (G->adj[u][v] && G->vertices[v]->status == 'W') {
            G->vertices[v]->predecessor = u;
            dfs_visit(G, v, time);
        }
    }

    (*time)++;
    G->vertices[u]->finish_time = *time;
    G->vertices[u]->status = 'B';
}

void dfs(Graph* G) {
    //initialization is in create graph
    int time = 0;
    for (int u = 0; u < NUM_VERTICES; u++) {
        if (G->vertices[u]->status == 'W') {
            dfs_visit(G, u, &time);
        }
    }
}

void print_dfs_result(Graph* G) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        Vertex* v = G->vertices[i];
        printf("%c: discovery = %d, finish = %d, predecessor = %c\n",
               nodeNames[v->id],
               v->discovery_time,
               v->finish_time,
               (v->predecessor == -1) ? '-' : nodeNames[v->predecessor]);
    }
}

int main() {
    Graph* G = createGraph();

    addEdge(G, 0, 1); // u → v
    addEdge(G, 0, 3); // u → x
    addEdge(G, 1, 4); // v → y
    addEdge(G, 2, 4); // w → y
    addEdge(G, 2, 5); // w → z
    addEdge(G, 3, 1); // x → v
    addEdge(G, 4, 3); // y → x
    addEdge(G, 5, 5); // z → z

    dfs(G);
    print_dfs_result(G);

    return 0;
}
