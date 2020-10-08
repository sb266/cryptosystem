This program uses public-private key pairs to encrypt and decrypt files. The user provides a random seed to be used for key generation, which uses the Miller-Rabin algorithm and a few other tricks to calculate safe primes. Encryption and decryption both use modular exponentiation to scramble (or unscramble) the input block by block.

Included files:
cryptosystem.c
	the main driver program. calls key generation, encryption, and decryption functions as
	specified by users.
generate_keys.c
	generates 'pubkey.txt' and 'prikey.txt', which respectively are public keys and private keys,
	using the algorithm for safe prime generation.
encrypt.c
	runs encryption on the specified plaintext file, using the specified public key. generates
	ciphertext file 'ctext.txt'
decrypt.c
	runs decryption on the specified ciphertext file, using the specified private key. generates
	'dtext.txt', which upon inspection should be equivalent to the plaintext file provided during
	encryption.
get_key.c
	a utility function. used during encryption and decryption to read key values from the specified key
	file. returns an array of unsigned ints containing key values.
fast_exp.c
	calculates fast modular exponentiation. returns the result of a^b mod n.
miller_rabin.c
	uses the miller-rabin algorithm, along with the witness and modular exponentiation functions, to
	determine whether the provided number is prime. returns true or false.

Compile instructions:
run the included makefile:
	make
if for some reason that doesn't work, it can be compiled manually:
	gcc -o public-key-cryptosystem cryptosystem.c generate_keys.c encrypt.c decrypt.c get_key.c fast_exp.c miller_rabin.c -g -lm

Run instructions:
(to generate keys):
	./public-key-cryptosystem keygen
(to encrypt):
	./public-key-cryptosystem <public key file> <file to encrypt> -e
(to decrypt):
	./public-key-cryptosystem <private key file> <file to decrypt> -d
