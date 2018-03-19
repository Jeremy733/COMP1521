// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct _bit_fields {
   unsigned int a : 4,
                b : 8,
                c : 20;
};

int main(void)
{
    struct _bit_fields x;

    x.a = 0x4;  
    //a: 0100
    x.b = 0xa4; 
    //b:  1010 0100
    x.c = 0xabcde; 
    //c: 1010 1011 1100 1101 1110   
    
    unsigned int * p = (unsigned int *)&x;
    //printf("%d\n",*(p+1));
  /*  for(int i = 0;i < 4; i++){
        for(int j = 0;j <= 7;j++){
            if(*(p + i) & (1 << j)) printf("1"); 
            else printf("0");
        }
        printf(" ");
    }
    // 00100010 01010111 10110011 11010101
    printf("\n");
    */
    printf("%x\n", *p);
    return 0;
}
