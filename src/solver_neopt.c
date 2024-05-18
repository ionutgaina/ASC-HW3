/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

void transpose(int N, double *src, double *dest) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dest[j * N + i] = src[i * N + j];
        }
    }
}

void multiply(int N, double *A, double *B, double *result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i * N + j] = 0.0;
            for (int k = 0; k < N; ++k) {
                result[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

void add(int N, double *A, double *B, double *result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i * N + j] = A[i * N + j] + B[i * N + j];
        }
    }
}

double* my_solver(int N, double *A, double* B) {
    // Memory allocation
    double *At = (double *)malloc(N * N * sizeof(double));
    double *Bt = (double *)malloc(N * N * sizeof(double));
    double *AtB = (double *)malloc(N * N * sizeof(double));
    double *BA = (double *)malloc(N * N * sizeof(double));
    double *sum = (double *)malloc(N * N * sizeof(double));
    double *C = (double *)malloc(N * N * sizeof(double));

    // Tranpose A and B
    transpose(N, A, At);
    transpose(N, B, Bt);

    // At * B = AtB
    multiply(N, At, B, AtB);

    // B * A = BA
    multiply(N, B, A, BA);

    // AtB + BA = sum
    add(N, AtB, BA, sum);

    // (sum) * Bt = C
    multiply(N, sum, Bt, C);

    // Free memory
    free(At);
    free(Bt);
    free(AtB);
    free(BA);
    free(sum);

    return C;
}
