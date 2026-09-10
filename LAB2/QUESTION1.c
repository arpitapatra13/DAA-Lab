#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int searchUnsorted(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) if (arr[i] == key) return i;
    return -1;
}

int searchSorted(int arr[], int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

void fillSorted(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

int main() {
    int sizes[] = {1000, 10000, 100000, 500000, 1000000, 2000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int repeats = 500;
    volatile int sink = 0; // prevent compiler from optimizing away the search calls

    printf("%-10s %-25s %-25s\n", "n", "Unsorted Search (s)", "Sorted Search (s)");
    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *arr = malloc(n * sizeof(int));
        fillSorted(arr, n);

        int key = n - 1;  // worst case

        clock_t t1 = clock();
        for (int r = 0; r < repeats; r++) sink += searchUnsorted(arr, n, key);
        clock_t t2 = clock();
        double unsortedTime = (double)(t2 - t1) / CLOCKS_PER_SEC / repeats;

        clock_t t3 = clock();
        for (int r = 0; r < repeats; r++) sink += searchSorted(arr, n, key);
        clock_t t4 = clock();
        double sortedTime = (double)(t4 - t3) / CLOCKS_PER_SEC / repeats;

        printf("%-10d %-25.8f %-25.8f\n", n, unsortedTime, sortedTime);

        free(arr);
    }

    return 0;
}
