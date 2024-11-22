#include "../lib/primes.c"

#include <limits.h>
#include <math.h>
#include <raylib.h>

const Color col(N n) {
  const unsigned char a = 0xf0, c = n % UCHAR_MAX;
  switch ((n / UCHAR_MAX) % 3) {
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

void draw(F w, F h, const N *ns, const N n) {
  w /= 2.0;
  h /= 2.0;
  const F s = ns[n - 1], l = w > h ? w : h;
  for (N i = 0; i < n; ++i) {
    const N r = ns[i];
    DrawCircle(w + l * r * cos(r) / s, h + l * r * sin(r) / s, 2, col(r));
  }
}

const int main(int argc, char *argv[]) {
  N i = 1000, n = i;
  N *ns = primes(2, n);
  if (!ns)
    return 1;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  int w = 256, h = w;
  InitWindow(w, h, "spiral");

  while (!WindowShouldClose()) {
    w = GetScreenWidth();
    h = GetScreenHeight();

    ClearBackground(BLACK);
    BeginDrawing();
    draw(w, h, ns, i);
    if (!IsKeyDown(KEY_SPACE)) {
      if (i >= n) {
        n *= 2;
        ns = realloc(ns, n * sizeof(N));
        if (!ns)
          return 1;
      }
      ns[i] = next(ns[i - 1]);
      ++i;
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
