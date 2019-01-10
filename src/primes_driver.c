#include <stdlib.h>
#include <stdio.h>
#include "primes.h"

int main()
{
	Primes *list = Primes_getList(2);
	Primes *index = list;
	while(index != NULL)
	{
		printf("Curr prime: %d\n", index->prime);
		index = index->next;
	}
	return 0;
}
