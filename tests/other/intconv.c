#include <stdio.h>

int main(void)
{

	#define uint8_t unsigned short
	#define int8_t short int

	int8_t a = -1;
	uint8_t b = (uint8_t) a;
	printf("%d\n",a);
	printf("%d\n",b);
	return 1;
}
