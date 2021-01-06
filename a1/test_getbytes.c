#include <stdio.h>
#include "bandb.h"

int main( int argc, char **argv )
{
  char *str1 = "abcdefghi";
  //char *str1 = "i am here. meow meow";
  //unsigned int arr[11] = {0,1,2,3,4,5,6,7,8,9,10};
  //unsigned int *str1 = arr;  
  unsigned char dest[9] = "01234567";

  printf( "\"%s\"\n", dest );

  getbytes( dest, 8, str1, 0 );
  dest[8] = '\0';

  printf( "\"%s\"\n", dest );

  getbytes( dest, 8, str1, 1 );
  dest[8] = '\0';

  printf( "\"%s\"\n", dest );

  return 0;
}
