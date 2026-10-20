#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
    long long weight;
    int root;
} HeapNode;
typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MaxHeap;
MaxHeap* create_heap(int capacity) {
    MaxHeap *h = (MaxHeap *)malloc(sizeof(MaxHeap));
    h->data = (HeapNode *)malloc(capacity * sizeof(HeapNode));
    h->size = 0;
    h->capacity = capacity;
    return h;
}
void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}
void heap_push(MaxHeap *h, long long weight, int root) {
    if (h->size >= h->capacity) {
        h->capacity *= 2;
        h->data = (HeapNode *)realloc(h->data, h->capacity * sizeof(HeapNode));
    }
    int i = h->size++;
    h->data[i].weight = weight;
    h->data[i].root = root;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[i].weight > h->data[parent].weight) {
            swap_nodes(&h->data[i], &h->data[parent]);
            i = parent;
        } else {
            break;
        }
    }
}
void heapify_down(MaxHeap *h, int i) {
    while (2 * i + 1 < h->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < h->size && h->data[left].weight > h->data[largest].weight)
            largest = left;
        if (right < h->size && h->data[right].weight > h->data[largest].weight)
            largest = right;

        if (largest != i) {
            swap_nodes(&h->data[i], &h->data[largest]);
            i = largest;
        } else {
            break;
        }
    }
}
void heap_pop(MaxHeap *h) {
    if (h->size <= 0) return;
    h->data[0] = h->data[--h->size];
    heapify_down(h, 0);
}
typedef struct {
    int *parent;
    int *size;
    long long *comp_weight;
    int V;
} DSU;
DSU* create_dsu(int V, long long *w) {
    DSU *dsu = (DSU *)malloc(sizeof(DSU));
    dsu->V = V;
    dsu->parent = (int *)malloc((V + 1) * sizeof(int));
    dsu->size = (int *)malloc((V + 1) * sizeof(int));
    dsu->comp_weight = (long long *)malloc((V + 1) * sizeof(long long));
    for (int i = 1; i <= V; i++) {
        dsu->parent[i] = i;
        dsu->size[i] = 1;
        dsu->comp_weight[i] = w[i];
    }
    return dsu;
}
int find_root(DSU *dsu, int x) {
    if (dsu->parent[x] == x)
        return x;
    return dsu->parent[x] = find_root(dsu, dsu->parent[x]);
}
bool union_components(DSU *dsu, int u, int v, int *new_root) {
    int root_u = find_root(dsu, u);
    int root_v = find_root(dsu, v);
    if (root_u == root_v) {
        *new_root = root_u;
        return false;
    }
    if (dsu->size[root_u] < dsu->size[root_v]) {
        int temp = root_u; root_u = root_v; root_v = temp;
    }

    dsu->parent[root_v] = root_u;
    dsu->size[root_u] += dsu->size[root_v];
    dsu->comp_weight[root_u] += dsu->comp_weight[root_v];
    *new_root = root_u;
    return true;
}
long long get_max_valid_weight(MaxHeap *h, DSU *dsu, int K) {
    while (h->size > 0) {
        HeapNode top = h->data[0];
        int r = top.root;
        if (dsu->parent[r] == r && dsu->comp_weight[r] == top.weight) {
            if (dsu->size[r] <= K) {
                return top.weight;
            }
        }
        heap_pop(h);
    }
    return -1; 
}
int main() {
    int V, E, K;
    if (scanf("%d %d %d", &V, &E, &K) != 3) return 0;

    long long *w = (long long *)malloc((V + 1) * sizeof(long long));
    for (int i = 1; i <= V; i++) {
        scanf("%lld", &w[i]);
    }
    DSU *dsu = create_dsu(V, w);
    MaxHeap *h = create_heap(V + E + 10);
    for (int i = 1; i <= V; i++) {
        if (dsu->size[i] <= K) {
            heap_push(h, dsu->comp_weight[i], i);
        }
    }
    printf("Maximum Weight Component with Size Constraint (Threshold K = %d):\n", K);
    long long initial_max = get_max_valid_weight(h, dsu, K);
    if (initial_max != -1) {
        printf("Initial State (0 edges): Max Weight (size <= %d) = %lld\n", K, initial_max);
    } else {
        printf("Initial State (0 edges): No component with size <= %d\n", K);
    }
    for (int i = 1; i <= E; i++) {
        int u, v;
        long long edge_w;
        if (scanf("%d %d %lld", &u, &v, &edge_w) != 3) break;
        int new_root;
        bool merged = union_components(dsu, u, v, &new_root);
        if (merged) {
            if (dsu->size[new_root] <= K) {
                heap_push(h, dsu->comp_weight[new_root], new_root);
            }
        }
        long long current_max = get_max_valid_weight(h, dsu, K);
        if (current_max != -1) {
            printf("Step %2d: Add Edge (%d, %d, wt=%lld) -> Max Weight (size <= %d) = %lld\n",
                   i, u, v, edge_w, K, current_max);
        } else {
            printf("Step %2d: Add Edge (%d, %d, wt=%lld) -> No component with size <= %d\n",
                   i, u, v, edge_w, K);
        }
    }
    free(w);
    free(dsu->parent);
    free(dsu->size);
    free(dsu->comp_weight);
    free(dsu);
    free(h->data);
    free(h);
    return 0;
}
