/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
#define BLOCK_SIZE 40
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
    double *pi = &B[i * N];
    double *pj = &Bt[i];
    for (int j = 0; j < N; j++) {
      *pj = *pi;
      ++pi;
      pj += N;
    }
  }

  //   Transpose A
  for (int i = 0; i < N; i++) {
    double *pi = &At[i * N];
    double *pj = &A[i];
    for (int j = 0; j <= i; j++) {
      *pi = *pj;
      pj += N;
      ++pi;
    }
  }

  // At * B = AtB
  for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
    for (int bj = 0; bj < N; bj += BLOCK_SIZE) {
      for (int i = bi; i < N && i < bi + BLOCK_SIZE; i++) {
        double *orig_pa = &At[i * N];

        for (int j = bj; j < N && j < bj + BLOCK_SIZE; j++) {
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
    }
  }

  // B * A = BA
  for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
    for (int bj = 0; bj < N; bj += BLOCK_SIZE) {
      for (int i = bi; i < N && i < bi + BLOCK_SIZE; i++) {
        double *orig_pb = &B[i * N];
        for (int j = bj; j < N && j < bj + BLOCK_SIZE; j++) {
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
    }
  }

  // AtB + BA = sum
  for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
    for (int bj = 0; bj < N; bj += BLOCK_SIZE) {
      for (int i = bi; i < bi + BLOCK_SIZE && i < N; i++) {
        double *psum = &sum[i * N + bj];
        double *patb = &AtB[i * N + bj];
        double *pa = &BA[i * N + bj];

        for (int j = bj; j < bj + BLOCK_SIZE && j < N; j++) {
          *psum = *patb + *pa;
          ++patb;
          ++pa;
          ++psum;
        }
      }
    }
  }

  // sum * Bt = C
  for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
    for (int bj = 0; bj < N; bj += BLOCK_SIZE) {
      for (int i = bi; i < N && i < bi + BLOCK_SIZE; i++) {
        double *orig_sum = &sum[i * N];
        for (int j = bj; j < N && j < bj + BLOCK_SIZE; j++) {
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