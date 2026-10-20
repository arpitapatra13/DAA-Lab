#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
    int *parent;
    int *parity;
    int *rank;
    int V;
} BipartiteDSU;
BipartiteDSU* create_dsu(int V) {
    BipartiteDSU *dsu = (BipartiteDSU *)malloc(sizeof(BipartiteDSU));
    dsu->V = V;
    dsu->parent = (int *)malloc((V + 1) * sizeof(int));
    dsu->parity = (int *)malloc((V + 1) * sizeof(int));
    dsu->rank = (int *)malloc((V + 1) * sizeof(int));
    for (int i = 0; i <= V; i++) {
        dsu->parent[i] = i;
        dsu->parity[i] = 0;
        dsu->rank[i] = 0;
    }
    return dsu;
}
int find_set(BipartiteDSU *dsu, int v) {
    if (v == dsu->parent[v])
        return v;
    int p = dsu->parent[v];
    dsu->parent[v] = find_set(dsu, p);
    dsu->parity[v] ^= dsu->parity[p];
    return dsu->parent[v];
}
bool add_edge(BipartiteDSU *dsu, int u, int v) {
    int root_u = find_set(dsu, u);
    int root_v = find_set(dsu, v);
    if (root_u == root_v) {
        if (dsu->parity[u] == dsu->parity[v]) {
            return false;
        }
        return true;
    }
    if (dsu->rank[root_u] < dsu->rank[root_v]) {
        int temp = root_u; root_u = root_v; root_v = temp;
        temp = u; u = v; v = temp;
    }
    dsu->parent[root_v] = root_u;
    dsu->parity[root_v] = dsu->parity[u] ^ dsu->parity[v] ^ 1;
    if (dsu->rank[root_u] == dsu->rank[root_v]) {
        dsu->rank[root_u]++;
    }
    return true;
}
void free_dsu(BipartiteDSU *dsu) {
    free(dsu->parent);
    free(dsu->parity);
    free(dsu->rank);
    free(dsu);
}
int main() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return 0;
    BipartiteDSU *dsu = create_dsu(V);
    printf("Online Graph-Bipartiteness Testing:\n");
    printf("Total Vertices: %d, Total Arriving Edges: %d\n\n", V, E);
    for (int i = 1; i <= E; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        bool success = add_edge(dsu, u, v);
        if (success) {
            printf("Edge %d: (%d, %d) -> ADDED (Graph remains bipartite)\n", i, u, v);
        } else {
            printf("Edge %d: (%d, %d) -> REJECTED (Violates bipartiteness: odd cycle detected)\n", i, u, v);
        }
    }
    free_dsu(dsu);
    return 0;
}
