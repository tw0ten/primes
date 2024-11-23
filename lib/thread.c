#include "primes.c"

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
T primescount = 0;
N *primecount = NULL;

void *primecounter() {
  T cap = 1;
  N i = 2;
  primecount = malloc(cap * sizeof(N));
  while (1) {
    if (isprime(i)) {
      pthread_mutex_lock(&mutex);
      if (primescount >= cap) {
        cap *= 2;
        primecount = realloc(primecount, cap * sizeof(N));
      }
      primecount[primescount++] = i;
      pthread_mutex_unlock(&mutex);
    }
    ++i;
  }
}
