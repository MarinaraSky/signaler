#ifndef PRIMES_H
#define PRIMES_H

/**
 * @brief Header file for my prime finding algorithm
 */

/**
 * @brief Doubly linked list of prime numbers
 */
typedef struct primes Primes;

/**
 * @brief Generates list of next 100 primes
 * @param list Primes pointer to append next 100 primes to
 * @param start_prime Prime Number to start from
 */
void Primes_getList(Primes *list, uint32_t start_prime);

/**
 * @brief Destroys list of primes
 * @param list List to be destroyed
 */
void Primes_destroyList(Primes *list);

#endif
