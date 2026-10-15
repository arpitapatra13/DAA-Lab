#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dist;
    int fuel;
} Station;

int compareStations(const void *a, const void *b) {
    Station *sa = (Station *)a;
    Station *sb = (Station *)b;
    return sa->dist - sb->dist;
}

int main() {
    int target, startFuel, n;
    if (scanf("%d %d %d", &target, &startFuel, &n) != 3) return 0;

    Station st[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &st[i].dist, &st[i].fuel);
    }

    qsort(st, n, sizeof(Station), compareStations);

    int max_heap[n + 1];
    int heap_size = 0;

    int cur_fuel = startFuel;
    int stops = 0;
    int idx = 0;

    while (cur_fuel < target) {
        while (idx < n && st[idx].dist <= cur_fuel) {
            max_heap[heap_size++] = st[idx].fuel;
            // Max heap push adjustment
            int c = heap_size - 1;
            while (c > 0) {
                int p = (c - 1) / 2;
                if (max_heap[c] > max_heap[p]) {
                    int tmp = max_heap[c];
                    max_heap[c] = max_heap[p];
                    max_heap[p] = tmp;
                    c = p;
                } else break;
            }
            idx++;
        }

        if (heap_size == 0) {
            printf("Cannot reach target! Stops = -1\n");
            return 0;
        }

        // Pop max from max heap
        int max_val = max_heap[0];
        max_heap[0] = max_heap[--heap_size];
        int p = 0;
        while (2 * p + 1 < heap_size) {
            int left = 2 * p + 1;
            int right = 2 * p + 2;
            int largest = p;
            if (left < heap_size && max_heap[left] > max_heap[largest]) largest = left;
            if (right < heap_size && max_heap[right] > max_heap[largest]) largest = right;
            if (largest != p) {
                int tmp = max_heap[p];
                max_heap[p] = max_heap[largest];
                max_heap[largest] = tmp;
                p = largest;
            } else break;
        }

        cur_fuel += max_val;
        stops++;
    }

    printf("Minimum Refueling Stops Required = %d\n", stops);
    return 0;
}
