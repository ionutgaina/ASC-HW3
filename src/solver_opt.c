/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
#define BLOCK_SIZE 200
double *my_solver(int N, double *A, double *B) {
  // Memory allocation
  register const int size = N * N * sizeof(double);
  double *At = (double *)malloc(size);
  double *Bt = (double *)malloc(size);
  double *AtB = (double *)malloc(size);
  double *BA = (double *)malloc(size);
  double *sum = (double *)malloc(size);
  double *C = (double *)malloc(size);

  register unsigned int i, j, k, bi, bj;

  // Transpose B
  for (i = 0; i < N; ++i) {
    register double *pi = &B[i * N];
    register double *pj = &Bt[i];
    for (j = 0; j < N; ++j) {
      *pj = *pi;
      ++pi;
      pj += N;
    }
  }

  //   Transpose A
  for (i = 0; i < N; ++i) {
    register double *pi = &At[i * N];
    register double *pj = &A[i];
    for (j = 0; j <= i; ++j) {
      *pi = *pj;
      pj += N;
      ++pi;
    }
    for (j = i + 1; j < N; ++j) {
      *pi = 0;
      ++pi;
    }
  }

  // At * B = AtB
  for (bi = 0; bi < N; bi += BLOCK_SIZE) {
    for (bj = 0; bj < N; bj += BLOCK_SIZE) {
      for (i = bi; i < N && i < bi + BLOCK_SIZE; ++i) {
        register double *orig_pa = &At[i * N];

        for (j = bj; j < N && j < bj + BLOCK_SIZE; ++j) {
          register double *pa = orig_pa;
          register double *pb = &B[j];

          register double suma = 0;
          for (k = 0; k <= i; ++k) {
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
  for (bi = 0; bi < N; bi += BLOCK_SIZE) {
    for (bj = 0; bj < N; bj += BLOCK_SIZE) {
      for (i = bi; i < N && i < bi + BLOCK_SIZE; ++i) {
        register double *orig_pb = &B[i * N];
        for (j = bj; j < N && j < bj + BLOCK_SIZE; ++j) {
          register double *pb = orig_pb;
          register double *pa = &A[j];

          register double suma = 0;
          for (k = 0; k <= j; ++k) {
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
  for (bi = 0; bi < N; bi += BLOCK_SIZE) {
    for (bj = 0; bj < N; bj += BLOCK_SIZE) {
      for (i = bi; i < bi + BLOCK_SIZE && i < N; ++i) {
        register double *psum = &sum[i * N + bj];
        register double *patb = &AtB[i * N + bj];
        register double *pa = &BA[i * N + bj];

        for (j = bj; j < bj + BLOCK_SIZE && j < N; ++j) {
          *psum = *patb + *pa;
          ++patb;
          ++pa;
          ++psum;
        }
      }
    }
  }

  // sum * Bt = C
  for (bi = 0; bi < N; bi += BLOCK_SIZE) {
    for (bj = 0; bj < N; bj += BLOCK_SIZE) {
      for (i = bi; i < N && i < bi + BLOCK_SIZE; ++i) {
        register double *orig_sum = &sum[i * N];
        for (j = bj; j < N && j < bj + BLOCK_SIZE; ++j) {
          register double *pa = orig_sum;
          register double *pb = &Bt[j];
          register double suma = 0;
          for (k = 0; k < N; ++k) {
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