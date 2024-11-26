#include "primes.c"

#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
T primescount = 1;
N *primecount;

void *primecounter() {
	pthread_mutex_lock(&mutex);
	T n = primescount;
	primecount = malloc(n * sizeof(N));
	pthread_mutex_unlock(&mutex);
	N i = 2;
	while (1) {
		if (isprime(i)) {
			pthread_mutex_lock(&mutex);

			if (primescount == n) {
				n *= 2;
				primecount = realloc(primecount, n * sizeof(N));
			}
			primecount[primescount] = i;
			++primescount;

			pthread_mutex_unlock(&mutex);
		}
		++i;
	}
}
