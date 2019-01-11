#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "primes.h"


static Primes *newPrimeNode(uint32_t primeNum);
static uint32_t getNextPrime(uint32_t start);

Primes *Primes_getList(uint32_t start_prime)
{
	int primes_added = 0;
	int primes_to_add = 5;
	if(start_prime < 2)
	{
		fprintf(stderr, "Primes cannot be less than 2.\n");
		return NULL;
	}
	Primes *list = newPrimeNode(0); 
	Primes *cursor = list;
	while(primes_added < primes_to_add)
	{
		uint32_t potential_prime = getNextPrime(start_prime);
		if(potential_prime != 0)
		{
			cursor->next = newPrimeNode(potential_prime);
			cursor->next->last = cursor;
			cursor = cursor->next;
			primes_added++;
		}
		start_prime++;
	}
	list = list->next;
	return list;
	
}

void Primes_destroyList(Primes *list)
{
	if(list == NULL)
	{
		return;
	}
	Primes *cursor = list;
	while(list->next != NULL)
	{
		cursor = list;
		printf("Del: %d\n", cursor->prime);	
		free(cursor);
		list = list->next;
	}
}

static Primes *newPrimeNode(uint32_t primeNum)
{
	Primes *node = calloc(1, sizeof(*node));
	printf("New prime: %d\n", primeNum);
	node->prime = primeNum;
	node->next = node->last = NULL;
	return node;
}

static uint32_t getNextPrime(uint32_t start)
{
	int nextPrime = 0;
	if(start > 1)
	{
		nextPrime = start;
		if(nextPrime == 2 || nextPrime == 3)
		{
			return nextPrime;
		}
		if(nextPrime % 2 == 0)
		{
			return 0;
		}
		for(int i = 3; i < start / 2; i += 2)
		{
			if(nextPrime % i == 0)
			{
				return 0;
			}
			else
			{
				nextPrime = start;
			}
		}
	}
	return nextPrime;
}
