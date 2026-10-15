#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double v;
    double w;
    double lambda;
    double ratio;
} Item;

int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemB->ratio > itemA->ratio) return 1;
    if (itemB->ratio < itemA->ratio) return -1;
    return 0;
}

int main() {
    int n;
    double W;
    if (scanf("%d %lf", &n, &W) != 2) return 0;

    Item items[n];
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        scanf("%lf %lf %lf", &items[i].v, &items[i].w, &items[i].lambda);
        items[i].ratio = (items[i].v / items[i].w) / items[i].lambda;
    }

    qsort(items, n, sizeof(Item), compare);

    double cur_W = 0.0;
    double total_value = 0.0;
    double time_elapsed = 0.0;

    printf("Scheduled Execution Order:\n");
    for (int i = 0; i < n; i++) {
        if (cur_W >= W) break;

        double take_w = (W - cur_W < items[i].w) ? (W - cur_W) : items[i].w;
        double fraction = take_w / items[i].w;

        double effective_density = (items[i].v / items[i].w) - (items[i].lambda * time_elapsed);
        if (effective_density < 0) effective_density = 0;

        double item_val = take_w * effective_density;
        total_value += item_val;

        printf("Item %d: Fraction = %.2f, Weight Taken = %.2f, Value Density = %.2f, Value Gained = %.2f\n",
               items[i].id, fraction, take_w, effective_density, item_val);

        cur_W += take_w;
        time_elapsed += take_w;
    }

    printf("Maximum Decayed Total Value = %.2f\n", total_value);
    return 0;
}
