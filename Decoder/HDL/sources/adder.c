#include <stdio.h>
#include <svdpi.h>
#include <limits.h>

int add(int a, int b)
{
	int c;
	long aux =(long) a + (long)b;
	if(aux > INT_MAX)
	{
		c = INT_MAX;
	}
	else 
		c = a + b;
	return c;
}

int main()
{
	int c = add(2147483647, 7);
	printf("%i\n", c);
}
