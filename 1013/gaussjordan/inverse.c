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
 
	double   a[3][3]= {2, 0, 1, -2, 3, 4, -5, 5, 6};//{2, -1, 0, 1, 0, -1, 1, 0, 1};//{3, -1, 2,  1, 2, 3, 2, -2, -1};
        double   x[3][3] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        double	 factor, sum[3]; 

/* make lower triangular matrix to 0 and a[k][k] = 1 */
        for( k=0; k < 3;k++){
		factor = a[k][k];
		for(j=k; j<3; j++) {
			a[k][j] /= factor; // make a[k][k] = 1
		}
		for(j = 0; j < 3; j++){
			x[k][j] /= factor;
		}
                for(i= k+1; i < 3; i++ ){
			factor = a[i][k];
                        for(j=0; j<3; j++){
			       	a[i][j] -= factor * a[k][j];
				x[i][j] -= factor * x[k][j];
			}   
		}
        }

/* make upper triangular matrix to 0 */
        for( i= 3-2; i>=0; i--){
                for(k=0; k<3; k++ ) {
			sum[k] = 0;
		}
                for(j=i+1; j<3; j++ ) {
			for(k=0; k<3; k++ ) {
				sum[k] += a[i][j] * x[j][k];
			}
		}
                for(k=0; k<3; k++ ) {
			x[i][k] = (x[i][k] - sum[k]);
		}
        }

/* print inverse matrix */

	for(i = 0; i < 3; i++) {
	        for(j =0; j < 3; j++) {
		     printf("%f ", x[i][j]);
	       
	        }
	    	printf("\n");		    
	}
}
