#include "include.h"

void generate_keys(unsigned int seed)
{
	printf("Seeding rand() with %u\n", seed);
	srand(seed);

	unsigned int q = 0, d = 0, g = 2, e2 = 0, p = 0;

	while(1)
	{
		q = (unsigned int) rand(); //select random (k-1)-bit prime
		if(q % 12 == 5) //make sure q mod 12 = 5. this breaks the algorithm's order a bit, but checking this first can prevent the more costly miller_rabin from running if there's no reason to.
		{
			if(!miller_rabin(40, q)) //make sure q is actually prime
			{
				p = (2 * q) + 1; //calculate p

				if(!miller_rabin(40, p) && (p & (1<<31))) //check if p is prime
				{
					break;
				}
			}
		}
	}

	//select d in {1, 2, ..., p - 1}
	d = 1 + ((unsigned int)rand() % (p - 2));
	
	e2 = fast_exp(g, d, p);

	//printf("g = %u, d = %u, p = %u, e2 = %u\n", g, d, p, e2);
	printf("generated p =\t%u\npicked d =\t%u\ncalculated e2 =\t%u\n", p, d, e2);

	//remove old key files
	fclose(fopen("pubkey.txt", "w"));
	fclose(fopen("prikey.txt", "w"));

	int publicKeyFile = open("pubkey.txt", O_WRONLY|O_APPEND|O_CREAT, 0666);
	int privateKeyFile = open("prikey.txt", O_WRONLY|O_APPEND|O_CREAT, 0666);
	if(-1 == publicKeyFile || -1 == privateKeyFile)
	{
		fprintf(stdout, "Error %d: %s\n", errno, strerror(errno));
		exit(1);
	}

	char space = ' ';
	//write public key parts to pubkey.txt, with key format: p g e2
	write(publicKeyFile, &p, 4); write(publicKeyFile, &space, 1);
	write(publicKeyFile, &g, 4); write(publicKeyFile, &space, 1);
	write(publicKeyFile, &e2, 4);

	//write private key parts to prikey.txt, with key format: p g d
	write(privateKeyFile, &p, 4); write(privateKeyFile, &space, 1);
	write(privateKeyFile, &g, 4); write(privateKeyFile, &space, 1);
	write(privateKeyFile, &d, 4);

	close(privateKeyFile); close(publicKeyFile);
}
