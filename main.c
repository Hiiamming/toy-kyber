#include "indcpa.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    for (uint32_t seed = 1; seed <= 100; seed++) {
        uint8_t msg[32];
        uint8_t out[32];

        public_key pk;
        secret_key sk;
        ciphertext ct;
        prng rng;

        for (int i = 0; i < 32; i++) {
            msg[i] = (uint8_t)(i * 37 + seed);
        }

        prng_init(&rng, seed);
        keygen(&pk, &sk, &rng);
        encrypt(&ct, &pk, msg, &rng);
        decrypt(out, &ct, &sk);

        if (memcmp(msg, out, 32) != 0) {
            printf("FAIL at seed %u\n", seed);
            return 1;
        }
    }

    printf("PASS: 100 seeds\n");
    return 0;
}
