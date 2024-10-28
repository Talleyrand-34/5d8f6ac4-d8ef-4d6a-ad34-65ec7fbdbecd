#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10000
#define ALIGNMENT 64

// Función para medir el tiempo (reemplaza a polybench_start_instruments)
#include <time.h>
double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    float *a, *x, *y;
    posix_memalign((void**)&a, ALIGNMENT, sizeof(float)*N*N);
    posix_memalign((void**)&x, ALIGNMENT, sizeof(float)*N);
    posix_memalign((void**)&y, ALIGNMENT, sizeof(float)*N);

    // Inicialización de matrices
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i*N+j] = j;
        }
        x[i] = i;
        y[i] = 0;
    }

    double start_time = get_time();

    // Multiplicación matriz-vector optimizada con AVX-512
    for (int t = 0; t < 100; ++t) {
        for (int i = 0; i < N; i += 16) {
            __m512 sum1 = _mm512_setzero_ps();
            __m512 sum2 = _mm512_setzero_ps();

            for (int j = 0; j < N; j++) {
                __m512 x_vec = _mm512_set1_ps(x[j]);
                __m512 a_vec1 = _mm512_load_ps(&a[i*N + j]);
                __m512 a_vec2 = _mm512_load_ps(&a[(i+8)*N + j]);
                
                sum1 = _mm512_fmadd_ps(a_vec1, x_vec, sum1);
                sum2 = _mm512_fmadd_ps(a_vec2, x_vec, sum2);
            }

            _mm512_store_ps(&y[i], sum1);
            _mm512_store_ps(&y[i+8], sum2);
        }
    }

    double end_time = get_time();
    double elapsed_time = end_time - start_time;

    printf("Tiempo de ejecución: %f segundos\n", elapsed_time);
    printf("y[40] = %f\n", y[40]);

    // Liberar memoria
    free(a);
    free(x);
    free(y);

    return 0;
}

