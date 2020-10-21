// 201811137 lee woo hyun 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main()
{
        int      i, j, k;
        double   a[3][3]= { 1, -1,1, 0, 10, 25 , 20, 10, 0 };//{3, -1, 2,  1, 2, 3, 2, -2, -1};
        double   c[3]   = { 0, 90, 80 };//{ 12, 11, 2 };
        double   x[3], factor, sum;//answer = {3, 1, 2};

/* make lower triangular matrix to 0 and a[k][k] = 1 */
        for( k=0; k < 3;k++){
		factor = a[k][k];
		for(j=k; j<3; j++) {
			a[k][j] /= factor; // make a[k][k] = 1
		}
		c[k] /= factor;
                for(i= k+1; i < 3; i++ ){
			factor = a[i][k];
                        for(j=0; j<3; j++) a[i][j] -= factor * a[k][j];
                        c[i] -= factor * c[k];
                }
		
        }

/* make upper triangular matrix to 0 */
	x[2] = c[2];
        for( i= 3-2; i>=0; i--){
                sum = 0;
                for(j=i+1; j<3; j++ )   sum += a[i][j] * x[j];
                x[i] = ( c[i] - sum );
        }

/* print results */

        for(i=0; i<3; i++) printf("x[%1d] = %10.4f, ", i, x[i]);
        printf("\n");
}
/*
	for(i = 0; i < 3; i++) {
	        for(j =0; j < 3; j++) {
		     printf("%f ", a[i][j]);
	       
	        }
		printf("%f ", c[i]);
	    	printf("\n");		    
	}
*/
/*
// make a[0][0] = 1
	for (i = 0; i < 3; i++) {
		a[0][i] /= a[0][0];
	}
	c[0] /= a[0][0];

// erase a[1][0], a[2][0]
	for (j = 1; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			a[j][i] -= a[j][0] * a[0][i];
		}
		c[j] -= a[j][0] * c[0];
	}

// make a[1][1]
*/

/*
	
        for( k=0; k < 3-1;k++){
                for(i= k+1; i < 3; i++ ){
                        factor = a[i][k] / a[k][k];
                        for(j=k+1; j<3; j++) a[i][j] -= factor * a[k][j];
                        c[i] -= factor * c[k];
                }
        }


        x[2] = c[2] / a[2][2];
        for( i= 3-2; i>=0; i--){
                sum = 0;
                for(j=i+1; j<3; j++ )   sum += a[i][j] * x[j];
                x[i] = ( c[i] - sum )/ a[i][i];
        }
*/
/* print results */

        //for(i=0; i<3; i++) printf("x[%1d] = %10.4f, ", i, x[i]);
        //printf("\n");
	
