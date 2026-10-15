#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int id;
    int weight;
    int is_leaf;
    int leaf_idx;
    struct Node *left;
    struct Node *right;
} Node;

Node* createLeaf(int leaf_idx, int weight) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->id = leaf_idx;
    node->weight = weight;
    node->is_leaf = 1;
    node->leaf_idx = leaf_idx;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* createInternal(Node *l, Node *r) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->id = -1;
    node->weight = l->weight + r->weight;
    node->is_leaf = 0;
    node->leaf_idx = -1;
    node->left = l;
    node->right = r;
    return node;
}

void getDepths(Node *root, int current_depth, int depths[]) {
    if (!root) return;
    if (root->is_leaf) {
        depths[root->leaf_idx] = current_depth;
        return;
    }
    getDepths(root->left, current_depth + 1, depths);
    getDepths(root->right, current_depth + 1, depths);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int weights[n];
    Node *list[200];
    int size = n;

    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
        list[i] = createLeaf(i, weights[i]);
    }

    printf("Hu-Tucker Merge Sequence:\n");
    int step = 1;

    while (size > 1) {
        int best_i = -1, best_j = -1;
        int min_sum = INT_MAX;

        for (int i = 0; i < size - 1; i++) {
            // Find compatible pairs (adjacent or separated only by internal nodes)
            for (int j = i + 1; j < size; j++) {
                int sum = list[i]->weight + list[j]->weight;
                if (sum < min_sum) {
                    min_sum = sum;
                    best_i = i;
                    best_j = j;
                }
                if (list[j]->is_leaf) break; // Stopped by next leaf
            }
        }

        Node *merged = createInternal(list[best_i], list[best_j]);
        printf("Step %d: Merge (Weight %d) and (Weight %d) -> Combined Weight %d\n",
               step++, list[best_i]->weight, list[best_j]->weight, merged->weight);

        // Update active node list
        list[best_i] = merged;
        for (int k = best_j; k < size - 1; k++) {
            list[k] = list[k + 1];
        }
        size--;
    }

    int depths[100] = {0};
    getDepths(list[0], 0, depths);

    int totalCost = 0;
    printf("\nLeaf Depths and Weighted Cost Contribution:\n");
    for (int i = 0; i < n; i++) {
        int cost = weights[i] * depths[i];
        totalCost += cost;
        printf("Leaf %d (Weight %d): Depth = %d, Contribution = %d\n",
               i + 1, weights[i], depths[i], cost);
    }

    printf("Optimal Alphabetic BST Total Cost = %d\n", totalCost);
    return 0;
}
