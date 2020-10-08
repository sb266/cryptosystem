#include "include.h"

void get_key(unsigned int * key, int fp)
{
	int i = 0;
	unsigned int buf, dummy;

	while(read(fp, &buf, 4))
	{
		//printf("got key buf: %u\n", buf);
		read(fp, &dummy, 1); //read a space
		key[i] = buf;
		if(i >= 2)
		{
			break;
		}
		i++;
		buf = 0;
	}
}
