#include "../lib/primes.c"

#include <stdio.h>

T filesize(const char *p) {
  FILE *f = fopen(p, "r");
  fseek(f, 0, SEEK_END);
  T s = ftell(f);
  fclose(f);
  return s;
}

N *read(const char *p) {
  FILE *f = fopen(p, "rb");
  T s = filesize(p);
  N *ns = malloc(s);
  fread(ns, 1, s, f);
  fclose(f);
  return ns;
}

N last(const char *p) {
  FILE *f = fopen(p, "rb");
  fseek(f, -sizeof(N), SEEK_END);
  N n;
  if (!fread(&n, sizeof(N), 1, f)) {
    fclose(f);
    return 1;
  }
  fclose(f);
  return n;
}

int main() {
  const char *PATH = "o/bin";
  FILE *f = fopen(PATH, "ab");
  N i = last(PATH);
  int j = 0;
  while ((i = next(i)) != 0) {
    fwrite(&i, sizeof(N), 1, f);
    if (++j % 128 == 0)
      fflush(f);
  }
  fclose(f);
}
