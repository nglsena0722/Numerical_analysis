#include <math.h>
#include <stdio.h>
#define MAX 4
double a[MAX][MAX]={
{ 5.0, -4.0, 1.0, 0.0 },
{ -4.0, 6.0, -4.0, 1.0 },
{ 1.0, -4.0, 6.0, -4.0 },
{ 0.0, 1.0, -4.0, 5.0 } };
double e_vect[MAX][MAX]={
{ 1.0, 0.0, 0.0, 0.0 },
{ 0.0, 1.0, 0.0, 0.0 },
{ 0.0, 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 0.0, 1.0 } };
double
ddabs(double x)
{
if(x<0.0) return(-x);
else return(x);
}
void
findij( int *i, int *j)
{
int k,l;
double tt=0.0,ddabs();
for(k=0;k<MAX;k++){
for(l=k+1;l<MAX;l++) {
if( ddabs(a[k][l]) > tt ) {
tt = ddabs(a[k][l]);
*i = k; *j = l;
}
}
}
}
double
tann(int i, int j)
{
double t,ddabs();
t= 2.0*a[i][j]/(ddabs(a[i][i]-a[j][j]) +
sqrt((a[i][i]-a[j][j])*(a[i][i]-a[j][j])+4.0*a[i][j]*a[i][j]));
return(t);
}
void
get_an( double u[MAX][MAX])
{
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
void
get_ev(double u[MAX][MAX])
{
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
void
get_u(int i,int j, double c, double s)
{
int k,l;
double u[MAX][MAX];
for(k=0;k<MAX;k++){
for(l=0;l<MAX;l++) {
if(k == l ) u[k][l] = 1.0;
else u[k][l] = 0.0;
}
}
u[i][i] = c; u[i][j] = -s; u[j][i] = s; u[j][j] = c;
get_an(u);
get_ev(u);
}
int
main()
{
int i,j,k,l;
double t, c, s, tann(), tem, ddabs();
for(k=0;k<MAX;k++){
for(l=0;l<MAX;l++) printf(" %12.6f", a[k][l]);
printf("\n");
}
printf("\n");
for(;;){
findij(&i,&j);
tem = ddabs(a[i][j]);
if(tem < 0.000000001) break;
t = tann(i,j);
c = 1.0/(sqrt(1.0 + t*t));
s = c * t;
get_u(i,j,c,s);
}
for(k=0;k<MAX;k++){
for(l=0;l<MAX;l++) printf(" %12.6f", a[k][l]);
printf("\n");
}
printf("\n");
for(i=0;i<MAX;i++){
for(j=0;j<MAX;j++) printf(" %12.6f", e_vect[i][j]);
printf("\n");
}
}
