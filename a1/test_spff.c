#include <stdio.h>
#include "bandb.h"

int main( int argc, char **argv )
{
  float x;
  char sign[2], exponent[9], significand[24];

  //x = -127.1;
  x = 0.15625;

  spff( sign, exponent, significand, &x );

  printf( "%f\n", x );
  printf( "%s %s %s\n", sign, exponent, significand );
  printf( "%sx(-1) x 2**%lld x %f\n", sign, bits2ull( exponent)-127, 
       1.0+(float)(bits2ull(significand))/(1<<23) );
  return 0;
}

