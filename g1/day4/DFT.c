

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void DFT( double *xr, double *xi, double *Xr, double *Xi, int N )
{
  int k, n;

  for( k = 0 ; k < N ; k++ ) {
    Xr[k] = Xi[k] = 0.0;
    for( n = 0 ; n < N ; n++ ) {
      Xr[k] +=   /* ?????????? */
      Xi[k] +=   /* ?????????? */
    }
  }
  return;
}

int main( int argc, char *argv[] )
{
  int  i, nskip, framelen;
  double spec;
  short  *sdata;
  double *xr, *xi, *Xr, *Xi;
  FILE *fpDAT;y
  
  if( 4 != argc ) {
    fprintf( stderr, "Usage : %s DATfile skip[sample] frame_length[sample]\n", argv[0] );
    exit( 1 );
  }

  if( NULL == ( fpDAT = fopen( argv[1], "r" ) ) )  exit( 1 );
  if( 0 > ( nskip    = atoi( argv[2] ) ) )  exit( 1 );
  if( 0 > ( framelen = atoi( argv[3] ) ) )  exit( 1 );

  fprintf( stderr, "# DATfile = %s\n", argv[1] );
  fprintf( stderr, "# %d samples are skipped.\n", nskip );
  fprintf( stderr, "# 1 frame contains %d sampels.\n", framelen );
b
  /* memory allocation */
  sdata = (short*)calloc( sizeof(short), framelen );
  xr = (double*)calloc( sizeof(double), framelen );
  xi = (double*)calloc( sizeof(double), framelen );
  Xr = (double*)calloc( sizeof(double), framelen );
  Xi = (double*)calloc( sizeof(double), framelen );
  if( NULL == sdata || NULL == xi || NULL == xi || NULL == Xr || NULL == Xi )  exit( 1 );

  fseek( fpDAT, nskip*sizeof(short), SEEK_SET );
  fread( sdata, sizeof(short), framelen, fpDAT );
  fclose( fpDAT );

  for( i = 0 ; i < framelen ; i++ ) {
    xr[i] = sdata[i];
    xi[i] = Xr[i] = Xi[i] = 0.0;
  }

  DFT( xr, xi, Xr, Xi, framelen );

  for( i = 0 ; i < framelen/2 ; i++ ) {
    spec = log10( (1.0/framelen)*( Xr[i]*Xr[i]+Xi[i]*Xi[i] ) );
    printf( "%d %lf\n", i, spec );
  }

  return( 0 );
}
