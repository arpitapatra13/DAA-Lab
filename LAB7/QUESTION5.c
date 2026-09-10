#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("Enter number of hiding spots n (n > 1): ");
    if (scanf("%d", &n) != 1 || n < 2) { fprintf(stderr, "invalid n\n"); return 1; }

    /* Build the shot sequence: 2,3,...,n, n,n-1,...,2 */
    int len = 2 * (n - 1);
    int *shots = malloc(len * sizeof(int));
    int idx = 0;
    for (int s = 2; s <= n; s++) shots[idx++] = s;
    for (int s = n; s >= 2; s--) shots[idx++] = s;

    printf("Shot sequence (%d shots): ", len);
    for (int i = 0; i < len; i++) printf("%d ", shots[i]);
    printf("\n\n");

    /* Verify via possible-position-set simulation */
    char *possible = malloc((n + 2) * sizeof(char)); /* 1-indexed, possible[0],[n+1] unused */
    char *next = malloc((n + 2) * sizeof(char));
    for (int i = 1; i <= n; i++) possible[i] = 1;

    int hit_guaranteed_at = -1;
    for (int t = 0; t < len; t++) {
        int s = shots[t];
        /* remove s (target cannot have been there and survived) */
        possible[s] = 0;
        int any = 0;
        for (int i = 1; i <= n; i++) if (possible[i]) any = 1;
        if (!any) { hit_guaranteed_at = t + 1; break; }
        /* expand by one adjacency step: new possible[i] = old possible[i-1] or possible[i+1] */
        for (int i = 1; i <= n; i++) {
            int left = (i - 1 >= 1) ? possible[i - 1] : 0;
            int right = (i + 1 <= n) ? possible[i + 1] : 0;
            next[i] = left || right;
        }
        for (int i = 1; i <= n; i++) possible[i] = next[i];
    }

    if (hit_guaranteed_at != -1)
        printf("Result: guaranteed hit proven within %d shots (out of %d fired), for n=%d.\n",
               hit_guaranteed_at, len, n);
    else
        printf("Result: possible-position set never emptied -- sequence NOT verified for n=%d.\n", n);

    free(shots); free(possible); free(next);
    return 0;
}
