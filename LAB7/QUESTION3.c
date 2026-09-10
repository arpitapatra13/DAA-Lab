#include <stdio.h>
#include <stdlib.h>

long long T4[100], T3pow[100]; /* T4[i] = min moves 4-peg, T3pow[i]=2^i-1 */
int bestk[100];
long move_count = 0;

void hanoi3(int n, int src, int dst, int aux, int report) {
    /* classical 3-peg hanoi, used for the "middle" phase */
    if (n == 0) return;
    hanoi3(n - 1, src, aux, dst, report);
    move_count++;
    if (report) printf("Move disk %d: peg %d -> peg %d\n", n, src, dst);
    hanoi3(n - 1, aux, dst, src, report);
}

void hanoi4(int n, int src, int dst, int aux1, int aux2, int report) {
    if (n == 0) return;
    if (n == 1) {
        move_count++;
        if (report) printf("Move disk %d: peg %d -> peg %d\n", n, src, dst);
        return;
    }
    int k = bestk[n];
    hanoi4(k, src, aux1, dst, aux2, report);         /* step 2 */
    hanoi3(n - k, src, dst, aux2, report);            /* step 3 (3-peg) */
    hanoi4(k, aux1, dst, src, aux2, report);           /* step 4 */
}

int main(void) {
    int n;
    printf("Enter number of disks n (Reve's puzzle uses n = 8): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 60) { fprintf(stderr, "invalid n\n"); return 1; }

    /* Precompute 3-peg move counts and 4-peg DP */
    T3pow[0] = 0;
    for (int i = 1; i <= n; i++) T3pow[i] = 2 * T3pow[i - 1] + 1; /* 2^i - 1 */

    T4[0] = 0;
    for (int i = 1; i <= n; i++) {
        long long best = -1; int bk = -1;
        for (int k = 1; k < i; k++) {
            long long cost = 2 * T4[k] + T3pow[i - k];
            if (best == -1 || cost < best) { best = cost; bk = k; }
        }
        if (i == 1) { best = 1; bk = 0; } /* base case handled separately */
        T4[i] = best;
        bestk[i] = bk;
    }

    printf("\nMinimum move counts T4(i) for i = 1..%d:\n", n);
    for (int i = 1; i <= n; i++) printf("  T4(%2d) = %lld\n", i, T4[i]);

    printf("\nFor n = 8, Reve's puzzle minimum moves = %lld", n >= 8 ? T4[8] : -1);
    if (n >= 8) printf("  (classic answer: 33, %s)\n", T4[8] == 33 ? "MATCH" : "MISMATCH");
    else printf("\n");

    printf("\nGenerating and verifying the explicit move sequence for n = %d:\n", n);
    move_count = 0;
    int report = (n <= 6); /* only print full move list for small n */
    hanoi4(n, 0, 3, 1, 2, report);
    printf("Total moves generated = %ld  (expected T4(%d) = %lld) -> %s\n",
           move_count, n, T4[n], (move_count == T4[n]) ? "OK" : "MISMATCH");
    return 0;
}
