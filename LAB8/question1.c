#include <stdio.h>
#include <limits.h>
int minCoins(int coins[], int n, int V) {
    int dp[V + 1];
    dp[0] = 0;
    for (int i = 1; i <= V; i++)
        dp[i] = INT_MAX;
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                if (dp[i - coins[j]] + 1 < dp[i])
                    dp[i] = dp[i - coins[j]] + 1;
            }
        }
    }
    return dp[V] == INT_MAX ? -1 : dp[V];
}
int main() {
    int n, V;
    scanf("%d", &n);
    int coins[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);
    scanf("%d", &V);
    printf("%d\n", minCoins(coins, n, V));
    return 0;
}
