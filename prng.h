#ifndef PRNG_H
#define PRNG_H
#include <stdint.h>


typedef struct {
    uint32_t state;
} prng;

void prng_init(prng *rng, uint32_t seed);
uint32_t prng_next(prng *rng);

#endif