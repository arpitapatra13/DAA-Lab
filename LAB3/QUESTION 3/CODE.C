#include <stdio.h>

struct Result {
    int min;
    int max;
};

long long comparisons = 0;

struct Result findMinMax(int a[], int low, int high) {
    struct Result result, left, right;
    int mid;

     if (low == high) {
        result.min = result.max = a[low];
        return result;
    }

     if (high == low + 1) {
        comparisons++;

        if (a[low] < a[high]) {
            result.min = a[low];
            result.max = a[high];
        } else {
            result.min = a[high];
            result.max = a[low];
        }

        return result;
    }

     mid = (low + high) / 2;

     left = findMinMax(a, low, mid);
    right = findMinMax(a, mid + 1, high);

     comparisons++;
    result.min = (left.min < right.min) ? left.min : right.min;

    comparisons++;
    result.max = (left.max > right.max) ? left.max : right.max;

    return result;
}

int main() {
    int n, i;
    int a[100];

    struct Result result;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    result = findMinMax(a, 0, n - 1);

    printf("\nMinimum element = %d\n", result.min);
    printf("Maximum element = %d\n", result.max);
    printf("Number of comparisons = %lld\n", comparisons);

    printf("Theoretical upper bound (3n/2) = %.1f\n",
           1.5 * n);

    return 0;
}
