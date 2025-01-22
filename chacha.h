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

void quarter_round(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);
void chacha20_round(ChaChaState *cc);
void chacha20_block(ChaChaState *cc);

#endif
