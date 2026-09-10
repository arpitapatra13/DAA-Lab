#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* merge_two(int* A, int sizeA, int* B, int sizeB) {
    int* res = malloc(sizeof(int) * (sizeA + sizeB));
    int i = 0, j = 0, k = 0;

    while (i < sizeA && j < sizeB) {
        if (A[i] <= B[j]) {
            res[k++] = A[i++];
        } else {
            res[k++] = B[j++];
        }
    }

    while (i < sizeA) res[k++] = A[i++];
    while (j < sizeB) res[k++] = B[j++];

    return res;
}

// Method 1: Sequential Merge
int* merge_sequential(int** arrays, int k, int n) {
    int* res = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        res[i] = arrays[0][i];
    }

    int curr_size = n;
    for (int i = 1; i < k; i++) {
        int* temp = merge_two(res, curr_size, arrays[i], n);
        free(res);
        res = temp;
        curr_size += n;
    }

    return res;
}

// Method 2: Pairwise Merge
int* merge_pairwise(int** arrays, int k, int n) {
    int** curr_arrays = malloc(sizeof(int*) * k);
    int* sizes = malloc(sizeof(int) * k);

    for (int i = 0; i < k; i++) {
        curr_arrays[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            curr_arrays[i][j] = arrays[i][j];
        }
        sizes[i] = n;
    }

    int count = k;
    while (count > 1) {
        int next_count = 0;

        for (int i = 0; i < count; i += 2) {
            if (i + 1 < count) {
                int* temp = merge_two(curr_arrays[i], sizes[i], curr_arrays[i+1], sizes[i+1]);
                free(curr_arrays[i]);
                free(curr_arrays[i+1]);

                curr_arrays[next_count] = temp;
                sizes[next_count] = sizes[i] + sizes[i+1];
            } else {
                curr_arrays[next_count] = curr_arrays[i];
                sizes[next_count] = sizes[i];
            }
            next_count++;
        }
        count = next_count;
    }

    int* final_res = curr_arrays[0];
    free(curr_arrays);
    free(sizes);

    return final_res;
}

void print_array(int* arr, int size) {
    if (size <= 12) {
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("%d %d %d %d ... %d %d %d %d (Total: %d)\n",
               arr[0], arr[1], arr[2], arr[3],
               arr[size - 4], arr[size - 3], arr[size - 2], arr[size - 1],
               size);
    }
}

int main() {
    int k, n, choice;

    printf("Enter number of arrays (k): ");
    scanf("%d", &k);

    printf("Enter size of each array (n): ");
    scanf("%d", &n);

    int** arrays = malloc(sizeof(int*) * k);
    for (int i = 0; i < k; i++) {
        arrays[i] = malloc(sizeof(int) * n);
    }

    printf("\n1. Manual Input\n2. Auto Generate\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        for (int i = 0; i < k; i++) {
            printf("Enter %d elements for Array %d:\n", n, i + 1);
            for (int j = 0; j < n; j++) {
                scanf("%d", &arrays[i][j]);
            }
        }
    } else {
        srand(time(NULL));
        for (int i = 0; i < k; i++) {
            int val = rand() % 10;
            for (int j = 0; j < n; j++) {
                arrays[i][j] = val;
                val += 1 + (rand() % 5);
            }
        }

        printf("\nInput Arrays:\n");
        if (k <= 6) {
            for (int i = 0; i < k; i++) {
                printf("Array %d: ", i + 1);
                print_array(arrays[i], n);
            }
        } else {
            printf("First 2 and last 2 arrays shown:\n");
            for (int i = 0; i < 2; i++) {
                printf("Array %d: ", i + 1);
                print_array(arrays[i], n);
            }
            printf("...\n");
            for (int i = k - 2; i < k; i++) {
                printf("Array %d: ", i + 1);
                print_array(arrays[i], n);
            }
        }
    }

    // Time sequential
    clock_t start = clock();
    int* seq_out = merge_sequential(arrays, k, n);
    clock_t end = clock();
    double seq_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    // Time pairwise
    start = clock();
    int* pair_out = merge_pairwise(arrays, k, n);
    end = clock();
    double pair_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("\n--- Results ---\n");
    printf("Sequential Result: ");
    print_array(seq_out, k * n);

    printf("Pairwise Result:   ");
    print_array(pair_out, k * n);

    printf("\nExecution Time:\n");
    printf("Sequential Merge : %.4f ms\n", seq_time);
    printf("Pairwise Merge   : %.4f ms\n", pair_time);

    for (int i = 0; i < k; i++) free(arrays[i]);
    free(arrays);
    free(seq_out);
    free(pair_out);

    return 0;
}
