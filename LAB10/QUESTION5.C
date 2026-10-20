#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Node {
    int val;
    struct Node *next;
} Node;
typedef struct {
    int *parent;
    int *rank;
    int n;
} DSU;
DSU* create_dsu(int n) {
    DSU *dsu = (DSU *)malloc(sizeof(DSU));
    dsu->n = n;
    dsu->parent = (int *)malloc((n + 1) * sizeof(int));
    dsu->rank = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}
int find_root(DSU *dsu, int x) {
    if (dsu->parent[x] == x)
        return x;
    return dsu->parent[x] = find_root(dsu, dsu->parent[x]);
}
void union_sets(DSU *dsu, int u, int v) {
    int root_u = find_root(dsu, u);
    int root_v = find_root(dsu, v);
    if (root_u == root_v) return;

    if (dsu->rank[root_u] < dsu->rank[root_v]) {
        dsu->parent[root_u] = root_v;
    } else {
        dsu->parent[root_v] = root_u;
        if (dsu->rank[root_u] == dsu->rank[root_v])
            dsu->rank[root_u]++;
    }
}
int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x - y);
}
int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int *A = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
    }
    DSU *dsu = create_dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            union_sets(dsu, u, v);
        }
    }
    Node **comp_head = (Node **)calloc(n + 1, sizeof(Node *));
    int *comp_size = (int *)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        int r = find_root(dsu, i);
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->val = i;
        newNode->next = comp_head[r];
        comp_head[r] = newNode;
        comp_size[r]++;
    }
    for (int r = 1; r <= n; r++) {
        if (comp_size[r] > 0) {
            int sz = comp_size[r];
            int *indices = (int *)malloc(sz * sizeof(int));
            int *values = (int *)malloc(sz * sizeof(int));
            Node *curr = comp_head[r];
            int idx = 0;
            while (curr) {
                indices[idx] = curr->val;
                values[idx] = A[curr->val];
                idx++;
                Node *tmp = curr;
                curr = curr->next;
                free(tmp);
            }
            qsort(indices, sz, sizeof(int), compare_ints);
            qsort(values, sz, sizeof(int), compare_ints);
            for (int j = 0; j < sz; j++) {
                A[indices[j]] = values[j];
            }
            free(indices);
            free(values);
        }
    }
    printf("Lexicographically Smallest Permutation:\n");
    for (int i = 1; i <= n; i++) {
        printf("%d%c", A[i], (i == n ? '\n' : ' '));
    }
    free(comp_head);
    free(comp_size);
    free(A);
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
    return 0;
}
