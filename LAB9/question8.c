#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int start[n];
    int end[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }

    qsort(start, n, sizeof(int), compare);
    qsort(end, n, sizeof(int), compare);

    int s_ptr = 0, e_ptr = 0;
    int rooms = 0, max_rooms = 0;

    while (s_ptr < n) {
        if (start[s_ptr] < end[e_ptr]) {
            rooms++;
            s_ptr++;
        } else {
            rooms--;
            e_ptr++;
        }
        
        
        if (rooms > max_rooms) {
            max_rooms = rooms;
        }
    }

    printf("Minimum Meeting Rooms Required = %d\n", max_rooms);
    return 0;
}
