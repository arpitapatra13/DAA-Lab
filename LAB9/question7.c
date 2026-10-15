#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void maxHeapify(int heap[], int size, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left] > heap[largest]) largest = left;
    if (right < size && heap[right] > heap[largest]) largest = right;

    if (largest != idx) {
        swap(&heap[idx], &heap[largest]);
        maxHeapify(heap, size, largest);
    }
}

int extractMax(int heap[], int *size) {
    int root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    maxHeapify(heap, *size, 0);
    return root;
}

void insertMaxHeap(int heap[], int *size, int val) {
    heap[*size] = val;
    int i = *size;
    (*size)++;

    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int heap[n + 1];
    int size = 0;
    int min_val = 2147483647;

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        if (val % 2 != 0) {
            val *= 2;
        }
        if (val < min_val) {
            min_val = val;
        }
        insertMaxHeap(heap, &size, val);
    }

    int min_deviation = heap[0] - min_val;

    while (heap[0] % 2 == 0) {
        int max_val = extractMax(heap, &size);
        int current_dev = max_val - min_val;
        if (current_dev < min_deviation) {
            min_deviation = current_dev;
        }

        int new_val = max_val / 2;
        if (new_val < min_val) {
            min_val = new_val;
        }
        insertMaxHeap(heap, &size, new_val);
    }

    int final_dev = heap[0] - min_val;
    if (final_dev < min_deviation) {
        min_deviation = final_dev;
    }

    printf("Minimum Deviation = %d\n", min_deviation);
    return 0;
}
