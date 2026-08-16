#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int n, int x, int *comparisons)
{
    int low = 0;
    int high = n - 1;

    *comparisons = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        (*comparisons)++;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}
int ternarySearch(int arr[], int n, int x, int *comparisons)
{
    int low = 0;
    int high = n - 1;

    *comparisons = 0;

    while (low <= high)
    {
        int third = (high - low) / 3;

        int mid1 = low + third;
        int mid2 = high - third;

        (*comparisons)++;

        if (arr[mid1] == x)
            return mid1;

        (*comparisons)++;

        if (arr[mid2] == x)
            return mid2;

        if (x < arr[mid1])
        {
            high = mid1 - 1;
        }
        else if (x > arr[mid2])
        {
            low = mid2 + 1;
        }
        else
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int main()
{
    int n, x;
    int binaryResult, ternaryResult;
    int binaryComparisons, ternaryComparisons;

    printf("Enter the size of sorted list: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d elements in sorted order:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\nEnter element to search: ");
    scanf("%d", &x);
        binaryResult = binarySearch(
        arr, n, x, &binaryComparisons
    );
    ternaryResult = ternarySearch(
        arr, n, x, &ternaryComparisons
    );
    printf("\n========== RESULTS ==========\n");

    if (binaryResult != -1)
        printf("Binary Search: Element found at index %d\n",
               binaryResult);
    else
        printf("Binary Search: Element not found\n");

    printf("Binary Search comparisons: %d\n",
           binaryComparisons);

    printf("\n");

    if (ternaryResult != -1)
        printf("Ternary Search: Element found at index %d\n",
               ternaryResult);
    else
        printf("Ternary Search: Element not found\n");

    printf("Ternary Search comparisons: %d\n",
           ternaryComparisons);

    printf("\n========== CONCLUSION ==========\n");

    if (binaryComparisons < ternaryComparisons)
        printf("Binary Search used fewer comparisons.\n");
    else if (ternaryComparisons < binaryComparisons)
        printf("Ternary Search used fewer comparisons.\n");
    else
        printf("Both used the same number of comparisons.\n");

    printf("\nTime Complexity:\n");
    printf("Binary Search  : O(log2(n))\n");
    printf("Ternary Search : O(log3(n))\n");

    printf("\nBinary search is generally better because each\n");
    printf("iteration requires fewer comparisons than ternary search.\n");

    free(arr);

    return 0;
}
