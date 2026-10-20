#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct EdgeNode {
    int to;
    struct EdgeNode *next;
} EdgeNode;
typedef struct {
    EdgeNode **head;
    int V;
} Graph;

Graph* create_graph(int V) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->V = V;
    g->head = (EdgeNode **)calloc(V + 1, sizeof(EdgeNode *));
    return g;
}
void add_edge(Graph *g, int u, int v) {
    EdgeNode *node1 = (EdgeNode *)malloc(sizeof(EdgeNode));
    node1->to = v;
    node1->next = g->head[u];
    g->head[u] = node1;

    EdgeNode *node2 = (EdgeNode *)malloc(sizeof(EdgeNode));
    node2->to = u;
    node2->next = g->head[v];
    g->head[v] = node2;
}
typedef struct {
    int *parent;
    int *rank;
    long long *comp_weight;
    bool *active;
    int V;
} DSU;
DSU* create_dsu(int V, long long *w) {
    DSU *dsu = (DSU *)malloc(sizeof(DSU));
    dsu->V = V;
    dsu->parent = (int *)malloc((V + 1) * sizeof(int));
    dsu->rank = (int *)malloc((V + 1) * sizeof(int));
    dsu->comp_weight = (long long *)malloc((V + 1) * sizeof(long long));
    dsu->active = (bool *)calloc(V + 1, sizeof(bool));
    for (int i = 1; i <= V; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
        dsu->comp_weight[i] = w[i];
    }
    return dsu;
}
int find_root(DSU *dsu, int x) {
    if (dsu->parent[x] == x)
        return x;
    return dsu->parent[x] = find_root(dsu, dsu->parent[x]);
}
bool union_components(DSU *dsu, int u, int v, long long *new_weight) {
    int root_u = find_root(dsu, u);
    int root_v = find_root(dsu, v);
    if (root_u == root_v)
        return false;

    if (dsu->rank[root_u] < dsu->rank[root_v]) {
        int temp = root_u; root_u = root_v; root_v = temp;
    }
    dsu->parent[root_v] = root_u;
    dsu->comp_weight[root_u] += dsu->comp_weight[root_v];
    if (dsu->rank[root_u] == dsu->rank[root_v])
        dsu->rank[root_u]++;
    *new_weight = dsu->comp_weight[root_u];
    return true;
}
int main() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return 0;

    long long *w = (long long *)malloc((V + 1) * sizeof(long long));
    for (int i = 1; i <= V; i++) {
        scanf("%lld", &w[i]);
    }
    Graph *g = create_graph(V);
    for (int i = 0; i < E; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            add_edge(g, u, v);
        }
    }
    int *p = (int *)malloc((V + 1) * sizeof(int));
    for (int i = 1; i <= V; i++) {
        scanf("%d", &p[i]);
    }
    DSU *dsu = create_dsu(V, w);
    long long *ans = (long long *)malloc((V + 1) * sizeof(long long));
    long long current_max = 0;
    for (int i = V; i >= 1; i--) {
        ans[i] = current_max;

        int u = p[i];
        dsu->active[u] = true;
        if (dsu->comp_weight[u] > current_max) {
            current_max = dsu->comp_weight[u];
        }

        for (EdgeNode *curr = g->head[u]; curr != NULL; curr = curr->next) {
            int v = curr->to;
            if (dsu->active[v]) {
                long long merged_wt;
                if (union_components(dsu, u, v, &merged_wt)) {
                    if (merged_wt > current_max) {
                        current_max = merged_wt;
                    }
                }
            }
        }
    }
    printf("Reverse Time-Step DSU: Sequential Vertex Deletion\n");
    printf("Total Vertices: %d, Total Edges: %d\n\n", V, E);
    for (int i = 1; i <= V; i++) {
        printf("After deleting vertex %d: Max Component Sum = %lld\n", p[i], ans[i]);
    }
    for (int i = 1; i <= V; i++) {
        EdgeNode *curr = g->head[i];
        while (curr) {
            EdgeNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g->head);
    free(g);
    free(w);
    free(p);
    free(ans);
    free(dsu->parent);
    free(dsu->rank);
    free(dsu->comp_weight);
    free(dsu->active);
    free(dsu);
    return 0;
}
