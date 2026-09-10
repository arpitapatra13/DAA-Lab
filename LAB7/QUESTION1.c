#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct { int x, y; } Point;
static int cmp_point(const void *a, const void *b) {
    const Point *p = a, *q = b;
    if (p->x != q->x) return p->x - q->x;
    return p->y - q->y;
}
 
static int point_in_sorted(Point *arr, int n, Point p) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int c = cmp_point(&arr[mid], &p);
        if (c == 0) return 1;
        if (c < 0) lo = mid + 1; else hi = mid - 1;
    }
    return 0;
}
 
static Point *build_up(int n, int *count) {
    int N = n * (n + 1) / 2;
    Point *pts = malloc(N * sizeof(Point));
    int idx = 0;
    for (int y = 0; y < n; y++)
        for (int c = 0; c <= y; c++)
            pts[idx++] = (Point){2 * c - y, y};
    *count = N;
    return pts;
}
 
static Point *build_down(Point *up, int n, int count) {
    Point *pts = malloc(count * sizeof(Point));
    for (int i = 0; i < count; i++)
        pts[i] = (Point){up[i].x, (n - 1) - up[i].y};
    return pts;
}
static int max_overlap(Point *up, int upN, Point *down, int downN, int n,
                        int *best_dx, int *best_dy) {
    Point *up_sorted = malloc(upN * sizeof(Point));
    memcpy(up_sorted, up, upN * sizeof(Point));
    qsort(up_sorted, upN, sizeof(Point), cmp_point);
 
    int best = -1;
    for (int dx = -2 * n; dx <= 2 * n; dx++) {
        for (int dy = -n; dy <= n; dy++) {
            int overlap = 0;
            for (int i = 0; i < downN; i++) {
                Point shifted = {down[i].x + dx, down[i].y + dy};
                if (point_in_sorted(up_sorted, upN, shifted)) overlap++;
            }
            if (overlap > best) {
                best = overlap;
                *best_dx = dx;
                *best_dy = dy;
            }
        }
    }
    free(up_sorted);
    return best;
}
 
static long formula_moves(int n) {
    long m = n - 1;
    long q = m / 3, r = m % 3;
    return (n - 1) + 3 * q * (q - 1) / 2 + r * q;
}
 
int main(void) {
    int n;
    printf("Invert the coin-triangle\n");
    printf("Enter number of rows n of the coin triangle: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
 
    long total = (long)n * (n + 1) / 2;
    printf("Total coins = %ld\n", total);
    long formula_ans = formula_moves(n);
    printf("Minimum moves (O(1) formula)      = %ld\n", formula_ans);
 
    if (n <= 40) {
        int upN, downN;
        Point *up = build_up(n, &upN);
        Point *down = build_down(up, n, upN);
        downN = upN;
        int dx, dy;
        int overlap = max_overlap(up, upN, down, downN, n, &dx, &dy);
        long moves = total - overlap;
        printf("Minimum moves (brute-force check) = %ld  (best shift dx=%d dy=%d)\n",
               moves, dx, dy);
        printf("%s\n", moves == formula_ans ? "[OK] formula matches brute-force search"
                                             : "[MISMATCH]");
        free(up);
        free(down);
    } else {
        printf("(brute-force validation skipped for n > 40, too slow)\n");
    }
 
    return 0;
}
