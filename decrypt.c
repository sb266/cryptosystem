#include "include.h"

void decrypt(FILE * ctextFP, int privateKeyFile)
{
	//prep the decipheredtext file for writing
	FILE * dtextFP = fopen("dtext.txt", "w");
	if(dtextFP == NULL)
	{
		fprintf(stdout, "Error %d: %s\n", errno, strerror(errno));
		exit(1);
	}

	//read private key values from the private key file
	unsigned int private_key[3];
	get_key(private_key, privateKeyFile);
	
	//assign vars from key
	unsigned int p = private_key[0], d = private_key[2], g = private_key[1];

	printf("Decrypting with p = %u, g = %u, d = %u\n", p, g, d);

	uint64_t m, c1, c2, exp;

	uint8_t ciph[8] = {0}, temp[4] = {0};

	printf("Decrypted blocks follow:\n");
	//read 2*(block size) bytes from the ciphertext
	while(fread(ciph, 8, 1, ctextFP))
	{
		//extract c1 and c2 from the ciphertext block
		memcpy(&c1, &ciph[0], 4);
    	memcpy(&c2, &ciph[4], 4);
		memset(ciph, 0, 8);

		exp = fast_exp(c1, p - 1 - d, p);
		//calculate m using the ((c1^(p-1-d) mod p)(c2 mod p)) mod p = m formula
		m = (uint64_t)(exp * (c2 % p)) % p;
		c1 = 0; c2 = 0;

		//convert m into an array of ASCII values
		memcpy(&temp[0], &m, 4);
		m = 0;

		printf("%s", temp); //works fine in Mint but prints garbage in Ubuntu

		fwrite(temp, 1, 4, dtextFP);
	}

	printf("Generated deciphered file 'dtext.txt' in cwd.\n");

	fclose(dtextFP);
}
