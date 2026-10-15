#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findOverlap(const char *s1, const char *s2, char *merged) {
    int max_overlap = 0;
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    for (int k = 1; k <= len1 && k <= len2; k++) {
        if (strncmp(s1 + len1 - k, s2, k) == 0) {
            max_overlap = k;
        }
    }

    strcpy(merged, s1);
    strcat(merged, s2 + max_overlap);
    return max_overlap;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    char strings[50][200];
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i]);
    }

    printf("Greedy Superstring Merging Trajectory:\n");
    int count = n;
    int step = 1;

    while (count > 1) {
        int max_ov = -1;
        int best_i = -1, best_j = -1;
        char best_merged[400];

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                if (i != j) {
                    char temp[400];
                    int ov = findOverlap(strings[i], strings[j], temp);
                    if (ov > max_ov) {
                        max_ov = ov;
                        best_i = i;
                        best_j = j;
                        strcpy(best_merged, temp);
                    }
                }
            }
        }

        printf("Step %d: Merge \"%s\" and \"%s\" (Overlap = %d) -> \"%s\"\n",
               step++, strings[best_i], strings[best_j], max_ov, best_merged);

        strcpy(strings[best_i], best_merged);
        for (int k = best_j; k < count - 1; k++) {
            strcpy(strings[k], strings[k + 1]);
        }
        count--;
    }

    printf("\nFinal Greedy Superstring = %s\n", strings[0]);
    printf("Superstring Length = %d\n", (int)strlen(strings[0]));
    return 0;
}
