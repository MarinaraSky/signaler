/**
 * @file signaler.c
 * @author Jack Spence
 * @date 10 Jan 2018
 * @brief Driver to handle signals and get primes
 */
#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "primes.h"

/**
 * @brief Used as a signal handler for sigaction
 * @param sig Integer of signal sent
 */
static void handleMe(int sig);

/* Group of static globals to interact with signal handler */
static bool reverse = false;
static bool skip = false;
static bool print = true;
static Primes *cursor = NULL;
static Primes *first = NULL;

/**
 * @struct sigHandler
 * @brief Signal hander struct to call my handleMe function 
 */
struct sigaction sigHandler = {
	.sa_handler = &handleMe,
	.sa_flags = SA_RESTART
};

int main(int argc, char **argv)
{
	int opt = 0;
	char *pEnd;
	uint32_t end = -1;
	/* Get opt loop to read CLI arguments */
	while((opt = getopt(argc, argv, "re:")) != -1)
	{
		switch(opt)
		{
			case 'r':
				printf("2\n");
				return 0;
				break;
			case 'e':
			{
				end = strtoul(optarg, &pEnd, 10);
				break;
			}
		}
	}

	uint32_t start = 2;
	uint32_t primesToMake = 10;
	Primes *list = Primes_getList(start, primesToMake);
	Primes *lastPrime = list;
	first = cursor = list;
	/* Starting up signal handling */
	sigaction(SIGALRM, &sigHandler, NULL);
	sigaction(SIGHUP, &sigHandler, NULL);	
	sigaction(SIGUSR1, &sigHandler, NULL);	
	sigaction(SIGUSR2, &sigHandler, NULL);	
	/* Prime the SIGALRM timer used to print primes */
	alarm(1);
	/* Loop used to generate primes */
	while(1)
	{
		/* If timer has gone off to print prime */
		if(print == true)
		{
			if(end > 0 && cursor->prime > end)
			{
				return 0;	
			}
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
				Primes_destroyList(list);
				return 0;
			}
		}
		/* Print in reverse and skip next prime */
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
		/* Skip next prime */
		else if(skip == true)
		{
			cursor = cursor->next;
			skip = false;
		}
		/* Used to keep track of the last prime to append to */
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

