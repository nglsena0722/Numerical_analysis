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

float  trapezoidal(int n, float* function, float x0, float x1) { // n is the number of data.
        float h = x1-x0;
	float result = (h/2)*(operation(n,function,x0)+operation(n, function, x1));
	return result;
}

float simpson(int n, float* function, float x0, float x1){
	float h = (x1-x0)/2;
	float result = (h/3)*(operation(n,function,x0)+4*operation(n, function, (x1+x0)/2) +operation(n, function, 1));
	return result;
}

float twopoint_gaussintegration(int n, float* function, float x0, float x1){
	float jacobian = (x1-x0)/2;
	float t[2] = {(x1+x0)/2, jacobian};
	float result = jacobian*( operation(n, function, t[1]*((-1)*sqrt((float)1/3))+t[0])+operation(n, function, t[1]*(sqrt((float)1/3))+t[0]));
	return result;
}

float threepoint_gaussintegration(int n, float* function, float x0, float x1){
	float jacobian = (x1-x0)/2;
	float t[2] = {(x1+x0)/2, jacobian};
	float r[3];
	float nu = t[1]*((-1)*sqrt((float)3/5))+t[0];
	r[0] = ((float)5/9)* operation(n, function, t[1]*((-1)*sqrt((float)3/5))+t[0]);
	r[1] = ((float)8/9)* operation(n, function, t[0]);
	r[2] = ((float)5/9)* operation(n, function, t[1]*(sqrt((float)3/5))+t[0]);
	float result = jacobian* (r[0]+r[1]+r[2]);
	return result;
}

int main() {
        int n = 5; // function's order is n-1.
        float function[5] = {-0.1, -0.15, -0.5, -0.25, 1.25};
//	int n = 3;
//	float function[3] = {2, 0, 0};
	float x0 = 0;
	float x1 = 1;

	int i;
	printf("function = "); 
	for (i = 0; i < n; i++) {
		printf("%.2f ", function[i]);
	}
	printf("\n");
	printf("--- the result of trapezoidal rule---\n");
	printf("I*f(x) : %f\n", trapezoidal(n, function, x0, x1));
	printf("--- the result of simpson rule---\n");
	printf("I*f(x) : %f\n", simpson(n, function, x0, x1));
	printf("--- the result of twopoint_gaussintegration---\n");
	printf("I : %f\n", twopoint_gaussintegration(n, function, x0, x1));
	printf("--- the result of threepoint_gaussintegration---\n");
	printf("I : %f\n", threepoint_gaussintegration(n, function, x0, x1));
        return 0;
}    








