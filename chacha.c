#include "./chacha.h"

const uint32_t INITIALIZATION_CONSTANTS[4] = {
    0x61707865, // "expa" LE
    0x3320646e, // "nd 3" LE
    0x79622d32, // "2-by" LE
    0x6b206574, // "te k" LE
};
