#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//function definitions
unsigned long mod_exp(unsigned long, long long int, unsigned long);
_Bool witness(unsigned long, unsigned long);
_Bool miller_rabin(int, unsigned long);

unsigned int fast_exp(unsigned int, unsigned int, unsigned int);

void generate_keys(unsigned int);

void decrypt(FILE *, int);

void encrypt(FILE *, int);

void get_key(unsigned int *, int);
