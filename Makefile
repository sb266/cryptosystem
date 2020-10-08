make: cryptosystem.c encrypt.c decrypt.c fast_exp.c generate_keys.c miller_rabin.c get_key.c
	gcc -o public-key-cryptosystem *.c -lm -g
