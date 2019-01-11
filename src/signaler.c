#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "primes.h"

static void startOver(int sig);

static bool reverse = false;
static bool skip = false;
static Primes *cursor = NULL;
static Primes *first = NULL;

struct sigaction restart = {
	.sa_handler = &startOver,
	.sa_flags = SA_RESTART
};

int main(void)
{
	uint32_t start = 2;
	sigaction(SIGHUP, &restart, NULL);	
	Primes *list = Primes_getList(start);
	first = cursor = list;
	while(1)
	{
		printf("Curr Prime: %d\n", cursor->prime);
		if(cursor->next == NULL)
		{
			cursor->next = Primes_getList(++cursor->prime);
			cursor->last = cursor;
		}
		cursor = cursor->next;
		sleep(1);
	}
	return 0;
}

static void startOver(int sig)
{
	fprintf(stderr, "RESETTING\n");
	cursor = first;
}
