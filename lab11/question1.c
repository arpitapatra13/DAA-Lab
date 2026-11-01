#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

typedef struct Edge {
    int to, w;
    struct Edge* next;
} Edge;

typedef struct {
    int u, parity; // parity: 0 = even k1, 1 = odd k1
} State;

// Add directed edge to adjacency list
void add_edge(Edge** adj, int u, int v, int w) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->w = w;
    e->next = adj[u];
    adj[u] = e;
}

void solve(int V, Edge** adj, int S, int C) {
    // dist[v][0] = min weight with even k1, dist[v][1] = min weight with odd k1
    int (*dist)[2] = malloc(V * sizeof(*dist));
    for (int i = 0; i < V; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    // Fixed-capacity Circular Deque for 0-1 BFS
    int cap = 2 * V + 5;
    State* dq = (State*)malloc(cap * sizeof(State));
    int front = 0, rear = 0;

    // Start at source vertex with even parity (0 weight-1 edges traversed)
    dist[S][0] = 0;
    dq[rear++] = (State){S, 0};

    while (front != rear) {
        State cur = dq[front];
        front = (front + 1) % cap;
        int u = cur.u, p = cur.parity;

        for (Edge* e = adj[u]; e != NULL; e = e->next) {
            int v = e->to, w = e->w;
            int np = p ^ w;          // Parity flips if w = 1, stays same if w = 0
            int nd = dist[u][p] + w;

            if (nd < dist[v][np]) {
                dist[v][np] = nd;
                State ns = {v, np};
                if (w == 0) {
                    front = (front - 1 + cap) % cap; // Push front for weight-0
                    dq[front] = ns;
                } else {
                    dq[rear] = ns;                   // Push back for weight-1
                    rear = (rear + 1) % cap;
                }
            }
        }
    }

    // Calculate effective min cost per vertex
    printf("Vertex\tMin Cost\n");
    for (int i = 0; i < V; i++) {
        int cost_even = dist[i][0];
        int cost_odd = (dist[i][1] == INF) ? INF : (dist[i][1] + C);
        int min_cost = (cost_even < cost_odd) ? cost_even : cost_odd;

        if (min_cost >= INF) {
            printf("%d\tUnreachable\n", i);
        } else {
            printf("%d\t%d\n", i, min_cost);
        }
    }

    free(dist);
    free(dq);
}

int main() {
    int V = 5, S = 0, C = 10;
    Edge** adj = (Edge**)calloc(V, sizeof(Edge*));

    // Sample Edges: (u, v, weight)
    add_edge(adj, 0, 1, 1);
    add_edge(adj, 1, 2, 1);
    add_edge(adj, 0, 3, 0);
    add_edge(adj, 3, 4, 1);
    add_edge(adj, 4, 2, 0);

    solve(V, adj, S, C);

    // Free graph memory
    for (int i = 0; i < V; i++) {
        Edge* cur = adj[i];
        while (cur) {
            Edge* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(adj);
    return 0;
}
