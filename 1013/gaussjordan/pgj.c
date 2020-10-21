//201811137 lee woo hyun
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main()
{
        int      i, j, k;
        double   **a;
        double   *c ;
        double   *x, factor, sum;


/* Memory Allocation  */

        a = (double **)malloc(3 * sizeof( double *));
        for(i=0; i<3; i++) a[i] = (double *)malloc( 3 * sizeof( double ));
        c = (double *)malloc(3 * sizeof(double));
        x = (double *)malloc(3 * sizeof(double));

/* initialize */

	a[0][0]=1; a[0][1]=-1; a[0][2]=1;
        a[1][0]=0; a[1][1]=10; a[1][2]=25;
        a[2][0]=20; a[2][1]=10; a[2][2]=0;
        c[0]  = 0; c[1]  = 90; c[2]  = 80;
        /*
        a[0][0]=3; a[0][1]=-1; a[0][2]=2;
        a[1][0]=1; a[1][1]=2; a[1][2]=3;
        a[2][0]=2; a[2][1]=-2; a[2][2]=-1;
        c[0]  = 12; c[1]  = 11; c[2]  = 2;
	*/
	//{3, -1, 2,  1, 2, 3, 2, -2, -1};
	//{ 12, 11, 2 };
	//answer = {3, 1, 2};

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
