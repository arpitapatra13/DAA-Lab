#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int type;   /* 0 = death (-1), 1 = birth (+1)   -- deaths sort first on ties */
} Event;

int cmp(const void *a, const void *b) {
    const Event *e1 = a, *e2 = b;
    if (e1->year != e2->year) return e1->year - e2->year;
    return e1->type - e2->type; /* death(0) before birth(1) on same year */
}

int main(void) {
    int n;
    printf("Enter number of scientists n: ");
    if (scanf("%d", &n) != 1 || n < 1) { fprintf(stderr, "invalid n\n"); return 1; }

    Event *ev = malloc(2 * n * sizeof(Event));
    printf("Enter %d lines of 'birth_year death_year':\n", n);
    for (int i = 0; i < n; i++) {
        int b, d;
        if (scanf("%d %d", &b, &d) != 2 || d < b) { fprintf(stderr, "invalid record\n"); return 1; }
        ev[2 * i]     = (Event){ b, 1 };
        ev[2 * i + 1] = (Event){ d, 0 };
    }

    qsort(ev, 2 * n, sizeof(Event), cmp);

    int cur = 0, best = 0, best_year = ev[0].year;
    for (int i = 0; i < 2 * n; i++) {
        if (ev[i].type == 1) { cur++; if (cur > best) { best = cur; best_year = ev[i].year; } }
        else cur--;
    }

    printf("\nMaximum number of scientists alive simultaneously = %d\n", best);
    printf("This maximum is first attained in the year = %d\n", best_year);

    free(ev);
    return 0;
}
