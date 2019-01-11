#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "primes.h"

int main()
{
	Primes *list = Primes_getList(2);
	Primes *index = list;
	for(int i = 0; i < 1000; i++)
	{
		printf("Curr prime: %d\n", index->prime);
		if(index->next == NULL)
		{
			int new_prime = index->prime + 1;
			index->next = Primes_getList(new_prime);
			index->next->last = index;
			index = index->next;
		}
		else
		{
			index = index->next;
		}
		//sleep(1);
	}
	printf("Reverse\n");
	while(index != NULL)
	{
		printf("Curr prime r: %d\n", index->prime);
		index = index->last;
		//sleep(1);
	}
	return 0;
}
