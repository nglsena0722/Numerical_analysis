#include <stdio.h>
#include <stdlib.h>

float* lsm(int n, float sum_x, float power_x, float sum_y, float xy) {
	float* result = (float*)malloc(2 * sizeof(float));
	float A[2][2];
	A[0][0] = n;
	A[0][1] = sum_x;
	A[1][0] = sum_x;
	A[1][1] = power_x;
	float dA = A[0][0] * A[1][1] - A[0][1] * A[1][0];

	result[0] = (1 / (dA)) * ((A[1][1] * sum_y) + ((-1)*A[0][1]*xy));
	result[1] = (1 / (dA)) * (((-1)*A[1][0] * sum_y) + (A[0][0]*xy));
	
	return result;
}

float* setcondition(int n, float* x, float* y) { // this function makes condtion such as sum_x, sum_y ...
	float* condition = (float*)malloc(5* sizeof(float));
	float sum_x = 0;	
	float power_x = 0;
	float sum_y = 0;
	float xy = 0;
	int i;

	for (i = 0; i < n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		power_x += x[i] * x[i];
		xy += x[i] * y[i];
	}

	condition[0] = n;
	condition[1] = sum_x;
	condition[2] = power_x;
	condition[3] = sum_y;
	condition[4] = xy;

	return condition;
}

float get_q(int n, float* x, float* y, float a, float b){
	float q = 0;
	float temp;
	for(int i = 0; i < n; i++) {
		temp = y[i] - (a+b*x[i]);
		q += temp * temp;
	}
	return q;
}
		

int main(){
	// this is a test in textbook
	int n = 4;
	float sum_x = 0.1;
	float power_x = 2.05;
	float sum_y = 3.907;
	float xy = 0.0517;
	float* result = lsm(n, sum_x, power_x, sum_y, xy);
	printf("this is a test in textbook\n");
	printf("y = a + bx\n");
	printf("a : %f, b : %f\n", result[0], result[1]);
	
	n = 6;
	float x[6] = {0, 0.2, 0.4, 0.6, 0.8, 1.0};
	float y[6] = {0, 0.6, 0.1, 0.4, 0.6, 0.7};
	float* condi = setcondition(n, x, y);
	result = lsm(condi[0], condi[1], condi[2], condi[3], condi[4]);
	printf("\nthis is another test not in textbook\n");
	printf("y = a + bx\n");
	printf("a : %f, b : %f\n", result[0], result[1]);
	printf("q : %f\n", get_q(n, x, y, result[0], result[1])); 
	return 0;
}
