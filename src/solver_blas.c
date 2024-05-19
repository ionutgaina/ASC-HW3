/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas.h>

double *my_solver(int N, double *A, double *B) {
  // Memory allocation
  double *AtB = (double *)malloc(N * N * sizeof(double));
  double *BA = (double *)malloc(N * N * sizeof(double));
  double *C = (double *)malloc(N * N * sizeof(double));

  // copy B into AtB
  for (int i = 0; i < N * N; ++i) {
    AtB[i] = B[i];
  }

  // At * B = AtB
  cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N,
              N, 1.0, A, N, AtB, N);

  // copy B into BA
  for (int i = 0; i < N * N; ++i) {
    BA[i] = B[i];
  }

  // B * A = BA
  cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit,
              N, N, 1.0, A, N, BA, N);

  // Sum = AtB + BA
  for (int i = 0; i < N * N; ++i) {
    C[i] = AtB[i] + BA[i];
  }

  // sum * Bt = C
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, C, N, B, N,
              0.0, C, N);

  // Free memory
  free(AtB);
  free(BA);

  return C;
}