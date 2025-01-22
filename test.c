#include "chacha.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdbool.h>

const uint8_t test_key[KEY_SIZE] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

const uint8_t test_nonce[NONCE_SIZE] = {0x00, 0x00, 0x00, 0x09, 0x00, 0x00,
                                        0x00, 0x4a, 0x00, 0x00, 0x00, 0x00};

void test_initialize_block(void) {
  ChaChaState state;
  initialize_state(&state, test_key, test_nonce, 1);

  uint32_t expected_state[16] = {
      0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 0x03020100, 0x07060504,
      0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
      0x00000001, 0x09000000, 0x4a000000, 0x00000000,
  };

  for (int i = 0; i < 16; i++) {
    CU_ASSERT(state.state[i] == expected_state[i]);
  }

  chacha20_block(&state);
}

int main() {
  CU_initialize_registry();

  CU_pSuite suite = CU_add_suite("ChaChaRoundSuite", 0, 0);
  CU_add_test(suite, "test of initialize_block()", test_initialize_block);

  CU_basic_run_tests();
  CU_cleanup_registry();
  return 0;
}
