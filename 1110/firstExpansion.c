#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float operation(int n, float* function, float x) {
	int i, j;
	float f = 0;
	float temp;
	for (i = 0; i < n; i++) {
		temp = function[i];
		for (j = 0; j < n-1-i; j++) {
			temp *= x;
		}
		f += temp;
	}
	return f;
}	

float differential(int n, float* function, float x) {
	int i, j;
	float f = 0;
	float temp;
	for (i = 0; i < n-1; i++) {
		temp = function[i] * (n-1-i);
		for (j = 0; j < n-2-i; j++) {
			temp *= x;
		}
		f += temp;
	}
	return f;
}	

float* firstExpansion(int n, float* function, float x, float h) { // n is the number of data.
        float* result = (float*)malloc(3 * sizeof(float));
	float fF = operation(n, function, x+h); // x_i+1
	float fC = operation(n, function, x); // x_i
	float fB = operation(n, function, x-h); // x_i-1
	
	//printf("fF : %f, fC : %f, fB : %f\n", fF, fC, fB);
	result[0] = (fF - fC)/h; // Forward Expansion
	result[1] = (fC - fB)/h; // Backward Expansion
	result[2] = (fF - fB)/(2 *h); // Central Expansion

        return result;
}

int main() {
        int n = 5;
        float function[5] = {-0.1, -0.15, -0.5, -0.25, 1.25};
	float x = 0.5;
	float h = 0.25;

        float* result = firstExpansion(n, function, x, h); 
        float root = differential(n, function, x);

	int i = 0;
        printf("root : %f\n", root);
	printf("Forward Expansion : %f, Error : %f%% \n", result[0], 100 * fabs((root-result[0]) / root));
        printf("Backward Expansion : %f, Error : %f%%\n", result[1], 100 * fabs((root-result[1]) / root));
        printf("Central Expansion : %f, Error : %f%%\n", result[2], 100 * fabs((root-result[2]) / root));
        return 0;
}    


