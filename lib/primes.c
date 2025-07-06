#include <stdlib.h>

typedef size_t T;
typedef unsigned long N;

int isprime(const N n) {
	for (N i = 2; i * i <= n; ++i)
		if (n % i == 0)
			return 0;
	return 1;
}

int isrealprime(const N n) {
	if (n < 2)
		return 0;
	return isprime(n);
}

N* count(N f, const N t, N* c) {
	T s = 0xf;
	N* ns = malloc(s * sizeof(N));
	if (!ns)
		return NULL;

	while (f <= t) {
		if (isprime(f)) {
			if (*c == s) {
				s *= 2;
				N* r = realloc(ns, s * sizeof(N));
				if (!r) {
					free(ns);
					break;
				}
				ns = r;
			}

			ns[(*c)++] = f;
		}
		++f;
	}

	return ns;
}

N next(N f) {
	do
		++f;
	while (!isprime(f));
	return f;
}

N* primes(N f, T c) {
	N* ns = malloc(c * sizeof(N));

	ns[0] = next(f);
	for (T i = 1; i < c; i++)
		ns[i] = next(ns[i - 1]);

	return ns;
}
