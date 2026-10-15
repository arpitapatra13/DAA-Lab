#include <stdio.h>
#include <float.h>

void optimalBST(int n, double p[], double q[]) {
    double e[n + 2][n + 2];
    double w[n + 2][n + 2];
    int root[n + 1][n + 1];

    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("Minimum Expected Search Cost = %.4f\n", e[1][n]);
}

int main() {
    int n;
    scanf("%d", &n);

    double p[n + 1];
    double q[n + 1];

    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }

    for (int i = 0; i <= n; i++) {
        scanf("%lf", &q[i]);
    }

    optimalBST(n, p, q);

    return 0;
}
