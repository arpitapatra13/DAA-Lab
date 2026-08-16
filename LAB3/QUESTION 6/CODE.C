#include <stdio.h>

void selectionSort(int A[], int n)
{
    int i, j, minIndex, temp;
    int comparisons = 0;
    int swaps = 0;

    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;

        for (j = i + 1; j < n; j++)
        {
            comparisons++;

            if (A[j] < A[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            temp = A[i];
            A[i] = A[minIndex];
            A[minIndex] = temp;
            swaps++;
        }
    }

    printf("\nNumber of comparisons = %d", comparisons);
    printf("\nNumber of swaps       = %d\n", swaps);
}

void printArray(int A[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main()
{
    int A[] = {64, 25, 12, 22, 11};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Original array: ");
    printArray(A, n);

    selectionSort(A, n);

    printf("Sorted array:   ");
    printArray(A, n);

    printf("\nTime Complexity:");
    printf("\nBest Case  = Theta(n^2)");
    printf("\nWorst Case = Theta(n^2)\n");

    return 0;
}
