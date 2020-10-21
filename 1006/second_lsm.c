#include <stdio.h>
#include <stdlib.h>

float* lsm(int n, float sum_x, float xx, float sum_y, float xy, float xxx, float xxxx, float xxy) {
	float* result = (float*)malloc(3 * sizeof(float));
	float a = n;
	float b = sum_x;
	float c = xx;
	float d = sum_x;
	float e = xx;
	float f = xxx;
	float g = xx;
	float h = xxx;
	float i = xxxx;
	
	float A[3][3];
	A[0][0] = n;
	A[0][1] = sum_x;
	A[0][2] = xx;
	A[1][0] = sum_x;
	A[1][1] = xx;
	A[1][2] = xxx;
	A[2][0] = xx;
	A[2][1] = xxx;
	A[2][2] = xxxx;
	
	float dA = (A[0][0] * A[1][1] * A[2][2] + A[0][1] * A[1][2] * A[2][0] + A[0][2] * A[1][0] * A[2][1] - A[0][2] * A[1][1] * A[2][0] - A[0][0] * A[1][2] * A[2][1] - A[0][1] * A[1][0] * A[2][2] );
	result[0] = (1 / (dA)) * (((e*i-f*h)* sum_y) + ((c*h-b*i)*xy) + ((b*f-c*e) *xxy));
	result[1] = (1 / (dA)) * (((f*g-d*i)* sum_y) + ((a*i-c*g)*xy) + ((c*d-a*f) *xxy));
	result[2] = (1 / (dA)) * (((d*h-e*g)* sum_y) + ((b*g-a*h)*xy) + ((a*e-b*d) *xxy));
	return result;
}

float* setcondition(int n, float* x, float* y) { // this function makes condtion such as sum_x, sum_y ...
	float* condition = (float*)malloc(8* sizeof(float));
	float sum_x = 0;	
	float power_x = 0;
	float sum_y = 0;
	float xy = 0;
	float xxx = 0;
	float xxxx = 0;
	float xxy = 0;
	int i;

	for (i = 0; i < n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		power_x += x[i] * x[i];
		xy += x[i] * y[i];
		xxx += x[i] * x[i] * x[i];
		xxxx += x[i] * x[i] * x[i] * x[i];
		xxy += x[i] * x[i] * y[i];	    
	}

	condition[0] = n;
	condition[1] = sum_x;
	condition[2] = power_x;
	condition[3] = sum_y;
	condition[4] = xy;
	condition[5] = xxx;
	condition[6] = xxxx;
	condition[7] = xxy;


	return condition;
}

float get_q(int n, float* x, float* y, float a, float b, float c){
	float q = 0;
	float temp;
	for(int i = 0; i < n; i++) {
		temp = y[i] - (a+b*x[i]+c*x[i]*x[i]);
		q += temp * temp;
	}
	return q;
}
		

int main(){	
	int n = 6;
	float x[6] = {0, 0.2, 0.4, 0.6, 0.8, 1.0};
	float y[6] = {0, 0.6, 0.1, 0.4, 0.6, 0.7};
	float* condi = setcondition(n, x, y);
	float* result = lsm(condi[0], condi[1], condi[2], condi[3], condi[4], condi[5], condi[6], condi[7]);
	printf("y = a + bx + cx^2\n");
	printf("a : %f, b : %f, c : %f\n", result[0], result[1], result[2]);
	printf("q : %f\n", get_q(n, x, y, result[0], result[1], result[2])); 
	return 0;
}


