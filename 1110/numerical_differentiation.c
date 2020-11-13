// 201811137 lee woo hyun
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

float* secondExpansion(int n, float* function, float x, float h) { // n is the number of data.
        float* result = (float*)malloc(3 * sizeof(float));
	float fFF = operation(n, function, x+2*h); // x_i+2
	float fF = operation(n, function, x+h); // x_i+1
	float fC = operation(n, function, x); // x_i
	float fB = operation(n, function, x-h); // x_i-1
	float fBB = operation(n, function, x-2*h); // x_i-2
	
	//printf("fF : %f, fC : %f, fB : %f\n", fF, fC, fB);
	result[0] = ((-1)*fFF + 4*fF - 3*fC)/(2 * h); // Forward Expansion
	result[1] = (3*fC - 4*fB + fBB)/(2 * h); // Backward Expansion
	result[2] = ((-1)*fFF + 8*fF - 8*fB + fBB)/(12 *h); // Central Expansion

        return result;
}

int main() {
        int n = 5; // function's order is n-1.
        float function[5] = {-0.1, -0.15, -0.5, -0.25, 1.25};
	float x = 0.5;
	float h = 0.25;

        float* result1 = firstExpansion(n, function, x, h); 
        float* result2 = secondExpansion(n, function, x, h); 
        float root = differential(n, function, x);

	int i;
	printf("function = "); 
	for (i = 0; i < n; i++) {
		printf("%.2f ", function[i]);
	}
	printf("\n");
	printf("x = %f\n", x);
	printf("h = %f\n", h);
        printf("f'(x) : %f\n", root);
	printf("----O(h)----\n"); 
	printf("Forward Expansion : %f, Error : %.2f%% \n", result1[0], 100 * fabs((root-result1[0]) / root));
        printf("Backward Expansion : %f, Error : %.2f%%\n", result1[1], 100 * fabs((root-result1[1]) / root));
        printf("Central Expansion : %f, Error : %.2f%%\n", result1[2], 100 * fabs((root-result1[2]) / root));
	printf("----O(h^2)----\n"); 
	printf("Forward Expansion : %f, Error : %.2f%% \n", result2[0], 100 * fabs((root-result2[0]) / root));
        printf("Backward Expansion : %f, Error : %.2f%%\n", result2[1], 100 * fabs((root-result2[1]) / root));
        printf("Central Expansion : %f, Error : %.2f%%\n", result2[2], 100 * fabs((root-result2[2]) / root));
        return 0;
}    


