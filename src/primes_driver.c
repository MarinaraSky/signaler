#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "primes.h"

int main()
{
	Primes *list = Primes_getList(2);
	Primes *index = list;
	while(1)
	{
		if(index == NULL)
		{
			index->next = Primes_getList(index->last->prime);
			index = index->next;
		}
		printf("Curr prime: %d\n", index->prime);
		index = index->next;
		sleep(1);
	}
	return 0;
}
