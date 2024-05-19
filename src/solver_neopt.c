/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

double *my_solver(int N, double *A, double *B) {
  // Memory allocation
  double *At = (double *)calloc(N * N, sizeof(double));
  double *Bt = (double *)calloc(N * N, sizeof(double));
  double *AtB = (double *)calloc(N * N, sizeof(double));
  double *BA = (double *)calloc(N * N,  sizeof(double));
  double *sum = (double *)malloc(N * N * sizeof(double));
  double *C = (double *)calloc(N * N, sizeof(double));

  // Transpose B
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      Bt[j * N + i] = B[i * N + j];
    }
  }

  //   Transpose A
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      At[i * N + j] = A[j * N + i];
    }
  }

  // At * B = AtB
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k <= i; k++) {
        AtB[i * N + j] += At[i * N + k] * B[k * N + j];
      }
    }
  }

  // B * A = BA
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k <= j; k++) {
        BA[i * N + j] += B[i * N + k] * A[k * N + j];
      }
    }
  }

  // AtB + BA = sum
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      sum[i * N + j] = AtB[i * N + j] + BA[i * N + j];
    }
  }

  // sum * Bt = C
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k <= j; k++) {
        C[i * N + j] += sum[i * N + k] * Bt[k * N + j];
      }
    }
  }

  // Free memory
  free(At);
  free(Bt);
  free(AtB);
  free(BA);
  free(sum);

  return C;
}
