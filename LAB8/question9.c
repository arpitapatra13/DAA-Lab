#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Functional decomposition: step calculation with overflow protection
unsigned long long next_collatz(unsigned long long n) {
    if (n % 2 == 0) {
        return n / 2;
    } else {
        if (n > (ULLONG_MAX - 1) / 3) {
            printf("Overflow detected for n = %llu!\n", n);
            return 0;
        }
        return 3 * n + 1;
    }
}

// Computes single trajectory using dynamic memory allocation
unsigned long long* get_trajectory(unsigned long long n, int *out_steps, unsigned long long *out_peak) {
    int capacity = 100;
    int steps = 0;
    unsigned long long peak = n;

    unsigned long long *trajectory = (unsigned long long*) malloc(capacity * sizeof(unsigned long long));
    if (!trajectory) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    unsigned long long curr = n;
    trajectory[steps++] = curr;

    while (curr > 1) {
        curr = next_collatz(curr);
        if (curr == 0) break; // Overflow guard

        if (curr > peak) peak = curr;

        if (steps >= capacity) {
            capacity *= 2;
            trajectory = (unsigned long long*) realloc(trajectory, capacity * sizeof(unsigned long long));
            if (!trajectory) {
                printf("Memory reallocation failed!\n");
                exit(1);
            }
        }
        trajectory[steps++] = curr;
    }

    *out_steps = steps - 1; // Number of transitions
    *out_peak = peak;
    return trajectory;
}

// Dynamic analysis across an interval [a, b]
void analyze_interval(unsigned long long a, unsigned long long b) {
    unsigned long long max_steps_num = a;
    int max_steps = 0;
    unsigned long long highest_peak_num = a;
    unsigned long long max_peak = 0;

    for (unsigned long long i = a; i <= b; i++) {
        int steps;
        unsigned long long peak;
        unsigned long long *traj = get_trajectory(i, &steps, &peak);

        if (steps > max_steps) {
            max_steps = steps;
            max_steps_num = i;
        }
        if (peak > max_peak) {
            max_peak = peak;
            highest_peak_num = i;
        }
        free(traj);
    }

    printf("Interval [%llu, %llu] Analysis:\n", a, b);
    printf("Max Steps: %d (Starting at n = %llu)\n", max_steps, max_steps_num);
    printf("Highest Peak: %llu (Starting at n = %llu)\n", max_peak, highest_peak_num);
}

int main() {
    unsigned long long n;
    printf("Enter starting value n: ");
    if (scanf("%llu", &n) != 1 || n < 1) {
        printf("Invalid input!\n");
        return 1;
    }

    int steps;
    unsigned long long peak;
    unsigned long long *traj = get_trajectory(n, &steps, &peak);

    printf("Trajectory for n = %llu:\n", n);
    for (int i = 0; i <= steps; i++) {
        printf("%llu ", traj[i]);
    }
    printf("\nTotal Steps = %d\n", steps);
    printf("Peak Value = %llu\n", peak);
    free(traj);

    unsigned long long a, b;
    printf("Enter interval [a, b]: ");
    if (scanf("%llu %llu", &a, &b) == 2 && a >= 1 && b >= a) {
        analyze_interval(a, b);
    }

    return 0;
}
