/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas.h>

double *my_solver(int N, double *A, double *B) {
  // Memory allocation
  double *AtB = (double *)calloc(N * N, sizeof(double));
  double *BA = (double *)calloc(N * N, sizeof(double));
  double *C = (double *)calloc(N * N, sizeof(double));


  // At * B = AtB
  cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1.0, A, N, B, N, 0.0, AtB, N);

  // B * A = BA
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, B, N, A, N, 0.0, BA, N);

  // Sum = AtB + BA
  for (int i = 0; i < N * N; ++i) {
    C[i] = AtB[i] + BA[i];
  }

  // sum * Bt = C
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, C, N, B, N, 0.0, C, N);

  // Free memory
  free(AtB);
  free(BA);

  return C;
}