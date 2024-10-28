#include <immintrin.h>
#include <stdio.h>
#define N 10000
#define NN 1000

int main() {
	float * a, * x, *y; 
	posix_memalign( (void*)&a, 32, sizeof(float)*N*N);
	posix_memalign( (void*)&x, 32, sizeof(float)*N);
	posix_memalign( (void*)&y, 32, sizeof(float)*N);

	for( int i = 0; i < N; ++i ) {
		for( int j = 0; j < N; ++j ) {
			a[i*N+j] = j;
		}
		x[i] = i;
		y[i] = 0;
	}
	
	polybench_start_instruments();
	for( int t = 0; t < 100; ++t ) {
	/* for( int t = 0; t < 100; ++t ) { */
		for( int i = 0; i < N; ++i ) {
		/* for( int i = 0; i < N; ++i ) { */
			y[i] = 0;
			for( int j = 0; j < N; ++j ) {
			/* for( int j = 0; j < N; j+=4 ) { */
			/* for( int j = 0; j < N; ++j ) { */
				y[i] += a[i*N+j] * x[j];
				/* y[i] += a[i*N+j] * x[j]; */
				/* y[i] += a[i*N+j] * x[j]; */
				/* y[i] += a[i*N+j] * x[j]; */
			}
		}
	}
	polybench_start_instruments();
	polybench_start_instruments();

	printf( "y[40] = %f\n", y[40] );
}
// original
/* int main() { */
/* 	float * a, * x, *y;  */
/* 	posix_memalign( (void*)&a, 32, sizeof(float)*N*N); */
/* 	posix_memalign( (void*)&x, 32, sizeof(float)*N); */
/* 	posix_memalign( (void*)&y, 32, sizeof(float)*N); */
/**/
/* 	for( int i = 0; i < N; ++i ) { */
/* 		for( int j = 0; j < N; ++j ) { */
/* 			a[i*N+j] = j; */
/* 		} */
/* 		x[i] = i; */
/* 		y[i] = 0; */
/* 	} */
/**/
/* 	for( int t = 0; t < 100; ++t )  */
/* 	for( int i = 0; i < N; ++i ) { */
/* 		y[i] = 0; */
/* 		for( int j = 0; j < N; ++j ) { */
/* 			y[i] += a[i*N+j] * x[j]; */
/* 		} */
/* 	} */
/**/
/* 	printf( "y[40] = %f\n", y[40] ); */
/* } */
