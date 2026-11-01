#include <stdio.h>
#include <stdlib.h>

// Adjacency List Node
typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

// Graph Structure
typedef struct Graph {
    int V;
    Edge** adj;
} Graph;

// Result Structure for each vertex
typedef struct {
    int owner; // Hub index (1..K) or -1 if unassigned
    int dist;  // Distance to assigned hub or -1
} Result;

// Create Graph
Graph* createGraph(int V) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->adj = (Edge**)calloc(V, sizeof(Edge*));
    return g;
}

// Add Undirected Edge
void addEdge(Graph* g, int u, int v) {
    Edge* e1 = (Edge*)malloc(sizeof(Edge));
    e1->to = v;
    e1->next = g->adj[u];
    g->adj[u] = e1;

    Edge* e2 = (Edge*)malloc(sizeof(Edge));
    e2->to = u;
    e2->next = g->adj[v];
    g->adj[v] = e2;
}

// Multi-Source BFS Hub Assignment Algorithm
Result* assignHubs(Graph* g, const int* hubs, int K, int R) {
    int V = g->V;
    Result* res = (Result*)malloc(V * sizeof(Result));

    // Initialize all vertices as unassigned
    for (int i = 0; i < V; i++) {
        res[i].owner = -1;
        res[i].dist = -1;
    }

    // Queue for BFS
    int* queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;

    // Push hubs in ascending index order (1 to K) for tie-breaking
    for (int i = 0; i < K; i++) {
        int h = hubs[i];
        if (res[h].owner == -1) {
            res[h].owner = i + 1; // 1-based indexing for output
            res[h].dist = 0;
            queue[rear++] = h;
        }
    }

    // Multi-Source BFS
    while (front < rear) {
        int u = queue[front++];
        int d = res[u].dist;

        // Do not expand beyond radius R
        if (d >= R) continue;

        for (Edge* e = g->adj[u]; e != NULL; e = e->next) {
            int v = e->to;
            // First time discovering vertex v guarantees minimal distance and tie-breaking
            if (res[v].owner == -1) {
                res[v].owner = res[u].owner;
                res[v].dist = d + 1;
                queue[rear++] = v;
            }
        }
    }

    free(queue);
    return res;
}

void freeGraph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        Edge* cur = g->adj[i];
        while (cur) {
            Edge* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

int main() {
    int V = 7;
    Graph* g = createGraph(V);

    // Graph Construction
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 3);
    addEdge(g, 0, 4);
    addEdge(g, 4, 5);
    addEdge(g, 5, 3);
    addEdge(g, 1, 6);

    // Hubs: h1 = vertex 0, h2 = vertex 3
    int hubs[] = {0, 3};
    int K = 2;
    int R = 2;

    Result* res = assignHubs(g, hubs, K, R);

    // Print Results
    printf("Vertex\towner[v]\tdist(v, owner)\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < V; i++) {
        if (res[i].owner == -1) {
            printf("%d\t-1\t\tUnreachable (> %d)\n", i, R);
        } else {
            printf("%d\t%d\t\t%d\n", i, res[i].owner, res[i].dist);
        }
    }

    free(res);
    freeGraph(g);
    return 0;
}
