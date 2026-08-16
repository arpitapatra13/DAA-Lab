#include <stdio.h>
#include <stdlib.h>



int findDefective(int coins[], int left, int right, int goodWeight)
{
    
    if (left == right)
    {
        if (coins[left] < goodWeight)
            return left;
        else
            return -1;
    }

    int n = right - left + 1;

     int third = n / 3;

    int aStart = left;
    int aEnd = left + third - 1;

    int bStart = aEnd + 1;
    int bEnd = bStart + third - 1;

    int cStart = bEnd + 1;
    int cEnd = right;

    if (third == 0)
    {
        
        for (int i = left; i <= right; i++)
        {
            if (coins[i] < goodWeight)
                return i;
        }
        return -1;
    }
    int weightA = 0;
    int weightB = 0;

    for (int i = aStart; i <= aEnd; i++)
        weightA += coins[i];

    for (int i = bStart; i <= bEnd; i++)
        weightB += coins[i];

    if (weightA < weightB)
    {
        return findDefective(coins, aStart, aEnd, goodWeight);
    }
     else if (weightB < weightA)
    {
        return findDefective(coins, bStart, bEnd, goodWeight);
    }

    // A and B are equal
    else
    {
        return findDefective(coins, cStart, cEnd, goodWeight);
    }
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int *coins = (int *)malloc(n * sizeof(int));

    printf("Enter the weights of %d coins:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    
    int goodWeight = coins[0];

    for (int i = 1; i < n; i++)
    {
        if (coins[i] > goodWeight)
            goodWeight = coins[i];
    }

    int defective = findDefective(coins, 0, n - 1, goodWeight);

    printf("\nRequired coin weight = %d\n", goodWeight);

    if (defective == -1)
    {
        printf("No defective coin found.\n");
    }
    else
    {
        printf("Defective coin found at position %d.\n", defective + 1);
        printf("Defective coin weight = %d\n", coins[defective]);
    }

    free(coins);

    return 0;
}
