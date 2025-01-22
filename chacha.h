#ifndef CHACHA_H
#define CHACHA_H

#include <stdint.h>

#define KEY_SIZE 32
#define NONCE_SIZE 12
#define COUNTER_SIZE 4
#define BLOCK_SIZE 64

extern const uint32_t INITIALIZATION_CONSTANTS[4];

typedef struct ChaChaState {
  uint32_t state[16];
} ChaChaState;

void initialize_state(ChaChaState *cc, const uint8_t *key, const uint8_t *nonce,
                      uint32_t counter);

#endif
