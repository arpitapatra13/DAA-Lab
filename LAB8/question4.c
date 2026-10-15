#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int A[n], dp[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        dp[i] = 1;
    }
    int maxLength = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i] && dp[j] + 1 > dp[i])
                dp[i] = dp[j] + 1;
        }
        if (dp[i] > maxLength)
            maxLength = dp[i];
    }
    printf("Length of LIS = %d\n", maxLength);
    return 0;
}
