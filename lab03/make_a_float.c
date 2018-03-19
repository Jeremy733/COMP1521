// make_a_float ... read in bit strings to build a float value
// COMP1521 Lab03 exercises
// Written by John Shepherd, August 2017
// Completed by ...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


typedef uint32_t Word;

struct _float {
   // define bit_fields for sign, exp and frac
   // obviously they need to be larger than 1-bit each
   // and may need to be defined in a different order
   unsigned int frac:23, exp:8, sign:1;
};
typedef struct _float Float32;

union _bits32 {
   float   fval;  // interpret the bits as a float
   Word    xval;  // interpret as a single 32-bit word
   Float32 bits;  // manipulate individual bits
};
typedef union _bits32 Union32;

void    checkArgs(int, char **);
Union32 getBits(char *, char *, char *);
char   *showBits(Word, char *);
int     justBits(char *, int);
char* Itoa(int value, char* str, int radix);

int main(int argc, char **argv)
{
   union _bits32 u;
   char out[50];

   // here's a hint ...
   u.bits.sign = u.bits.exp = u.bits.frac = 0;

   // check command-line args (all strings of 0/1
   // kills program if args are bad
   checkArgs(argc, argv);

   // convert command-line args into components of
   // a Float32 inside a Union32, and return the union
   u = getBits(argv[1], argv[2], argv[3]);
   //printf("%d\n",u.bits.frac);
   printf("bits : %s\n", showBits(u.xval,out));
   printf("float: %0.10f\n", u.fval);

   return 0;
}

// convert three bit-strings (already checked)
// into the components of a struct _float
Union32 getBits(char *sign, char *exp, char *frac)
{
   Union32 new;
   int mant;
   double f;
   new.bits.sign = new.bits.exp = new.bits.frac = 0;
   new.bits.sign += (sign[0]-'0');
   //printf("%x\n",new.bits.sign);
   int j=0;
   for(j=0;j<7;j++){
   	new.bits.exp += (exp[j]-'0');

   	new.bits.exp <<= 1;
   }
   //printf("%x\n",new.bits.exp);
   for(j=0;j<22;j++){
   	new.bits.frac += (frac[j]-'0');

   	new.bits.frac <<= 1;
   }
   //printf("%x\n",new.bits.frac);   
   //unsigned int * p = (unsigned int *)&new.bits;
   //    printf("%x\n", *p);

   int i;
   int ex = 0;
   for (i = 0; i <= 7; i++)
       ex = ex * 2 + (exp[i] - '0');
   ex -= 127;
   if (ex > -127){
   // Normal(ized) numbers
       mant = 1; // The implicit "1."
   // Account for "1." being in bit position 23 instead of bit position 0
       ex -= 23;
   }else{
   // Subnormal numbers
       mant = 0; // No implicit "1."
       ex = -126; // See your IEEE-54 formulas
   // Account for ".1" being in bit position 22 instead of bit position -1
       ex-= 23;
   } 
   for (i = 0; i <= 22; i++)
       mant = mant * 2 + (frac[i] - '0');
       f = mant;   
   while (ex > 0)
       f *= 2, ex--;

   while (ex < 0)
       f /= 2, ex++;   
   if (new.bits.sign)
       f = -f;     
   new.fval = f;

   return new;
}

// convert a 32-bit bit-stringin val into a sequence
// of '0' and '1' characters in an array buf
// assume that buf has size > 32
// return a pointer to buf
char *showBits(Word val, char *buf)
{
   unsigned int * p = (unsigned int *)&val;
   Itoa(*p,buf,2);
   return buf;
}

// checks command-line args
// need at least 3, and all must be strings of 0/1
// never returns if it finds a problem
void checkArgs(int argc, char **argv)
{
   if (argc < 3) {
      printf("Usage: %s Sign Exp Frac\n", argv[0]);
      exit(1);
   }
   if (!justBits(argv[1],1)) {
      printf("%s: invalid Sign: %s\n", argv[0], argv[1]);
      exit(1);
   }
   if (!justBits(argv[2],8)) {
      printf("%s: invalid Exp: %s\n", argv[0], argv[2]);
      exit(1);
   }
   if (!justBits(argv[3],23)) {
      printf("%s: invalid Frac: %s\n", argv[0], argv[3]);
      exit(1);
   }
   return;
}

// check whether a string is all 0/1 and of a given length
int justBits(char *str, int len)
{
   if (strlen(str) != len) return 0;

   while (*str != '\0') {
      if (*str != '0' && *str != '1') return 0;
      str++;
   }
   return 1;
}

char* Itoa(int value, char* str, int radix) {
    static char dig[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    int n = 0;
    unsigned int v;
    char* p, *q;
    char c;
    /*if (radix == 10 && value < 0) {
        value = -value;
        neg = 1;
    }*/
    v = value;
    do {
    	if(n == 23 || n == 32){
    	    str[n++] = ' ';
    	    continue;
    	}
        str[n++] = dig[v%radix];
        v /= radix;
    } while (v);
    /*if (neg)
        str[n++] = '-';*/
    //printf("%d\n",n);
    while(n < 34){
    	if(n == 23 || n == 32){
    	    str[n++] = ' ';
    	    continue;
    	}
    	str[n] = '0';
    	n++;
    }
    str[n] = '\0';
    //printf("%s\n",str);
    for (p = str, q = p + (n-1); p < q; ++p, --q)
        c = *p, *p = *q, *q = c;
    return str;
}
