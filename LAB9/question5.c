#include <stdio.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int ratings[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &ratings[i]);
    }

    int candies[n];
    for (int i = 0; i < n; i++) {
        candies[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            if (candies[i + 1] + 1 > candies[i]) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    int totalCandies = 0;
    printf("Candies Allocated to Each Child:\n");
    for (int i = 0; i < n; i++) {
        printf("Child %d (Rating %d): %d candies\n", i + 1, ratings[i], candies[i]);
        totalCandies += candies[i];
    }

    printf("Minimum Total Candies Needed = %d\n", totalCandies);
    return 0;
}
