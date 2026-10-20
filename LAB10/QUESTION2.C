#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
    int R, C;
    int *parent;
    int *rank;
    bool *is_land;
    int island_count;
} GridDSU;

GridDSU* create_grid_dsu(int R, int C) {
    GridDSU *grid = (GridDSU *)malloc(sizeof(GridDSU));
    grid->R = R;
    grid->C = C;
    int total = R * C;
    grid->parent = (int *)malloc(total * sizeof(int));
    grid->rank = (int *)malloc(total * sizeof(int));
    grid->is_land = (bool *)calloc(total, sizeof(bool));
    grid->island_count = 0;
    for (int i = 0; i < total; i++) {
        grid->parent[i] = i;
        grid->rank[i] = 0;
    }
    return grid;
}

int find_root(GridDSU *grid, int x) {
    if (grid->parent[x] == x)
        return x;
    return grid->parent[x] = find_root(grid, grid->parent[x]);
}

bool union_cells(GridDSU *grid, int x, int y) {
    int root_x = find_root(grid, x);
    int root_y = find_root(grid, y);
    if (root_x == root_y)
        return false;

    if (grid->rank[root_x] < grid->rank[root_y]) {
        grid->parent[root_x] = root_y;
    } else {
        grid->parent[root_y] = root_x;
        if (grid->rank[root_x] == grid->rank[root_y])
            grid->rank[root_x]++;
    }
    return true;
}

int add_land(GridDSU *grid, int r, int c) {
    if (r < 0 || r >= grid->R || c < 0 || c >= grid->C) {
        return grid->island_count;
    }

    int idx = r * grid->C + c;
    if (grid->is_land[idx]) {
        // Already land cell
        return grid->island_count;
    }

    grid->is_land[idx] = true;
    grid->parent[idx] = idx;
    grid->rank[idx] = 0;
    grid->island_count++;

    // 4 cardinal directions: Up, Down, Left, Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];

        if (nr >= 0 && nr < grid->R && nc >= 0 && nc < grid->C) {
            int n_idx = nr * grid->C + nc;
            if (grid->is_land[n_idx]) {
                if (union_cells(grid, idx, n_idx)) {
                    grid->island_count--;
                }
            }
        }
    }

    return grid->island_count;
}

void free_grid_dsu(GridDSU *grid) {
    free(grid->parent);
    free(grid->rank);
    free(grid->is_land);
    free(grid);
}

int main() {
    int R, C, K;
    if (scanf("%d %d %d", &R, &C, &K) != 3) return 0;

    GridDSU *grid = create_grid_dsu(R, C);

    printf("Dynamic Connected Components in Grid (%d x %d):\n", R, C);
    printf("Total Land Additions: %d\n\n", K);

    for (int i = 1; i <= K; i++) {
        int r, c;
        if (scanf("%d %d", &r, &c) != 2) break;

        int count = add_land(grid, r, c);
        printf("Operation %2d: Add land at (%d, %d) -> Islands Count = %d\n", i, r, c, count);
    }

    free_grid_dsu(grid);
    return 0;
}
