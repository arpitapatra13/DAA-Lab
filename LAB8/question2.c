#include <stdio.h>
long long countWays(int coins[], int n, int V) {
    long long dp[V + 1];
    for (int i = 0; i <= V; i++)
        dp[i] = 0;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= V; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    return dp[V];
}
int main() {
    int n, V;
    scanf("%d", &n);
    int coins[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);
    scanf("%d", &V);
    printf("%lld\n", countWays(coins, n, V));
    return 0;
}
