#include <stdio.h>
#include <string.h>
int main() {
    char X[100], Y[100];
    scanf("%s", X);
    scanf("%s", Y);
    int m = strlen(X);
    int n = strlen(Y);
    int dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= n; j++)
        dp[0][j] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1]
                         ? dp[i - 1][j]
                         : dp[i][j - 1];
            }
        }
    }
    printf("LCS Length = %d\n", dp[m][n]);
    int len = dp[m][n];
    char lcs[len + 1];
    lcs[len] = '\0';
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[len - 1] = X[i - 1];
            len--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    printf("LCS = %s\n", lcs);
    return 0;
}
