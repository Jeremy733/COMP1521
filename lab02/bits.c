// COMP1521 18s1 Week 02 Lab (warm-up)

#include <stdio.h>

int getMaxInt(){
	return ((unsigned int)-1)>>1;
}

int getMaxUnsignedInt(){
	return ~0;
}

long long int getLLInt(){
	return ((unsigned long long int)-1)>>1;
}

long long int getULLInt(){
	return ~0;
}

int main()
{
	// Code to generate and display the largest "int" value
    

	int x = getMaxInt();


    	printf("int %x, %d\n", x, x);
    
	// Code to generate and display the largest "unsigned int" value

	unsigned int y = getMaxUnsignedInt();


	printf("unsigned int %x, %u\n", y, y);
    
	// Code to generate and display the largest "long int" value

	long int xx = x;
	printf("long int %lx, %li\n", xx, xx);

	// Code to generate and display the largest "unsigned long int" value

	unsigned long int xy = y;
	printf("unsigned long int %lx, %lu\n", xy, xy);

	// Code to generate and display the largest "long long int" value
    
	long long int xxx = getLLInt(); 

    	printf("long long int %llx, %lli\n", xxx, xxx);

	// Code to generate and display the largest "unsigned long long int" value

	unsigned long long int xxy = getULLInt();


	printf("unsigned long long int %llx, %llu\n", xxy, xxy);
	return 0;
}
