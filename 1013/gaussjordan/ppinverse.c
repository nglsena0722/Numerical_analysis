// 201811137 lee woo hyun 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main()
{
        int n; // we handle n x n matrix
	n = 3;
	int i, j, k;
        double *a;
	double *x;
	double *sum;
	double *tem;
	double factor;

        a = (double *)malloc(n * n * sizeof( double));
        x = (double *)malloc(n * n * sizeof(double));
        sum = (double *)malloc(n * sizeof(double));
	
        tem = a;
        *tem++ =2;  *tem++ =0;  *tem++ =1;
        *tem++ =-2; *tem++ =3;  *tem++ =4;
        *tem++ =-5; *tem++ =5;  *tem++ =6;

        tem = x;
        *tem++ =1;  *tem++ =0; *tem++ =0;
        *tem++ =0;  *tem++ =1; *tem++ =0;
        *tem++ =0;  *tem++ =0; *tem++ =1;

/* make lower triangular matrix to 0 and a[k][k] = 1 */
        for( k=0; k < n;k++){
		factor = *(a + n*k +k);
		for(j=k; j<n; j++) {
			*(a + n*k +j) /= factor; // make a[k][k] = 1
		}
		for(j = 0; j < n; j++){
			*(x + n*k +j) /= factor;
		}
                for(i= k+1; i < n; i++ ){
			factor = *(a + n*i +k);
                        for(j=0; j<n; j++){	
				*(a + n*i +j) -= factor * (*(a + n*k +j));
				*(x + n*i +j) -= factor * (*(x + n*k +j));
			}   
		}
        }

/* make upper triangular matrix to 0 */
        for( i= n-2; i>=0; i--){
                for(k=0; k<n; k++ ) {
			*(sum + k) = 0;
		}
                for(j=i+1; j<n; j++ ) {
			for(k=0; k<n; k++ ) {
				*(sum+k) += (*(a + n*i +j)) * (*(x + n*j +k));
			}
		}
                for(k=0; k<n; k++ ) {
			*(x + n*i +k) -= *(sum+k);
		}
        }

/* print inverse matrix */

	for(i = 0; i < n; i++) {
	        for(j =0; j < n; j++) {
		     printf("%f ", *(x + n*i +j));
	        }
	    	printf("\n");		    
	}
}
