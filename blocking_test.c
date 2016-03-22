#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned char* split_block(unsigned char * m, int block_size,int padd );
void text_to_digit(unsigned char * m, int block_size, unsigned char** result, int result_size);
unsigned char * padding(unsigned char* m, int size ) ;
unsigned char * generate_padd( int size );


int main()
{

unsigned char* m = "123456abcdefghijklmnopqrstuvwxyz123456abcdefghijklmnopqrstuvwxyzend8";
unsigned char** result; // = malloc(sizeof(char*)*numberOfLines)

int result_size = 0;
text_to_digit(m, 10, result, result_size );

return 0;
}


void text_to_digit(unsigned char * m, int block_size,unsigned  char** result, int  result_size)
{

  result = malloc(sizeof(char*)*result_size);

  int size = strlen(m)/block_size;   
  int mode = strlen(m)%block_size; 
  int padd = 0;
  result_size = size +1;
  
  for(int i = 0 ; i <= size; ++i )
  {
   if((i == size) && (mode != 0) )
   {
      padd = block_size - mode;
   }
   else
   {
     padd = 0;
   }
  *(result + i) =  split_block((m + i * block_size) , block_size, padd );
  printf("%s\n", *(result + i));
  
 }
  
}

unsigned char* split_block(unsigned char * m, int block_size, int padd  )
{
  unsigned char * split_m = (char*)malloc(block_size); 
  unsigned char * p;
  unsigned char * c;
  p  = memcpy(split_m, m, block_size);

  if(padd != 0)
  {
    c = generate_padd(padd); 
    p = strcat(p,c);
  }
  printf("%s\n ", p  );
  return p; 
}

unsigned char * generate_padd( int size )
{
  unsigned char * padded_m = (char*)malloc(size); 
  for(int i = 0; i < size; i++)
  {
    padded_m = strcat(padded_m, "0"); 
  }
   
  return  padded_m;
}



