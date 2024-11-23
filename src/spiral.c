#ifdef THREADED
#include "../lib/thread.c"
#else
#include "../lib/primes.c"
#endif

#include <math.h>
#include <raylib.h>

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
#ifdef THREADED
  pthread_t t;
  if (pthread_create(&t, NULL, primecounter, NULL) != 0)
    return EXIT_FAILURE;
  T i;
  N *ns;
#else
  T i = 1, n = i;
  N *ns = primes(2, n);
#endif

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(64);
  int w = 256, h = w;
  InitWindow(w, h, "spiral");

  while (!WindowShouldClose()) {
    w = GetScreenWidth();
    h = GetScreenHeight();

    ClearBackground(BLACK);
    BeginDrawing();

#ifdef THREADED
    pthread_mutex_lock(&mutex);
    ns = primecount;
    i = primescount;
#else
    if (!IsKeyDown(KEY_SPACE)) {
      if (i >= n) {
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
