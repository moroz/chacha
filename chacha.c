#include "./chacha.h"
#include <stdio.h>
#include <string.h>

const uint32_t INITIALIZATION_CONSTANTS[4] = {
    0x61707865, // "expa" LE
    0x3320646e, // "nd 3" LE
    0x79622d32, // "2-by" LE
    0x6b206574, // "te k" LE
};

static void debug_state(ChaChaState *cc) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%08X ", cc->state[4 * i + j]);
    }
    printf("\n");
  }
  printf("\n");
}

void initialize_state(ChaChaState *cc, const uint8_t *key, const uint8_t *nonce,
                      uint32_t counter) {
  for (int i = 0; i < 4; i++) {
    cc->state[i] = INITIALIZATION_CONSTANTS[i];
  }

  for (int i = 0; i < 8; i++) {
    cc->state[i + 4] = ((uint32_t *)key)[i];
  }

  cc->state[12] = counter;

  for (int i = 0; i < 3; i++) {
    cc->state[i + 13] = ((uint32_t *)nonce)[i];
  }

  debug_state(cc);
}

#define ROTL32(value, shift) ((value << shift) | (value >> 32 - shift))

void quarter_round(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
  *a = (*a + *b) & 0xFFFFFFFF;
  *d = *d ^ *a;
  *d = ROTL32(*d, 16);
  *c = (*c + *d) & 0xFFFFFFFF;
  *b = *b ^ *c;
  *b = ROTL32(*b, 12);
  *a = (*a + *b) & 0xFFFFFFFF;
  *d = *d ^ *a;
  *d = ROTL32(*d, 8);
  *c = (*c + *d) & 0xFFFFFFFF;
  *b = *b ^ *c;
  *b = ROTL32(*b, 7);
}

#define QROUND(cc, a, b, c, d)                                                 \
  quarter_round(&cc->state[a], &cc->state[b], &cc->state[c], &cc->state[d])

void chacha20_round(ChaChaState *cc) {
  QROUND(cc, 0, 4, 8, 12);
  QROUND(cc, 1, 5, 9, 13);
  QROUND(cc, 2, 6, 10, 14);
  QROUND(cc, 3, 7, 11, 15);
  QROUND(cc, 0, 5, 10, 15);
  QROUND(cc, 1, 6, 11, 12);
  QROUND(cc, 2, 7, 8, 13);
  QROUND(cc, 3, 4, 9, 14);
}

void chacha20_block(ChaChaState *cc) {
  uint32_t initial_state[16];
  memcpy(initial_state, cc->state, sizeof(uint32_t) * 16);

  for (int i = 0; i < 10; i++) {
    chacha20_round(cc);
  }

  for (int i = 0; i < 16; i++) {
    cc->state[i] = (cc->state[i] + initial_state[i]) & 0xFFFFFFFF;
  }

  debug_state(cc);
}
