#include "include.h"

int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		printf("Not enough arguments.\n");
		return 1;
	}

	if(0 == strncmp(argv[1], "keygen", 6))
	{
		unsigned int seed = 0;
		printf("Generating key pairs.\nEnter random seed: ");
		scanf("%u", &seed);

		generate_keys(seed);
	}
	else if(argc == 4 && 0 == strncmp(argv[3], "-e", 2))
	{
		//open public key file, and error out if unable to open.
		int pubKeyFile;
		if(-1 == (pubKeyFile = open(argv[1], O_RDONLY)))
		{
			fprintf(stdout, "Error %d: %s '%s'\n", errno, strerror(errno), argv[1]);
			return 1;
		}

		//open plaintext file, and error out if unable to open.
		FILE * plainText = fopen(argv[2], "r");
		if(plainText == NULL)
		{
			fprintf(stdout, "Error %d: %s '%s'\n", errno, strerror(errno), argv[2]);
			return 1;
		}

		encrypt(plainText, pubKeyFile);
		fclose(plainText); close(pubKeyFile);
		
	}
	else if(argc == 4 && 0 == strncmp(argv[3], "-d", 2))
	{
		//open public key file, and error out if unable to open.
		int priKeyFile;
		if(-1 == (priKeyFile = open(argv[1], O_RDONLY)))
		{
			fprintf(stdout, "Error %d: %s '%s'\n", errno, strerror(errno), argv[1]);
			return 1;
		}

		//open ciphertext file, and error out if unable to open.
		FILE * cipherText = fopen(argv[2], "r");
		if(cipherText == NULL)
		{
			fprintf(stdout, "Error %d: %s '%s'\n", errno, strerror(errno), argv[2]);
			return 1;
		}

		decrypt(cipherText, priKeyFile);
		fclose(cipherText);close(priKeyFile);
	}
	else
	{
		printf("Bad or missing argument(s)\n");
	}

	return 0;
}
