#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min3(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

int main() {
    char A[100], B[100];
    scanf("%s", A);
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min3(dp[i - 1][j],      // Delete
                                   dp[i][j - 1],      // Insert
                                   dp[i - 1][j - 1]); // Substitute
        }
    }

    printf("Minimum Edit Distance = %d\n", dp[m][n]);

    // Traceback reconstruction
    int i = m, j = n;
    char ops[200][100];
    int op_count = 0;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] && dp[i][j] == dp[i - 1][j - 1]) {
            sprintf(ops[op_count++], "Keep '%c'", A[i - 1]);
            i--; j--;
        }
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            sprintf(ops[op_count++], "Substitute '%c' -> '%c'", A[i - 1], B[j - 1]);
            i--; j--;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            sprintf(ops[op_count++], "Delete '%c'", A[i - 1]);
            i--;
        }
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            sprintf(ops[op_count++], "Insert '%c'", B[j - 1]);
            j--;
        }
    }

    printf("Traceback Operations:\n");
    for (int k = op_count - 1; k >= 0; k--) {
        printf("%d. %s\n", op_count - k, ops[k]);
    }

    return 0;
}
