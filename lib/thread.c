#include "primes.c"

#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
T primescount = 1;
N *primecount;

void *primecounter() {
  T cap = 1;
  primecount = malloc(cap * sizeof(N));
  primecount[0] = 2;
  N i = 3;
  while (1) {
    if (isprime(i)) {
      pthread_mutex_lock(&mutex);

      if (primescount == cap) {
        cap *= 2;
        primecount = realloc(primecount, cap * sizeof(N));
      }
      primecount[primescount] = i;
      ++primescount;

      pthread_mutex_unlock(&mutex);
    }
    ++i;
  }
}
