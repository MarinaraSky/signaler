#include "primes.h"

typedef struct primes{
	uint32_t prime;
	primes *next;
	primes *last;
}Primes;

void Primes_getList(Primes *list, uint32_t start_prime)
{
	if(list == NULL)
	{
		fprintf(stderr, "Primes list is not allocated.\n");
		return;
	}
	if(start_prime < 2)
	{
		fprintf(stderr, "Primes cannot be less than 2.\n");
		return;
	}
	
}

void Primes_destroyList(Primes *list)
{
	/* While loop to iterate through and free lists */
}

static uint32_t getNextPrime(uint32_t start)
{
	int nextPrime = 0;
	if(start > 1)
	{
		// Algorithm that returns next prime
	}
	return nextPrime;
}
