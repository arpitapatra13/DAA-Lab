#include <stdio.h>

void swap(long long *a, long long *b) {
    long long t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(long long heap[], int size, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;

    if (smallest != idx) {
        swap(&heap[idx], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

void insertMinHeap(long long heap[], int *size, long long val) {
    heap[*size] = val;
    int i = *size;
    (*size)++;

    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

long long extractMin(long long heap[], int *size) {
    long long root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    minHeapify(heap, *size, 0);
    return root;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long long heap[n + 1];
    int size = 0;

    for (int i = 0; i < n; i++) {
        long long stick;
        scanf("%lld", &stick);
        insertMinHeap(heap, &size, stick);
    }

    long long totalCost = 0;

    while (size > 1) {
        long long first = extractMin(heap, &size);
        long long second = extractMin(heap, &size);

        long long cost = first + second;
        totalCost += cost;

        insertMinHeap(heap, &size, cost);
    }

    printf("Minimum Total Cost to Connect Sticks = %lld\n", totalCost);
    return 0;
}
