// Copyright 2025 William Stafford Parsons

#include <stddef.h>
#include <stdint.h>

struct wavedrift_state {
  uint64_t elements[16];
  uint64_t a;
  uint64_t b;
};

void wavedrift(struct wavedrift_state *s) {
  uint64_t mix[2] = {
    s->elements[7],
    s->elements[15]
  };
  size_t i = 0;
  size_t j;
  size_t k = 0;

  s->a += 11111111111111111;

  while (i < 2) {
    s->b += s->a;
    mix[i] += (s->b << 23) | (s->b >> 41);
    j = 0;

    while (j < 4) {
      s->elements[k] += (mix[i] << 51) | (mix[i] >> 13);
      s->elements[k] ^= s->b;
      s->elements[k + 1] += (mix[i] << 27) | (mix[i] >> 37);
      mix[i] += s->elements[k];
      j++;
      k += 2;
    }

    i++;
  }

  s->elements[7] += mix[0];
  s->b ^= mix[1];
}
