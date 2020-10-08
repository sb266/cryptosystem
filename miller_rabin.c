#include "include.h"

unsigned long mod_exp(unsigned long a, long long int b, unsigned long n)
{
	unsigned long d = 1, c = 0;
	long long int bitK = 0;

	for(long long int i = (long long int)log2(b); i >= 0; i--)
	{
		bitK = (b >> i) & 1;

		c *= 2;
		d = (d * d) % n;

		if(bitK == 1)
		{
			c++;
			d = (d * a) % n;
		}

		//printf("%lld, %lld, %lu\n", i, bitK, d);
	}

	return d;
}

_Bool witness(unsigned long a, unsigned long n)
{
	unsigned long prevX, xi, t = 0;
	long long int u = n - 1;
	
	for(; u % 2 == 0; u = u >> 1, t++){}

	prevX = mod_exp(a, u, n);

	for(int i = 1; i <= t; i++)
	{
		xi = (prevX * prevX) % n;
		//printf("%lu, %lu, %lu, %d, %ld\n", xi, prevX, (n - 1), i, t);
		if(xi == 1 && prevX != 1 && prevX != (n - 1))
		{
			return 1;
		}
		prevX = xi;
	}
	if(xi != 1)
	{
		return 1;
	}

	return 0;
}

_Bool miller_rabin(int tests, unsigned long n)
{
	unsigned long s = tests, a;

	//we know all even numbers greater than 2 are composite,
	//so there's no need to bother with any more calculations.
	if(!(n & 1) && n > 2)
	{
		//printf("%ld isn't prime\n", n);
		return 0;
	}

	if(n == 2 || n == 1)
	{
		//printf("%ld is prime\n", n);
		return 0;
	}
	if(n == 0)
	{
		//printf("%ld is weird\n", n);
		return 0;
	}

	for(int j = 0; j <= s; j++)
	{
		unsigned long rando = random();
		a = ((rando << 32 | random()) % (n-1)) + 1;
		if(a == 0)
		{
			a = 1;
		}

		if(witness(a, n))
		{
			//printf("%ld isn't prime\n", n);
			return 1;
		}
	}
	
	//printf("%ld may be prime\n", n);
	return 0;
}
