// 201811137 lee woo hyun
// gcc -o jacobian_201811137 jacobian_201811137.c -lm
#include <math.h>
#include <stdio.h>
#define MAX 4

double a[MAX][MAX]={
    { 5.0, -4.0, 1.0, 0.0 },
    { -4.0, 6.0, -4.0, 1.0 },
    { 1.0, -4.0, 6.0, -4.0 },
    { 0.0, 1.0, -4.0, 5.0 }
};

double e_vect[MAX][MAX]={
    { 1.0, 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 0.0, 1.0 }
};

int test(double matrix[MAX][MAX]) { // if matrix's nondiagonal element is not 0, return 1 
    int i, j;
    for (i = 0; i < MAX; i++) {
	    for (j = 0; j < MAX; j++) {
		    if (i != j) {
			    if (fabs(matrix[i][j]) >= 0.000005) {
				    return 1;
			    }
		    }
	    }
    }
    return 0;
}

double tann(int i, int j) {
	double t;
	t= 2.0*a[i][j]/(fabs(a[i][i]-a[j][j]) + sqrt((a[i][i]-a[j][j])*(a[i][i]-a[j][j])+4.0*a[i][j]*a[i][j]));
	return(t);
}

void get_an( double u[MAX][MAX]) {
	double an[MAX][MAX];
	int i,j,k;
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++) an[i][j] = 0.0;
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++)
		for(k=0;k<MAX;k++)
		    an[i][j]+=u[k][i]*a[k][j];
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++) a[i][j] = an[i][j];
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++) an[i][j] = 0.0;
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++)
		for(k=0;k<MAX;k++)
		    an[i][j]+=a[i][k]*u[k][j];
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++) a[i][j] = an[i][j];
}

void get_ev(double u[MAX][MAX]) {
	int i,j,k;
	double t_vect[MAX][MAX];
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++) t_vect[i][j] = 0.0;
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++)
		for(k=0;k<MAX;k++)
		    t_vect[i][j]+=e_vect[i][k]*u[k][j];
	for(i=0;i<MAX;i++)
	    for(j=0;j<MAX;j++) e_vect[i][j] = t_vect[i][j];
}

void get_u(int i,int j, double t) {
	double c, s;
	c = 1/(sqrt(1+t*t));
	s = c * t;
	int k,l;
	double u[MAX][MAX];
	for(k=0;k<MAX;k++){
	    for(l=0;l<MAX;l++) {
		if(k == l )
		       	u[k][l] = 1.0;
		else u[k][l] = 0.0;
	    }
	}
	u[i][i] = c; u[i][j] = -s; u[j][i] = s; u[j][j] = c;
	get_an(u);
	get_ev(u);
}

int main() {
	int i = 0;
	int j = 1;
	int k, l;
	double t;
	for(k=0;k<MAX;k++){
	    for(l=0;l<MAX;l++) printf(" %12.6f", a[k][l]);
		printf("\n");
	}
	printf("\n");
	while (test(a) != 0) {
		if (i == MAX-2) {
			t = tann(i, j);
			get_u(i, j, t);
			i = 0;
			j = 1;
		}
		else if(j == MAX-1) {
			t = tann(i, j);
			get_u(i, j, t);
			i++;
			j = i+1;
		}
		else {
			t = tann(i, j);
			get_u(i, j, t);
		    	j++;
		}
	}
        for(k=0;k<MAX;k++){
            for(l=0;l<MAX;l++) printf(" %12.6f", a[k][l]);
                printf("\n");
        }  
	printf("\n");
        for(k=0;k<MAX;k++){
            for(l=0;l<MAX;l++) printf(" %12.6f", e_vect[k][l]);
                printf("\n");
        }  
}

