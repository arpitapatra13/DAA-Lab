#include <stdio.h>
#include <stdlib.h>
int min_trials(int E, int F) {
    if (F <= 0) return 0;
    long *prev = calloc(E + 1, sizeof(long));
    long *cur  = calloc(E + 1, sizeof(long));
    int t = 0;
    while (1) {
        t++;
        cur[0] = 0;
        for (int k = 1; k <= E; k++) {
            cur[k] = prev[k - 1] + prev[k] + 1;
        }
        if (cur[E] >= F) { free(prev); free(cur); return t; }
        for (int k = 0; k <= E; k++) prev[k] = cur[k];
    }
}

int main(void) {
    int E, F;
    printf("Enter number of eggs E and number of floors F: ");
    if (scanf("%d %d", &E, &F) != 2 || E < 1 || F < 1) {
        fprintf(stderr, "invalid input\n"); return 1;
    }
    int t = min_trials(E, F);
    printf("Minimum number of droppings guaranteed to find the critical\n"
           "floor with %d egg(s) and %d floor(s): %d\n", E, F, t);

    /* Sanity check against the classical case: 2 eggs, 100 floors -> 14 */
    if (E == 2 && F == 100)
        printf("(Matches the well-known textbook answer: 14.)\n");
    return 0;
}
