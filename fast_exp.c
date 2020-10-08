#include "include.h"

unsigned int fast_exp(unsigned int aa, unsigned int bb, unsigned int cc)
{
	unsigned int a, b, n, bitK = 0;
	a = aa;b = bb;n = cc;

	uint64_t d = 1;

	for(int i = (int)log2(b); i >= 0; i--)
	{
		bitK = (b >> i) & 1;

		d = (uint64_t)(d * d) % n;

		if(bitK == 1)
		{
			d = (d * a) % n;
		}
	}

	return (unsigned int)d;
}
