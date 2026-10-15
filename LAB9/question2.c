#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    char ch;
    int freq;
    int len;
    char code[32];
} SymbolCode;

Node* createNode(char ch, int freq, Node *left, Node *right) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

void getLengths(Node *root, int depth, SymbolCode syms[], int *count) {
    if (!root) return;
    if (!root->left && !root->right) {
        syms[*count].ch = root->ch;
        syms[*count].freq = root->freq;
        syms[*count].len = depth;
        (*count)++;
        return;
    }
    getLengths(root->left, depth + 1, syms, count);
    getLengths(root->right, depth + 1, syms, count);
}

int compareCanonical(const void *a, const void *b) {
    SymbolCode *sa = (SymbolCode *)a;
    SymbolCode *sb = (SymbolCode *)b;
    if (sa->len != sb->len) return sa->len - sb->len;
    return sa->ch - sb->ch;
}

void intToBinaryString(unsigned int val, int len, char *str) {
    str[len] = '\0';
    for (int i = len - 1; i >= 0; i--) {
        str[i] = (val & 1) ? '1' : '0';
        val >>= 1;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Node *heap[100];
    int heapSize = 0;

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;
        scanf(" %c %d", &ch, &freq);
        heap[heapSize++] = createNode(ch, freq, NULL, NULL);
    }

    int total_freq = 0;
    for (int i = 0; i < heapSize; i++) total_freq += heap[i]->freq;

    while (heapSize > 1) {
        int min1 = 0, min2 = 1;
        if (heap[min1]->freq > heap[min2]->freq) { min1 = 1; min2 = 0; }
        for (int i = 2; i < heapSize; i++) {
            if (heap[i]->freq < heap[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (heap[i]->freq < heap[min2]->freq) {
                min2 = i;
            }
        }
        Node *n1 = heap[min1];
        Node *n2 = heap[min2];
        Node *parent = createNode('$', n1->freq + n2->freq, n1, n2);

        int pos = 0;
        for (int i = 0; i < heapSize; i++) {
            if (i != min1 && i != min2) heap[pos++] = heap[i];
        }
        heap[pos++] = parent;
        heapSize = pos;
    }

    SymbolCode syms[100];
    int count = 0;
    getLengths(heap[0], 0, syms, &count);

    qsort(syms, count, sizeof(SymbolCode), compareCanonical);

    unsigned int currentCode = 0;
    double weightedLengthSum = 0;

    printf("Canonical Huffman Codebook:\n");
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            currentCode = (currentCode + 1) << (syms[i].len - syms[i - 1].len);
        }
        intToBinaryString(currentCode, syms[i].len, syms[i].code);
        printf("Symbol '%c' (Freq: %d): Length = %d, Code = %s\n",
               syms[i].ch, syms[i].freq, syms[i].len, syms[i].code);
        weightedLengthSum += syms[i].freq * syms[i].len;
    }

    printf("Minimum Expected Length = %.4f bits/symbol\n", weightedLengthSum / total_freq);

    return 0;
}
