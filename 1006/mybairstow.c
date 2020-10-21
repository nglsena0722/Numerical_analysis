#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Max_loop 1000
#define epsilon 0.001 // error range

void // this function is from the file 'bairstow.c'
quad(float *x, float *coeff) 
{
    float    a, b, c, d;
    a = coeff[2]; b = coeff[1]; c = coeff[0];
    d = b*b - 4*a * c;
    if(  d >0 ) {
        x[2]= (b + sqrt(d))/(2.0*a); x[1]= (b - sqrt(d))/(2.0*a);
    }
    else if( d == 0 ) x[2]= x[1]= b/(2 * a);
    else {
        x[2]= (b + sqrt(-d))/(2.0*a); x[1]= (b - sqrt(-d))/(2.0*a);
    }
}

float* bairstow(int n, float* function, float r, float s){
	float* root = (float*)calloc(n, sizeof(float));
	float delta_r;
	float delta_s;
	int loop_num = 0;
	int i;
	int temp;
	float b[n];
	float c[n];
	float d;
	//float quotient[n]; // (x^2 - rx -s) * quotient = function

	do {
		if (loop_num++ > Max_loop) {
			printf("It doesn't converg!\n");
			exit(0);
		}
		b[n-1] = function[n-1];
		b[n-2] = function[n-2] + r * b[n-1]; 
		for (i = n-3; i >= 0; i--) {
			b[i] = function[i] + r * b[i + 1] + s * b[i + 2]; 
		}

		c[n-1] = b[n-1];
		c[n-2] = b[n-2] + r * c[n-1];
		for (i = n-3; i >= 1; i--) {
			c[i] = function[i] + r * c[i + 1] + s * c[i + 2];
		}

//		delta_r = (b[0]*c[1] - b[1]*c[2]) / (c[0]*c[2] - c[1]*c[1]);
//		delta_s = (b[1]*c[1] - b[0]*c[0]) / (c[0]*c[2] - c[1]*c[1]);
		delta_s = (-c[1]*b[1] + c[2]*b[0])/(c[1]*c[3] - c[2]*c[2]);
		delta_r = (-c[3] * delta_s -b[1])/c[2];

		r += delta_r;
		s += delta_s;

		if (fabs(delta_r/r) <= epsilon && fabs(delta_s/s) <= epsilon) { // we need to save root
			printf("r : %f, s : %f\n", r, s);
			if ((d = r*r + 4*s) > 0) {
				root[n-1] = 0.5 * (r + sqrt(d));
				root[n-2] = 0.5 * (r - sqrt(d));
			}
			else if (d == 0) {	
				root[n-1] = 0.5 * r;
				root[n-2] = root[n-1];
			}
			else {
				root[n-1] = 0.5 * r;
				root[n-2] = 0.5 * sqrt(-d);
			}
			n -= 2;
			for (i = 0; i < n; i++) {
				function[i] = b[i+2];
			}
		}
	} while (n > 3);
	if (n == 3) {
		quad(root, function);	
	}
	else {
		root[n-1] = -s / r;
	}
	return root;
}

int main() {
	int n = 6;
	// maybe change the position of coefficient
	float function[6] = {1.25, -3.875, 2.125, 2.75, -3.5, 1.0}; // it means 1.25x^5 -3.875x^4 +2.125x^3 + 2.75x^2 -3.5x + 1.0 = 0.0 
	float r = -1.0;
	float s = -1.0;
	float* root = bairstow(n, function, r, s);

	for(int i=1; i< 6; i++) 
	{
		printf("x[%1d] = %7.3f, ",i,root[i]);
	        printf("\n");
	}	
	return 0;
}
