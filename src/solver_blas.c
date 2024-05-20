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

  // copy B into AtB
  cblas_dcopy(N * N, B, 1, AtB, 1);

  // At * B = AtB
  cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N,
              N, 1.0, A, N, AtB, N);

  // copy B into BA
  cblas_dcopy(N * N, B, 1, BA, 1);

  // B * A = BA
  cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit,
              N, N, 1.0, A, N, BA, N);

  // Sum = AtB + BA
  cblas_daxpy(N * N, 1.0, AtB, 1, BA, 1);

  // sum * Bt = C
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, BA, N, B, N,
              0.0, BA, N);

  // Free memory
  free(AtB);

  return BA;
}