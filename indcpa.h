#ifndef INDCPA_H
#define INDCPA_H

#include <stdint.h>

#include "prng.h"
#include "poly.h"
#include "polyvec.h"

typedef struct {
    polymat A;
    polyvec t;
} public_key;

typedef struct {
    polyvec s;
} secret_key;

typedef struct {
    polyvec u;
    poly v;
} ciphertext;

void keygen(public_key *pk, secret_key *sk, prng *rng);
void encrypt(ciphertext *ct, const public_key *pk, const uint8_t msg[32], prng *rng);
void decrypt(uint8_t msg[32], const ciphertext *ct, const secret_key *sk);

#endif


