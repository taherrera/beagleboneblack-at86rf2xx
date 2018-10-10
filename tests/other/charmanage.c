#include <stdio.h>

#define uint8_t unsigned short
#define int8_t short int

int main(void)
{

	char a[1];
	a[0] = 0x64;
	printf("%x , %s\n",*a, a );

	return 1;
}
