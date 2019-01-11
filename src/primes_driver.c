#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "primes.h"

int main()
{
	Primes *list = Primes_getList(2);
	Primes *index = list;
	for(int i = 0; i < 100; i++)
	{
		printf("Curr prime: %d\n", index->prime);
		if(index->next == NULL)
		{
			printf("Generating Next Primes\n");
			int new_prime = index->prime + 1;
			index->next = Primes_getList(new_prime);
			index = index->next;
		}
		else
		{
			index = index->next;
		}
	}
	Primes_destroyList(list);
	return 0;
}
