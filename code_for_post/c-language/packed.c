//#pragma pack(push,1) // If you wish to insist 1 size padding for all the structures, simply we can push the alignment value to stack using #pragma

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	char Data1;
	int Data2;
	unsigned short Data3;
	char Data4;

}__attribute__((packed, aligned(1))) sSampleStruct; 

typedef struct
{
	char Data1;
	int Data2;
	unsigned short Data3;
	char Data4;

} sSampleStruct12; 

int main ( int argc, char *argv[] )
{
	printf("sizeof(char):%d\n",sizeof(char));
	printf("sizeof(int):%d\n",sizeof(int));
	printf("sizeof(unsigned short):%d\n",sizeof(unsigned short));
	printf("sizeof(sSampleStruct):%d\n",sizeof(sSampleStruct));
	printf("sizeof(sSampleStruct12):%d\n",sizeof(sSampleStruct12));
	return 0;
}	

//#pragma pop
