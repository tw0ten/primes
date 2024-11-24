#include "../lib/read.c"

int main() {
	const char *PATH = "o/bin";
	FILE *f = fopen(PATH, "ab");
	N i = last(PATH);
	int j = 0;
	while ((i = next(i)) != 0) {
		fwrite(&i, sizeof(N), 1, f);
		if (++j % 1024 == 0)
			fflush(f);
	}
	fclose(f);
}
