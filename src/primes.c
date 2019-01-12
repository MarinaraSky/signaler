#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "primes.h"

/* Allocates memory and sets value for new prime number node */
static Primes *newPrimeNode(uint32_t primeNum);
/* Takes a starting point and finds the next prime number */
static uint32_t getNextPrime(uint32_t num);
/* Check to find if a number is prime */
static uint32_t isPrime(uint32_t num);

Primes *Primes_getList(uint32_t startPrime, uint32_t primesToMake)
{
	uint32_t primesAdded = 0;
	if(startPrime < 2)
	{
		fprintf(stderr, "Primes cannot be less than 2.\n");
		return NULL;
	}
	Primes *list = NULL; 
	Primes *cursor = list;
	while(primesAdded < primesToMake)
	{
		if(list == NULL)
		{
			list = newPrimeNode(getNextPrime(startPrime));
			cursor = list;
			startPrime = list->prime;
		}
		else
		{
			cursor->next = newPrimeNode(getNextPrime(startPrime));
			cursor->next->last = cursor;
			startPrime = cursor->next->prime;
			cursor = cursor->next;
		}
		primesAdded++;
		startPrime++;
	}
	return list;
	
}

static Primes *newPrimeNode(uint32_t primeNum)
{
	Primes *node = calloc(1, sizeof(*node));
	node->prime = primeNum;
	node->next = node->last = NULL;
	return node;
}

static uint32_t getNextPrime(uint32_t start)
{
	for(uint32_t i = start; i < start * 2; i++)
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
	uint32_t nextPrime = 0;
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
		for(uint32_t i = 3; i < num / 2; i += 2)
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
