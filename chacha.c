#include "./chacha.h"
#include <stdio.h>

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
