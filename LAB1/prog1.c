#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[40];
    double logval;
} Func;

int cmp(const void *a, const void *b) {
    double da = ((Func*)a)->logval;
    double db = ((Func*)b)->logval;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

int main() {
    double L = 100000.0;      
    double n = pow(2.0, L);

    Func f[12];
    int i = 0;

    strcpy(f[i].name, "1/n");
    f[i++].logval = -L;

    strcpy(f[i].name, "log2(n)");
    f[i++].logval = log2(L);

    strcpy(f[i].name, "12*sqrt(n)");
    f[i++].logval = log2(12.0) + 0.5*L;

    strcpy(f[i].name, "50*n^0.5");
    f[i++].logval = log2(50.0) + 0.5*L;

    strcpy(f[i].name, "n^0.51");
    f[i++].logval = 0.51*L;

    strcpy(f[i].name, "2^32 * n");
    f[i++].logval = 32.0 + L;

    strcpy(f[i].name, "n*log2(n)");
    f[i++].logval = L + log2(L);

    strcpy(f[i].name, "n^2 - 324");
    f[i++].logval = 2*L;

    strcpy(f[i].name, "100n^2 + 6n");
    f[i++].logval = log2(100.0) + 2*L;

    strcpy(f[i].name, "2n^3");
    f[i++].logval = 1.0 + 3*L;

    strcpy(f[i].name, "n^log2(n)");
    f[i++].logval = L*L;

    strcpy(f[i].name, "3^n");
    f[i++].logval = n * log2(3.0);

    qsort(f, 12, sizeof(Func), cmp);

    printf("Order of growth (increasing), n -> infinity:\n\n");
    for (int k = 0; k < 12; k++) {
        printf("%2d. %-15s (log2 f(n) ~ %.6g)\n", k+1, f[k].name, f[k].logval);
    }
    return 0;
}