#include "include.h"

void encrypt(FILE * plainText, int publicKeyFile)
{
	FILE * cipherText = fopen("ctext.txt", "w");
	if(cipherText == NULL)
	{
		fprintf(stdout, "Error %d: %s\n", errno, strerror(errno));
		exit(1);
	}

	//read key parts from the key file
	unsigned int public_key[3];
	get_key(public_key, publicKeyFile);

	//assign vars from key
	unsigned int g = public_key[1], e2 = public_key[2],
				 p = public_key[0], k = 0;

	uint64_t exp, c2, c1;

	uint8_t ciph[8] = {0}, temp[4] = {0};

	srand(time(NULL));

	printf("Decrypting with p = %u, g = %u, e2 = %u\n", p, g, e2);

	//loop through the file and encrypt 32-bit blocks
	while(fread(temp, 4, 1, plainText))
	{
		//pick k from {0, ..., p - 1}
		k = (unsigned int) ((unsigned int)rand() % p);
		
		//calculate c1 = g^k mod p
		c1 = fast_exp(g, k, p);

		exp = fast_exp(e2, k, p);

		//cast the data to an array of unsigned ints so it can be "multiplied"
		//and then finish calculating c2 = e2^k * m mod p.
		c2 = (uint64_t)(exp * *((uint32_t*)temp)) % p;

		printf("Block encrypted:\nc1 =\t%lu\nc2 =\t%lu\n", c1, c2);

		//concatenate c1 and c2 into the ciphertext block
		memcpy(&ciph[0], &c1, 4);
    	memcpy(&ciph[4], &c2, 4);

		//write 2*(block size) bytes to the ciphertext file
		fwrite(ciph, 8, 1, cipherText);

		//make sure there's no garbage data hanging around
		memset(ciph, 0, 8);
		memset(temp, 0, 4);
		c1 = 0; c2 = 0;
	}
	fclose(cipherText);
}
