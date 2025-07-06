#ifndef FPS
#define FPS 0
#endif

#ifdef THREADED
#include "../lib/thread.c"
#else
#include "../lib/primes.c"
#endif

#include <math.h>
#include <raylib.h>

typedef long double F;

#define FIT 0

#ifdef RGB
Color col(N n) {
	const unsigned char a = 0xf0, c = n % 0xff;
	switch ((n / 0xff) % 3) {
	case 0:
		return (Color){0xff - c, c, 0, a};
	case 1:
		return (Color){0, 0xff - c, c, a};
	case 2:
		return (Color){c, 0, 0xff - c, a};
	}
	return WHITE;
}
#else
const Color COL = {0xff, 0xff, 0xff, 0xf0};
#endif

const Color BG = {0x00, 0x00, 0x00, 0x00};

void draw(F w, F h, const N* ns, const T n) {
	w /= 2.0;
	h /= 2.0;
	const F s = ns[n - 1];
#if FIT == 0
	const F l = sqrt(w * w + h * h);
#endif
#if FIT == 1
	const F l = w > h ? w : h;
#endif
#if FIT == 2
	const F l = w < h ? w : h;
#endif
	for (N i = 0; i < n; ++i) {
		const N r = ns[i];
#ifdef RGB
		const Color COL = col(r);
#endif
		DrawPixel(w + l * r * cos(r) / s, h + l * r * sin(r) / s, COL);
	}
}

int main(int argc, char** argv) {
	T i;
	N* ns;
#ifdef THREADED
	pthread_t t;
	pthread_create(&t, NULL, primecounter, NULL);
#else
	T n = 1;
	i = 1;
	ns = malloc(n * sizeof(N));
	ns[0] = 2;
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MOUSE_PASSTHROUGH);
	SetTargetFPS(FPS);
	int w = 256, h = w;
	InitWindow(w, h, "spiral");

	while (!WindowShouldClose()) {
		w = GetScreenWidth();
		h = GetScreenHeight();

		ClearBackground(BG);
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
