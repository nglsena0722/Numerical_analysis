#include <stdio.h>
#include <stdlib.h>

float** spline(int n, float* x, float* y) { // n is the number of data.
	float** result = (float**)malloc(2 * sizeof(float*));
	float* a = (float*)malloc((n-1) * sizeof(float));
	float* b = (float*)malloc((n-1) * sizeof(float));
	result[0] = a;
	result[1] = b;

	for (int i=0; i < n-1; i++) {
		a[i] = (y[i+1]-y[i]) /(x[i+1]-x[i]);
		b[i] = y[i]-a[i]*x[i];
	}

	return result;

}

int main() {
	int n = 6;
	float x[6] = {0, 0.2, 0.4, 0.6, 0.8, 1.0};
	float y[6] = {0, 0.6, 0.1, 0.4, 0.6, 0.7};

	float** result = spline(n, x, y);
	for( int i =0; i < n-1; i++) {
		printf("i : %d, a : %f, b: %f\n", i, result[0][i], result[1][i]);
	}
	return 0;
}	



