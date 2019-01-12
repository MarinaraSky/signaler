#include <stdint.h>

/**
 * @file primes.h
 * @author Jack Spence
 * @date 10 Jan 2018
 * @brief Header file for my prime finding algorithm
 */

/**
 * @struct primes
 * @brief Doubly linked list of prime numbers
 */
typedef struct primes Primes;

struct primes{
	uint32_t prime;
	Primes *next;
	Primes *last;
};

/**
 * @brief Generates list of next 100 primes
 * @param start_prime Prime Number to start from
 * @param primesToMake Number of primes to find
 * @return Pointer to list of new primes
 */
Primes *Primes_getList(uint32_t start_prime, uint32_t primesToMake);
