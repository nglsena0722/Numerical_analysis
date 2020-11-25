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

float euler_method(float a, float b, float x, float x0, float y0, float h){
	int n = (x-x0)/h;
	int i;
	float ya;
	float yb = y0;
	float xb = x0;
	for (i = 0; i < n; i++){
		ya = yb+h*(a*yb+b*xb);
		yb = ya;
		xb += h;
	}
	return ya;
}

float heun(float a, float b, float x, float x0, float y0, float h){
	int n = (x-x0)/h;
	int i;
	float ya;
	float yb = y0;
	float xb = x0;
	for (i = 0; i < n; i++){
		ya = yb+(h/2)*(a*yb+b*xb+a*(yb+h*a*yb));
		yb = ya;
		xb += h;
	}
	return ya;
}

float midpoint(float a, float b, float x, float x0, float y0, float h){
	int n = (x-x0)/h;
	int i;
	float ya;
	float yb = y0;
	float xb = x0;
	float k1;
	float k2;
	for (i = 0; i < n; i++){
		k1 = a*yb+b*xb;
		k2 = a*(yb+k1*h/2)+b*(xb+h/2); 
		ya = yb+k2*h;
		yb = ya;
		xb += h;
	}
	return ya;
}

float ralston(float a, float b, float x, float x0, float y0, float h){
	int n = (x-x0)/h;
	int i;
	float ya;
	float yb = y0;
	float xb = x0;
	float k1;
	float k2;
	for (i = 0; i < n; i++){
		k1 = a*yb+b*xb;
		k2 = a*(yb+k1*h*((float)3/4))+b*(xb+((float)3/4)*h); 
		ya = yb+h*(k1/3+2*k2/3);
		yb = ya;
		xb += h;
	}
	return ya;
}

int main() {
        int n = 5; // function's order is n-1.
        float function[5] = {-0.1, -0.15, -0.5, -0.25, 1.25};
//	int n = 3;
//	float function[3] = {2, 0, 0};
	float a = 2;
	float b = 0;

	float x = 0.1;
	float x0 = 0;
	float y0 = 1;
	float h = 0.05;

	int i;
	printf("Setting : "); 
    	printf("x = %f, h = %f, x0 = %f, y0 = %f, y' = %.2fy + %.2fx\n", x, h, x0, y0, a,b);
	printf("--- the result of Euler Method---\n");
	printf("when x = %.2f, y = %f\n", x, euler_method(a, b, x, x0, y0, h));
	printf("--- the result of HEUN---\n");
	printf("when x = %.2f, y = %f\n", x, heun(a, b, x, x0, y0, h));
	printf("--- the result of Runge-Kutta, Mid point Method---\n");
	printf("when x = %.2f, y = %f\n", x, midpoint(a, b, x, x0, y0, h));
	printf("--- the result of Runge-Kutta, Ralston Method---\n");
	printf("when x = %.2f, y = %f\n", x, ralston(a, b, x, x0, y0, h));
        return 0;
}    


