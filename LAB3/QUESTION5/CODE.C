#include <stdio.h>
#include <stdlib.h>

void add(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void multiplySpecial(int **X, int **Y, int **Z, int n)
{
    if (n == 1)
    {
        Z[0][0] = X[0][0] * Y[0][0];
        return;
    }

    int k = n / 2;

    
    int **A = malloc(k * sizeof(int *));
    int **B = malloc(k * sizeof(int *));
    int **C = malloc(k * sizeof(int *));
    int **D = malloc(k * sizeof(int *));

    int **P = malloc(k * sizeof(int *));
    int **Q = malloc(k * sizeof(int *));
    int **R = malloc(k * sizeof(int *));
    int **S = malloc(k * sizeof(int *));

    int **U = malloc(k * sizeof(int *));
    int **V = malloc(k * sizeof(int *));
    int **T1 = malloc(k * sizeof(int *));
    int **T2 = malloc(k * sizeof(int *));

    for (int i = 0; i < k; i++)
    {
        A[i] = malloc(k * sizeof(int));
        B[i] = malloc(k * sizeof(int));
        C[i] = malloc(k * sizeof(int));
        D[i] = malloc(k * sizeof(int));

        P[i] = malloc(k * sizeof(int));
        Q[i] = malloc(k * sizeof(int));
        R[i] = malloc(k * sizeof(int));
        S[i] = malloc(k * sizeof(int));

        U[i] = malloc(k * sizeof(int));
        V[i] = malloc(k * sizeof(int));
        T1[i] = malloc(k * sizeof(int));
        T2[i] = malloc(k * sizeof(int));
    }

   
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A[i][j] = X[i][j];
            B[i][j] = X[i][j + k];

            C[i][j] = Y[i][j];
            D[i][j] = Y[i][j + k];
        }
    }

    
    add(A, B, P, k);
    sub(A, B, Q, k);

    
    add(C, D, R, k);
    sub(C, D, S, k);

    
    multiplySpecial(P, R, U, k);
    multiplySpecial(Q, S, V, k);

    
    add(U, V, T1, k);
    sub(U, V, T2, k);

    
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            Z[i][j] = T1[i][j] / 2;
            Z[i][j + k] = T2[i][j] / 2;
            Z[i + k][j] = T2[i][j] / 2;
            Z[i + k][j + k] = T1[i][j] / 2;
        }
    }

   
    for (int i = 0; i < k; i++)
    {
        free(A[i]); free(B[i]);
        free(C[i]); free(D[i]);
        free(P[i]); free(Q[i]);
        free(R[i]); free(S[i]);
        free(U[i]); free(V[i]);
        free(T1[i]); free(T2[i]);
    }

    free(A); free(B); free(C); free(D);
    free(P); free(Q); free(R); free(S);
    free(U); free(V); free(T1); free(T2);
}

int main()
{
    int n = 4;

    int **X = malloc(n * sizeof(int *));
    int **Y = malloc(n * sizeof(int *));
    int **Z = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        X[i] = malloc(n * sizeof(int));
        Y[i] = malloc(n * sizeof(int));
        Z[i] = malloc(n * sizeof(int));
    }

   
    int x[4][4] = {
        {1, 2, 3, 4},
        {2, 1, 4, 3},
        {3, 4, 1, 2},
        {4, 3, 2, 1}
    };

    
    int y[4][4] = {
        {5, 6, 7, 8},
        {6, 5, 8, 7},
        {7, 8, 5, 6},
        {8, 7, 6, 5}
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            X[i][j] = x[i][j];
            Y[i][j] = y[i][j];
        }

    multiplySpecial(X, Y, Z, n);

    printf("Matrix X:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%4d", X[i][j]);
        printf("\n");
    }

    printf("\nMatrix Y:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%4d", Y[i][j]);
        printf("\n");
    }

    printf("\nProduct X * Y:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%4d", Z[i][j]);
        printf("\n");
    }

    printf("\nTime Complexity: O(n^2)\n");

    for (int i = 0; i < n; i++)
    {
        free(X[i]);
        free(Y[i]);
        free(Z[i]);
    }

    free(X);
    free(Y);
    free(Z);

    return 0;
}
