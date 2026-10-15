#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int price[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }

    int r[n + 1];
    int s[n + 1];

    r[0] = 0;
    s[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_rev = -1;
        int best_cut = 0;
        for (int j = 1; j <= i; j++) {
            if (price[j] + r[i - j] > max_rev) {
                max_rev = price[j] + r[i - j];
                best_cut = j;
            }
        }
        r[i] = max_rev;
        s[i] = best_cut;
    }

    printf("Maximum Revenue = %d\n", r[n]);
    printf("Optimal Piece Lengths: ");
    int temp = n;
    while (temp > 0) {
        printf("%d ", s[temp]);
        temp = temp - s[temp];
    }
    printf("\n");

    return 0;
}
