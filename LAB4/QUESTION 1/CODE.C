#include <stdio.h>
#include <string.h>

#define RED 0
#define BLUE 1
#define YELLOW 2

typedef struct {
    int number;
    int colour;
} Item;

int colourCode(char c) {
    if (c == 'R') return RED;
    if (c == 'B') return BLUE;
    return YELLOW;
}

char colourName(int c) {
    if (c == RED) return 'R';
    if (c == BLUE) return 'B';
    return 'Y';
}

void sortByColour(Item a[], Item output[], int n) {
    int count[3] = {0, 0, 0};

    // Count each colour
    for (int i = 0; i < n; i++)
        count[a[i].colour]++;

    // Starting positions of each colour
    int start[3];
    start[RED] = 0;
    start[BLUE] = count[RED];
    start[YELLOW] = count[RED] + count[BLUE];

    int pos[3] = {start[RED], start[BLUE], start[YELLOW]};

    // Stable placement: scan input from left to right
    for (int i = 0; i < n; i++) {
        int c = a[i].colour;
        output[pos[c]] = a[i];
        pos[c]++;
    }
}

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item a[n], output[n];

    printf("Enter number and colour (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        char c;
        scanf("%d %c", &a[i].number, &c);
        a[i].colour = colourCode(c);
    }

    sortByColour(a, output, n);

    printf("\nItems sorted by colour:\n");

    for (int i = 0; i < n; i++) {
        printf("(%d, %c) ", output[i].number,
               colourName(output[i].colour));
    }

    printf("\n");

    return 0;
}
