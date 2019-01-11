#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "primes.h"

static void handleMe(int sig);

static bool reverse = false;
static bool skip = false;
static Primes *cursor = NULL;
static Primes *first = NULL;

struct sigaction sigHandler = {
	.sa_handler = &handleMe,
	.sa_flags = SA_RESTART
};

int main(void)
{
	uint32_t start = 2;
	sigaction(SIGHUP, &sigHandler, NULL);	
	sigaction(SIGUSR1, &sigHandler, NULL);	
	sigaction(SIGUSR2, &sigHandler, NULL);	
	Primes *list = Primes_getList(start);
	first = cursor = list;
	while(1)
	{
		printf("Curr Prime: %d\n", cursor->prime);
		printf("Skip: %d\n", skip);
		if(cursor->next == NULL)
		{
			int nextPrime = cursor->prime + 1;
			cursor->next = Primes_getList(nextPrime);
			cursor->next->last = cursor;
			cursor = cursor->next;
		}
		if(reverse == false)
		{
			cursor = cursor->next;
		}
		else if(reverse == true && cursor->last != NULL)
		{
			cursor = cursor->last;
		}
		if(skip == true && cursor->next != NULL && cursor->next->next == NULL)
		{
			int nextPrime = cursor->next->prime + 1;
			cursor->next->next = Primes_getList(nextPrime);
			cursor->next->next->last = cursor;
			cursor = cursor->next;
			skip = false;
		}
		else if(skip == true && reverse == true)
		{
			cursor = cursor->last;
			skip = false;
		}
		else if(skip == true)
		{
			cursor = cursor->next;
			skip = false;
		}
		sleep(1);
	}
	return 0;
}

static void handleMe(int sig)
{
	switch(sig)
	{
	case SIGHUP:
		fprintf(stderr, "RESETTING\n");
		cursor = first;
		break;
	case SIGUSR1:
		fprintf(stderr, "SKIPPING\n");
		skip ^= true;
		break;
	case SIGUSR2:
		fprintf(stderr, "REVERSING\n");
		reverse ^= true;
		break;
	}
}

