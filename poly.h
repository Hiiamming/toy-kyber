#ifndef POLY_H
#define POLY_H

#include <stdint.h>

#define N 256
#define Q 3329
#define K 2

// invariant:
// every stored coefficient satisfies
// 0 <= c[i] < Q
typedef struct{ 
    int16_t c[N];
} poly;

typedef struct {
    uint32_t state;
} prng;

typedef struct {
    poly v[K];
} polyvec;

typedef struct {
    poly m[K][K];
} polymat;

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

int16_t mod_q(int64_t x);
void poly_zero(poly *p);
void poly_set_coeff(poly *p, int i, int64_t x);
void poly_add(poly *r, const poly *a, const poly *b);
void poly_sub(poly *r, const poly *a, const poly *b);
void poly_mul(poly *r, const poly *a, const poly *b);
void prng_init(prng *rng, uint32_t seed);
uint32_t prng_next(prng *rng);
void poly_sample_small(poly *p, prng *rng);
void poly_sample_uniform(poly *p, prng *rng);

void polyvec_zero(polyvec *v);
void polyvec_sample_small(polyvec *v, prng *rng);
void keygen(public_key *pk, secret_key *sk, prng *rng);
void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b);
void polyvec_sub(polyvec *r, const polyvec *a, const polyvec *b);
void polyvec_dot(poly *r, const polyvec *a, const polyvec *b);

void polymat_vec_mul(polyvec *r, const polymat *A, const polyvec *v);
void polymat_transpose_vec_mul(polyvec *r, const polymat *A, const polyvec *v);
void polymat_sample_uniform(polymat *A, prng *rng);

void poly_frommsg(poly *p, const uint8_t msg[32]);
void poly_tomsg(uint8_t msg[32], const poly *p);

void encrypt(ciphertext *ct, const public_key *pk, const uint8_t msg[32], prng *rng);
void decrypt(uint8_t msg[32],
             const ciphertext *ct,
             const secret_key *sk);

#endif



