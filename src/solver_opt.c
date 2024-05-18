/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double *my_solver(int N, double *A, double *B) {
  // Memory allocation
  double *At = (double *)calloc(N * N, sizeof(double));
  double *Bt = (double *)malloc(N * N * sizeof(double));
  double *AtB = (double *)malloc(N * N * sizeof(double));
  double *BA = (double *)malloc(N * N * sizeof(double));
  double *sum = (double *)malloc(N * N * sizeof(double));
  double *C = (double *)malloc(N * N * sizeof(double));

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
    double *orig_pa = &At[i * N];

    for (int j = 0; j < N; j++) {
      double *pa = orig_pa;
      double *pb = &B[j];

      register double suma = 0;
      for (int k = 0; k <= i; k++) {
        suma += *pa * *pb;
        ++pa;
        pb += N;
      }
      AtB[i * N + j] = suma;
    }
  }

  // B * A = BA
  for (int i = 0; i < N; i++) {
    double *orig_pb = &B[i * N];
    for (int j = 0; j < N; j++) {
      double *pb = orig_pb;
      double *pa = &A[j];

      register double suma = 0;
      for (int k = 0; k <= j; k++) {
        suma += *pa * *pb;
        ++pb;
        pa += N;
      }
      BA[i * N + j] = suma;
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
    double *orig_sum = &sum[i * N];
    for (int j = 0; j < N; j++) {
      double *pa = orig_sum;
      double *pb = &Bt[j];
      register double suma = 0;
      for (int k = 0; k < N; k++) {
        suma += *pa * *pb;
        ++pa;
        pb += N;
      }
      C[i * N + j] = suma;
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