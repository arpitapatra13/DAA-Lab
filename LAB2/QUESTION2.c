#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long comparisons2way = 0;
long comparisons3way = 0;

void merge2(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparisons2way++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void mergeSort2(int arr[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort2(arr, l, m);
    mergeSort2(arr, m + 1, r);
    merge2(arr, l, m, r);
}

void merge3(int arr[], int l, int m1, int m2, int r) {
    int n1 = m1 - l + 1, n2 = m2 - m1, n3 = r - m2;
    int *A = malloc(n1 * sizeof(int));
    int *B = malloc(n2 * sizeof(int));
    int *C = malloc(n3 * sizeof(int));
    for (int i = 0; i < n1; i++) A[i] = arr[l + i];
    for (int i = 0; i < n2; i++) B[i] = arr[m1 + 1 + i];
    for (int i = 0; i < n3; i++) C[i] = arr[m2 + 1 + i];

    int i = 0, j = 0, k = 0, idx = l;
    while (i < n1 && j < n2 && k < n3) {
        comparisons3way += 2;
        if (A[i] <= B[j] && A[i] <= C[k]) arr[idx++] = A[i++];
        else if (B[j] <= A[i] && B[j] <= C[k]) arr[idx++] = B[j++];
        else arr[idx++] = C[k++];
    }
    while (i < n1 && j < n2) {
        comparisons3way++;
        if (A[i] <= B[j]) arr[idx++] = A[i++]; else arr[idx++] = B[j++];
    }
    while (j < n2 && k < n3) {
        comparisons3way++;
        if (B[j] <= C[k]) arr[idx++] = B[j++]; else arr[idx++] = C[k++];
    }
    while (i < n1 && k < n3) {
        comparisons3way++;
        if (A[i] <= C[k]) arr[idx++] = A[i++]; else arr[idx++] = C[k++];
    }
    while (i < n1) arr[idx++] = A[i++];
    while (j < n2) arr[idx++] = B[j++];
    while (k < n3) arr[idx++] = C[k++];
    free(A); free(B); free(C);
}

void mergeSort3(int arr[], int l, int r) {
    if (l >= r) return;
    int len = r - l + 1;
    if (len < 3) {
        int m = l + (r - l) / 2;
        mergeSort3(arr, l, m);
        mergeSort3(arr, m + 1, r);
        merge2(arr, l, m, r);
        return;
    }
    int third = len / 3;
    int m1 = l + third - 1;
    int m2 = l + 2 * third - 1;
    mergeSort3(arr, l, m1);
    mergeSort3(arr, m1 + 1, m2);
    mergeSort3(arr, m2 + 1, r);
    merge3(arr, l, m1, m2, r);
}

void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;
}

int main() {
    srand(time(NULL));
    int sizes[] = {1000, 10000, 100000, 500000, 1000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("%-10s %-15s %-15s %-15s %-15s\n", "n", "2-way comp", "2-way time(s)", "3-way comp", "3-way time(s)");
    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *arr1 = malloc(n * sizeof(int));
        int *arr2 = malloc(n * sizeof(int));
        fillRandom(arr1, n);
        for (int i = 0; i < n; i++) arr2[i] = arr1[i];

        comparisons2way = 0;
        clock_t t1 = clock();
        mergeSort2(arr1, 0, n - 1);
        clock_t t2 = clock();
        double time2 = (double)(t2 - t1) / CLOCKS_PER_SEC;

        comparisons3way = 0;
        clock_t t3 = clock();
        mergeSort3(arr2, 0, n - 1);
        clock_t t4 = clock();
        double time3 = (double)(t4 - t3) / CLOCKS_PER_SEC;

        printf("%-10d %-15ld %-15.6f %-15ld %-15.6f\n", n, comparisons2way, time2, comparisons3way, time3);

        free(arr1); free(arr2);
    }
    return 0;
}
