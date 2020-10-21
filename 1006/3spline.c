#include <stdio.h>
#include <stdlib.h>

float** spline(int n, float* x, float* y, float w1, float w0) { // n is the number of data.
	float** result = (float**)malloc(3 * sizeof(float*));
	float* a = (float*)malloc((n-1) * sizeof(float));
	float* w = (float*)malloc((n) * sizeof(float));
	float* z = (float*)malloc((n) * sizeof(float));
	w[1] = w1;
	w[0] = w0;
	result[0] = a;
	result[1] = w;
	result[2] = z;

	int i; 
	float x1;
	float x2;

	for (i=0; i < (n-2); i++) { 
		x1 = x[i+1] - x[i];
		x2 = x[i+2] - x[i+1];
		w[i+2] = (6*(y[i+2]-y[i+1]) / (x2)) -(4*w[i+1]) - ((3*w[i+1]) / (x2)) - ((6*w[i]*(x1)) / (x2));
	}

	for (i=0; i < (n-1); i++){
		a[i] = (w[i+1]-(2*w[i])) / (6 * (x[i+1]-x[i]));
	}

	for (i=0; i < (n-1); i++){
		x1 = x[i+1] - x[i];
		z[i] = ((y[i+1]-y[i])-(a[i]*(x1)*(x1)*(x1)+w[i]*(x1)*(x1)) / (x1));
	}
	return result;
}

int main() {
	int n = 6;
	float w1 = 0.5;
	float w0 = 0.5;
	float x[6] = {0, 0.2, 0.4, 0.6, 0.8, 1.0};
	float y[6] = {0, 0.6, 0.1, 0.4, 0.6, 0.7};
	int i;

	float** result = spline(n, x, y, w1, w0);
	printf("S_i function = a_i(x-x_i)^3 + w_i(x-x_i)^2 + z_i(x-x_i) + y_i\n");
	for(i =0; i < n-2; i++) {
		printf("i : %d, a : %f, w : %f, z : %f, x : %f, y : %f\n", i, result[0][i], result[1][i], result[2][i],  x[i], y[i]);
	}


	return 0;
}	
