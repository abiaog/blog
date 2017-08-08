#include <stdio.h>

int power(int,int);

int main() {

	int i;
	printf("Program to calculate power\n");
	for (i=0;i<10;i++)
		printf("%d %d\n",i, power(2,i));
	return 0;
}

int power (int base, int n) {

	int i,p;
	p=1;
	for (i=1; i<=n; i++)
		p = p*base;
	return p;
}

// $ cc -g -o my_prg power.c
