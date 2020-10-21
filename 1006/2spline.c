#include <stdio.h>
#include <stdlib.h>

float** spline(int n, float* x, float* y, float z0) { // n is the number of data.
	float** result = (float**)malloc(2 * sizeof(float*));
	float* a = (float*)malloc((n-1) * sizeof(float));
	float* z = (float*)malloc((n) * sizeof(float));
	z[0] = z0;
	result[0] = a;
	result[1] = z;

	int i; 

	for (i=0; i < (n-1); i++) {
		z[i+1] = (2*(y[i+1]-y[i])/(x[i+1]-x[i])) - z[i];
	}

	for (i=0; i < (n-1); i++){
		a[i] = (z[i+1]-z[i]) / (2 * (x[i+1]-x[i]));
	}

	return result;

}

int main() {
	int n = 6;
	float z0 = 0.5;
	float x[6] = {0, 0.2, 0.4, 0.6, 0.8, 1.0};
	float y[6] = {0, 0.6, 0.1, 0.4, 0.6, 0.7};

	float** result = spline(n, x, y, z0);
	
	printf("S_i function = a_i(x-x_i)^2 + z_i(x-x_i) + y_i\n");
	for( int i =0; i < n-1; i++) {
		printf("i : %d, a : %f, z : %f, x : %f, y : %f\n", i, result[0][i], result[1][i], x[i], y[i]);
	}
	return 0;
}	
