#include "bandb.h"
/* 
 * Author: Michelle Berry (Student #: 1082031)
 * Last Updated: Sept 21st, 2020
 * Purpose: Manipulate data and bits and bytes
 */

//retrieve bytes no. of bytes from src and put values into dest
void getbytes( unsigned char dest[], int bytes, void *src, int reverse){
  int s = 0;  
  unsigned char *csrc = src; 

  for(s = 0; s < bytes; s++){
    dest[s] = (reverse == 0 ? *(csrc+s) : *(csrc+(bytes-1-s)));  
  }
}

//retrieve bits from src and copy bit values into dest
void getbits( char dest[], int bytes, void *src, int start, int end){
  int i = 0; int k; 
  unsigned char *csrc = src;  
  int squo; int srem; 

  for(i = 0; start > end; start--, i++){
    squo = start/8; //src[sqo] is certain byte
    srem = start%8; //srem is right bit inside the byte

    k = csrc[bytes - squo - 1] >> srem; 
    dest[i] = ((k & 1) == 1? '1' : '0');

  }
  dest[i] = '\0'; 
}

//my own string length function because libraries were not allowed
int getLen( char *str ){
  int i = 0; 
  while( str[i] ){
    i++; 
  }
  return i; 
}

//binary bit string to long long
unsigned long long bits2ull( char *bits ){
  int bitlen = getLen(bits) - 1; 
  unsigned long long value = 1; 
  unsigned long long toReturn = 0; 

  while(bitlen > -1){
    if (bits[bitlen] == '1'){
      toReturn = toReturn + value; 
    }
    value = value*2;
    bitlen--; 
  }

  return toReturn; 
}

//2's complement signed binary bit string to long long 
long long bits2ll( char *bits ){
  int bitlen = getLen(bits)-1; 
  long long value = 1; 
  long long toReturn = 0; 

  while(bitlen > -1){
    if(bits[bitlen] == '1' && bitlen == 0){
      toReturn = toReturn + ((-1)*value);
    } else if (bits[bitlen] == '1'){
      toReturn = toReturn + value; 
    }
    value = value*2;
    bitlen--; 
  }

  return toReturn; 
}

//single precision floating point to binary
void spff( char *sign, char *exponent, char *significand, float *src ){
  int i = 0; 
  unsigned char bytes[65];
  char bitStr[65];
    
  getbytes( bytes, sizeof(double*), src, 1 );
  getbits( bitStr, sizeof(double*), bytes, 31, -1 );

  //divide string into sign bit, exponent bits, significand
  for(i = 0; i < 32; i++){
    if(i == 0){
      sign[i] = bitStr[i]; 
    } else if(i > 0 && i < 9){
      exponent[i-1] = bitStr[i]; 
    } else {
      significand[i-9] = bitStr[i]; 
    }
  }
  sign[1] = '\0'; 
  exponent[8] = '\0'; 
  significand[23] = '\0'; 
}

//double precision floating point to binary
void dpff( char *sign, char *exponent, char *significand, double *src ){
  int i = 0; 
  unsigned char bytes[65];
  char bitStr[65];
  
  //retrieve bit values using getbits (need to be reversed first)
  getbytes( bytes, sizeof(double*), src, 1 );
  getbits( bitStr, sizeof(double*), bytes, 63, -1 );
  
  //divide string into sign bit, exponent bits, significand
  for(i = 0; i < 64; i++){
    if(i == 0){
      sign[i] = bitStr[i]; 
    } else if(i > 0 && i < 12){
      exponent[i-1] = bitStr[i]; 
    } else {
      significand[i-12] = bitStr[i]; 
    }
  }
  sign[1] = '\0'; 
  exponent[11] = '\0'; 
  significand[52] = '\0';
}
