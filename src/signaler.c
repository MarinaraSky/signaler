#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "primes.h"

static void handleMe(int sig);

static bool reverse = false;
static bool skip = false;
static bool print = true;
static Primes *cursor = NULL;
static Primes *first = NULL;

struct sigaction sigHandler = {
	.sa_handler = &handleMe,
	.sa_flags = SA_RESTART
};

int main(int argc, char **argv)
{
	int opt = 0;
	while((opt = getopt(argc, argv, "r")) != -1)
	{
		switch(opt)
		{
			case 'r':
				printf("2\n");
				return 0;
				break;
		}
	}

	uint32_t start = 2;
	uint32_t primesToMake = 10;
	Primes *list = Primes_getList(start, primesToMake);
	Primes *lastPrime = list;
	first = cursor = list;
	sigaction(SIGALRM, &sigHandler, NULL);
	sigaction(SIGHUP, &sigHandler, NULL);	
	sigaction(SIGUSR1, &sigHandler, NULL);	
	sigaction(SIGUSR2, &sigHandler, NULL);	
	alarm(1);
	while(1)
	{
		if(print == true)
		{
			printf("%d\n", cursor->prime);
			print = false;
			if(reverse == false)
			{
				cursor = cursor->next;
			}
			else if(reverse == true && cursor->last != NULL)
			{
				cursor = cursor->last;	
			}
			else if(reverse == true && cursor->last == NULL)
			{
				return 0;
			}
		}
		if(skip == true && reverse == true)
		{
			if(cursor->prime == 3)
			{
				fprintf(stderr, "No numbers to skip to.\n");
			}
			else
			{
				cursor = cursor->last;
				skip = false;
			}
		}
		else if(skip == true)
		{
			cursor = cursor->next;
			skip = false;
		}
		while(lastPrime->next != NULL)
		{
			lastPrime = lastPrime->next;
		}
		uint32_t nextPrime = lastPrime->prime + 1;
		lastPrime->next = Primes_getList(nextPrime, primesToMake);
		lastPrime->next->last = lastPrime;
		pause();
	}
	return 0;
}

static void handleMe(int sig)
{
	switch(sig)
	{
	case SIGHUP:
		cursor = first;
		break;
	case SIGUSR1:
		skip ^= true;
		break;
	case SIGUSR2:
		reverse ^= true;
		break;
	case SIGALRM:
		print ^= true;
		alarm(1);
		break;
	}
}

