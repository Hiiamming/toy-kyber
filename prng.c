#include "prng.h"

void prng_init(prng *rng, uint32_t seed)
{
    rng->state = seed ? seed : 1;
}

uint32_t prng_next(prng *rng)
{
    uint32_t x = rng->state;

    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    rng->state = x;
    return x;
}
