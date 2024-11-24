#include "primes.c"

#include <stdio.h>

T filesize(const char *p) {
	FILE *f = fopen(p, "r");
	fseek(f, 0, SEEK_END);
	const T s = ftell(f);
	fclose(f);
	return s;
}

void *readfilebytes(const char *p) {
	FILE *f = fopen(p, "rb");
	const T s = filesize(p);
	void *ns = malloc(s);
	fread(ns, s, 1, f);
	fclose(f);
	return ns;
}

N last(const char *p) {
	FILE *f = fopen(p, "rb");
	fseek(f, -sizeof(N), SEEK_END);
	N n;
	if (fread(&n, sizeof(N), 1, f) != sizeof(N))
		n = 1;
	fclose(f);
	return n;
}
