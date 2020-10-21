#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void 
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

float 
*func(int *rank, float *x, float *b, float *c, float *coeff, float *rs) 
{
    float    *err;
    int    i, itemp = *rank-1;

    err = (float *)malloc( *rank * sizeof(float));


    b[itemp]= coeff[itemp];
    b[itemp-1]= coeff[itemp-1] + rs[0] * b[itemp];
    for(i=itemp-2; i>=0; i--) b[i]= coeff[i] + rs[0] * b[i+1] + rs[1] * b[i+2];
 
    c[itemp]= b[itemp];
    c[itemp-1]= b[itemp-1] + rs[0] * c[itemp];
    for((i=itemp-2); i>=1; i--) c[i]= b[i] + rs[0] * c[i+1] + rs[1] * c[i+2];

    err[1]= (-c[1]*b[1] + c[2]*b[0])/(c[1]*c[3] - c[2]*c[2]);
    err[0]= (-c[3] * err[1] -b[1])/c[2];

    rs[0] = rs[0] + err[0]; rs[1] = rs[1] + err[1];

    err[1]= err[1]/rs[1]; err[0]= err[0]/rs[0];
    if( err[0] < 0 ) err[0]=-err[0];
    if( err[1] < 0 ) err[1]=-err[1];

    return err;
}

float 
*Bairstow( float *(*fn)(int *, float *, float *, float *,float *, float * ),
            float *rs, int *rank, float epsilon, int Max_iteration)
{
        float   *x,*b, *c, d;

    float    coeff[6]={ 1.25, -3.875, 2.125, 2.75, -3.5, 1.0};     
            /* 1.25x^5 -3.875x^4 +2.125x^3 + 2.75x^2 -3.5x + 1.0 = 0.0 */

    int    imaginary[6]={ 0, 0, 0, 0, 0, 0 };
    float    *err;
        int     i=0;

    x = (float *)calloc( *rank, sizeof(float));
    b = (float *)malloc( *rank * sizeof(float));
    c = (float *)malloc( *rank * sizeof(float));

    do{
        if( i++ > Max_iteration ) {
            printf(" It dosen't converg!!!\n");
            exit(0);
        }
        err = fn( rank, x, b, c, coeff, rs );
        if( err[0] <= epsilon && err[1] <= epsilon )
        {
	    printf("r : %f, s : %f\n", rs[0], rs[1]);
            if( (d = rs[0]*rs[0] + 4 * rs[1]) > 0 ) 
            {
                x[*rank-1]= 0.5 *( rs[0] + sqrt(d));
                x[*rank-2]= 0.5 *( rs[0] - sqrt(d));
            }
            else if ( d == 0 ) { x[*rank-1]= x[*rank-2]= 0.5 * rs[0]; }
            else
            {
                x[*rank-1]= 0.5 * rs[0];
                                x[*rank-2]= 0.5 * sqrt(-d);
            }
            *rank -= 2;
            for( i = 0; i < *rank; i++ ) coeff[i] = b[i+2];
        }
    } while( *rank > 3 );

    if( *rank == 3 ) quad( x, coeff );
    else x[*rank-1]= - rs[1] / rs[0];
        return x;
}

int     
main()
{
        float   *(*funcs)(  int *, float *, float *,float *,float *, float *) = *func;

        int    *rank;
        int     i, Max_iteration= 1000;

        float   rs[2]; 
        float    epsilon = 0.01;
    rs[0]    =-1.0, rs[1]    =-1.0;
        float    *result;

    rank    = (int *)malloc(sizeof(int));
    *rank     = 6;

        result  = Bairstow( *funcs,  rs, rank, epsilon, Max_iteration);    

    for( i=1; i< 6; i++) 
    {
        printf("x[%1d] = %7.3f, ",i,result[i]);
        printf("\n");
    }
}

