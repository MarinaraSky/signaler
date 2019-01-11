#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "primes.h"


static Primes *newPrimeNode(uint32_t primeNum);
static uint32_t getNextPrime(uint32_t num);
static uint32_t isPrime(uint32_t num);

Primes *Primes_getList(uint32_t start_prime)
{
	int primes_added = 0;
	int primes_to_add = 5;
	if(start_prime < 2)
	{
		fprintf(stderr, "Primes cannot be less than 2.\n");
		return NULL;
	}
	Primes *list = NULL; 
	Primes *cursor = list;
	while(primes_added < primes_to_add)
	{
		if(list == NULL)
		{
			list = newPrimeNode(getNextPrime(start_prime));
			cursor = list;
			start_prime = list->prime;
			//printf("List Head: %d\n", list->prime);
		}
		else
		{
			//printf("Start Prime: %d\n", start_prime);
			cursor->next = newPrimeNode(getNextPrime(start_prime));
			cursor->next->last = cursor;
			start_prime = cursor->next->prime;
			cursor = cursor->next;
		}
		primes_added++;
		start_prime++;
	}
	//list = list->next;
	return list;
	
}

static Primes *newPrimeNode(uint32_t primeNum)
{
	Primes *node = calloc(1, sizeof(*node));
	//printf("New prime: %d\n", primeNum);
	node->prime = primeNum;
	node->next = node->last = NULL;
	return node;
}

static uint32_t getNextPrime(uint32_t start)
{
	for(int i = start; i < start * 2; i++)
	{
		if(isPrime(i))
		{
			return i;
		}
	}
	return 0;
}

static uint32_t isPrime(uint32_t num)
{
	int nextPrime = 0;
	if(num > 1)
	{
		nextPrime = num;
		if(nextPrime == 2 || nextPrime == 3)
		{
			return nextPrime;
		}
		if(nextPrime % 2 == 0)
		{
			return 0;
		}
		for(int i = 3; i < num / 2; i += 2)
		{
			if(nextPrime % i == 0)
			{
				return 0;
			}
			else
			{
				nextPrime = num;
			}
		}
	}
	return nextPrime;
}
