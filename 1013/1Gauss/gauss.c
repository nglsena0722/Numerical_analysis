#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main()
{
        int      i, j, k;
        double   a[3][3]= { 1, -1,1, 0, 10, 25 , 20, 10, 0 };
        double   c[3]   = { 0, 90, 80 };
        double   x[3], factor, sum;

/* Forward Reduction */

        for( k=0; k < 3-1;k++){
                for(i= k+1; i < 3; i++ ){
                        factor = a[i][k] / a[k][k];
                        for(j=k+1; j<3; j++) a[i][j] -= factor * a[k][j];
                        c[i] -= factor * c[k];
                }
        }

/* back substitution */

        x[2] = c[2] / a[2][2];
        for( i= 3-2; i>=0; i--){
                sum = 0;
                for(j=i+1; j<3; j++ )   sum += a[i][j] * x[j];
                x[i] = ( c[i] - sum )/ a[i][i];
        }

/* print results */

        for(i=0; i<3; i++) printf("x[%1d] = %10.4f, ", i, x[i]);
        printf("\n");
}	
