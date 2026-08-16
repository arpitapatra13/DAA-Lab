#include <stdio.h>

// Binary Search
int binarySearch(int arr[], int n, int key, int *comparisons)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        (*comparisons)++;

        if (arr[mid] == key)
            return mid;

        (*comparisons)++;

        if (key < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

// Ternary Search
int ternarySearch(int arr[], int n, int key, int *comparisons)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        (*comparisons)++;

        if (arr[mid1] == key)
            return mid1;

        (*comparisons)++;

        if (arr[mid2] == key)
            return mid2;

        (*comparisons)++;

        if (key < arr[mid1])
        {
            high = mid1 - 1;
        }
        else if (key > arr[mid2])
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
    int n, key;
    int binaryComparisons = 0;
    int ternaryComparisons = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements in sorted order:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search: ");
    scanf("%d", &key);

    // Binary Search
    int binaryResult = binarySearch(
        arr, n, key, &binaryComparisons
    );

    // Ternary Search
    int ternaryResult = ternarySearch(
        arr, n, key, &ternaryComparisons
    );

    printf("\n----- RESULTS -----\n");

    if (binaryResult != -1)
        printf("Binary Search: Element found at index %d\n",
               binaryResult);
    else
        printf("Binary Search: Element not found\n");

    if (ternaryResult != -1)
        printf("Ternary Search: Element found at index %d\n",
               ternaryResult);
    else
        printf("Ternary Search: Element not found\n");

    printf("\nBinary Search comparisons : %d\n",
           binaryComparisons);

    printf("Ternary Search comparisons: %d\n",
           ternaryComparisons);

    if (binaryComparisons < ternaryComparisons)
        printf("\nConclusion: Binary Search performed better.\n");
    else if (ternaryComparisons < binaryComparisons)
        printf("\nConclusion: Ternary Search performed better for this input.\n");
    else
        printf("\nConclusion: Both performed the same number of comparisons.\n");

    return 0;
}
