#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

void dfs(int** graph, int row_size, int at, bool* isVisited, int* visitedNodes, int* len){

    isVisited[at] = true;

    for(int i = 0; i < row_size; i++){
        if(graph[at][i] == 1 && isVisited[i] == false){
            dfs(graph, row_size, i, isVisited, visitedNodes, len);
        }
    }

    visitedNodes[(*len)++] = at;
}


int* topological_sort(int** graph, int row_size){
    bool* isVisited = (bool*) calloc(row_size, sizeof *isVisited);
    int* ordering = (int*) calloc(row_size, sizeof *ordering);
    int* visitedNodes = (int*) malloc(sizeof(row_size * sizeof *visitedNodes));
    int i = row_size - 1;

    for(int at = 0; at < row_size; at++){
        if(isVisited[at] == false){
            int len = 0;
            dfs(graph, row_size, at, isVisited, visitedNodes, &len);
            for(int nodeId = 0; nodeId < len; nodeId++){
                ordering[i--] =  visitedNodes[nodeId];
            }
        }
    }
    free(visitedNodes);
    free(isVisited);
    return ordering;
}

int** graph_init(int* len){
    #define ROW 13
    *len = ROW;
    int graph[ROW][ROW]= {
        {0,0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0,0},
        {1,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,0,0,0,0,0},
        {1,0,0,1,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,1,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    int** G = (int**) malloc(ROW * sizeof(int*));
    for(int i = 0; i < ROW; i++){   
        G[i] = (int*) malloc(ROW * sizeof(int));
        memcpy(G[i], graph[i], ROW * sizeof(int));
    }

    return G;
}
/**
 * 0  : not connect 
 * 1  : -> connect to other
 */
// directed graph



void is_valid_topo(int** graph, int* topo, int len) {
    int pos[len];
    bool isValid = true;
    for (int i = 0; i < len; i++) {
        pos[topo[i]] = i;  // map node → index in topo order
    }
    for (int u = 0; u < len; u++) {
        for (int v = 0; v < len; v++) {
            if (graph[u][v] == 1 && pos[u] > pos[v]) {
                // u should come before v in topo sort
                isValid = false;
            }
        }
    }
    printf("%s", (isValid) ? "\n[Test]: topo is valid\n" : "\n[Test]: topo is invalid\n");
}


int main(void){
    int len;
    int** graph = graph_init(&len); //len is init also
    int* result = topological_sort((int**)graph, len);

    is_valid_topo(graph, result, len);

    for(int i = 0; i < len; i++){
        printf("%c  ", 'A' + result[i]); 
    }

    for(int i = 0; i < len; i++){
        free(graph[i]);
    }
    free(graph);
    free(result);
    return 0;
}