#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int A[n], dp[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        dp[i] = A[i];
    }
    int maxSum = A[0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {

            if (A[j] < A[i] && dp[j] + A[i] > dp[i])
                dp[i] = dp[j] + A[i];
        }
        if (dp[i] > maxSum)
            maxSum = dp[i];
    }
    printf("Maximum Sum = %d\n", maxSum);
    return 0;
}
