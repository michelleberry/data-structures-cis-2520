#include <stdio.h>
#include "bandb.h"

int main( int argc, char **argv )
{
  double x;
  char sign[2], exponent[12], significand[53];

  //x = -127.1;
  x = 0.15625;

  dpff( sign, exponent, significand, &x );

  printf( "%lf\n", x );
  printf( "%s %s %s\n", sign, exponent, significand );
  printf( "%sx(-1) x 2**%lld x %lf\n", sign, bits2ull( exponent)-1023, 
       1.0+(double)(bits2ull(significand))/(1ULL<<52) );
  return 0;
}

