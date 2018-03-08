// BigNum.h ... LARGE positive integer values

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "BigNum.h"

// Initialise a BigNum to N bytes, all zero
void initBigNum(BigNum *n, int Nbytes)
{
   assert(Nbytes != 0);
   assert(n != NULL);
   n->nbytes = Nbytes;
   n->bytes = (Byte *)malloc(Nbytes*sizeof(Byte));
   memset(n->bytes,'0',Nbytes);
   return;
}

// Add two BigNums and store result in a third BigNum
void addBigNums(BigNum n, BigNum m, BigNum *res)
{
   // set size to be one greater than the bigger one
   int size = (n.nbytes >= m.nbytes ? n.nbytes : m.nbytes) + 1;
   
   // if the size is bigger than res->nbytes
   if(res->nbytes < size){
   	free(res->bytes);
   	res->nbytes = size;
   	res->bytes = (Byte *)malloc(size*sizeof(Byte));
   	memset(res->bytes,'0',size);
   }else{
   	res->nbytes = size;
   }

   int curr = 0;
   int flag = 0;
   int temp = 0;
   
   while(curr<=size){
   	// when it comes to the end
   	if(curr == size-1 && flag == 1){
		res->bytes[curr] = 1 + '0';
		break;
	}else if(curr == size-1 && flag == 0){
		break;
	}else{
		if(curr >= n.nbytes){
			temp = m.bytes[curr]-'0';
		}else if (curr >= m.nbytes){
			temp = n.bytes[curr]-'0';
		}else{
			temp = (n.bytes[curr]-'0')+(m.bytes[curr]-'0');
		}
		// if the sum of two digits greater than 10
		if(flag == 1){
		   	temp ++;
		   	flag = 0;
		}
		if(temp >= 10){
			temp -= 10;
			flag = 1;
		}
		res->bytes[curr] = temp + '0';
	}
	curr++;
   } 	
   return;
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum(char *s, BigNum *n)
{
   assert(s != NULL);
   assert(n != NULL);
   int curr = 0;
   int size = 0;
   // count for how many digits in the array
   while(s[curr]!='\0'){
	   if(s[curr]>='0' && s[curr]<='9'){
		size++;
	   }
	   curr++;
   }
   // in no digits in the array
   if(size == 0){
   	return 0;
   }
   // if the size is bigger than res->nbytes
   if(n->nbytes < size){
   	free(n->bytes);
   	n->bytes = (Byte *)malloc(size*sizeof(Byte));
   	n->nbytes = size;
   	memset(n->bytes,'0',size);
   }else{
   	n->nbytes = size;
   }
   
   int i = size-1;
   curr = 0;
   
   while(s[curr]!='\0' && i >= 0){
   	if(s[curr]>='0' && s[curr]<='9'){
		n->bytes[i] = s[curr];
		i--;
	}
	curr++;
   }
   return 1;
}

// Display a BigNum in decimal format
void showBigNum(BigNum n)
{
   int curr = n.nbytes-1;
   int flag = 0;
   // ignore leading '0' digits
   while(curr >= 0){
   	if(flag){
   		
   		printf("%c",n.bytes[curr]);
   		curr--;
   		continue;
   	}else{
   		if(n.bytes[curr] == '0'){
   			curr--;
   			continue;
   		}
   		flag = 1;
   	}
   }
   // if there are no non-'0' digits in the array
   if(flag == 0){
 	printf("0");
   }
   return;
}

