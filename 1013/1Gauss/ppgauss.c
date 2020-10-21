#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main()
{
        int      i, j, k;
        double   *a;
        double   *c ;
        double   *x, factor, sum;
        double   *tem;               /* temporary adress variable */


/* Memory Allocation  */

        a = (double *)malloc(3 * 3 * sizeof( double));
        c = (double *)malloc(3 * sizeof(double));
        x = (double *)malloc(3 * sizeof(double));

/* initialize */

        tem = a;
        *tem++ =1;  *tem++ =-1; *tem++ =1;
        *tem++ =0;  *tem++ =10; *tem++ =25;
        *tem++ =20; *tem++ =10; *tem++ =0;

        tem = c;
        *tem++ = 0; *tem++ = 90; *tem++ = 80;

/* Forward Reduction */

        for( k=0; k < 3-1;k++){
                for(i= k+1; i < 3; i++ ){
                        factor = *(a + 3*i +k) / *(a + 3*k +k );
                        for(j=k+1; j<3; j++) *(a + 3*i +j) -= factor * *(a + 3*k +j);
                        *(c+i) -= factor * *(c+k);
                }
        }

/* back substitution */

        *(x+2) = *(c+2)/ *(a + 2*3 + 2);
        for( i= 3-2; i>=0; i--){
                sum = 0;
                for(j=i+1; j<3; j++ )   sum += *(a + i*3 +j ) * *(x+j);
                *(x+i) = ( *(c+i) - sum )/ *(a + i*3 + i);
        }

/* print results */

        for(i=0; i<3; i++) printf("x[%1d] = %10.4f, ", i, x[i]);
        printf("\n");
}	
