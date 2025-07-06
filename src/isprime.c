#include "../lib/primes.c"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc == 2)
		return !isrealprime(strtoul(argv[1], NULL, 0));
	for (int i = 1; i < argc; i++)
		printf("%d\n", isrealprime(strtoul(argv[i], NULL, 0)));
}
