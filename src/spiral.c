#ifdef THREADED
#include "../lib/thread.c"
#else
#include "../lib/primes.c"
#endif

#include <math.h>
#include <raylib.h>

const Color BGCOL = {0x00, 0x00, 0x00, 0x00};

Color col(N n) {
	const unsigned char a = 0xf0, c = n % 255;
	switch ((n / 255) % 3) {
	case 0:
		return (Color){255 - c, c, 0, a};
	case 1:
		return (Color){0, 255 - c, c, a};
	case 2:
		return (Color){c, 0, 255 - c, a};
	}
	return WHITE;
}

typedef long double F;

void draw(F w, F h, const N *ns, const T n) {
	w /= 2.0;
	h /= 2.0;
	const F s = ns[n - 1], l = w > h ? w : h;
	for (N i = 0; i < n; ++i) {
		const N r = ns[i];
		DrawPixel(w + l * r * cos(r) / s, h + l * r * sin(r) / s, col(r));
	}
}

int main() {
	T i;
	N *ns;
#ifdef THREADED
	pthread_t t;
	pthread_create(&t, NULL, primecounter, NULL);
#else
	i = 1;
	T n = i;
	ns = malloc(i * sizeof(N));
	ns[0] = 2;
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MOUSE_PASSTHROUGH);
	SetTargetFPS(64);
	int w = 256, h = w;
	InitWindow(w, h, "spiral");

	while (!WindowShouldClose()) {
		w = GetScreenWidth();
		h = GetScreenHeight();

		ClearBackground(BGCOL);
		BeginDrawing();
#ifdef THREADED
		pthread_mutex_lock(&mutex);
		ns = primecount;
		i = primescount;
#else
		if (!IsKeyDown(KEY_SPACE)) {
			if (i == n) {
				n *= 2;
				ns = realloc(ns, n * sizeof(N));
			}
			ns[i] = next(ns[i - 1]);
			++i;
		}
#endif
		draw(w, h, ns, i);
#ifdef THREADED
		pthread_mutex_unlock(&mutex);
#endif
		EndDrawing();
	}

	CloseWindow();
}
