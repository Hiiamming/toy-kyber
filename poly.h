#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "params.h"
#include "prng.h"


// invariant:
// every stored coefficient satisfies
// 0 <= c[i] < Q
typedef struct{ 
    int16_t c[N];
} poly;

int16_t mod_q(int64_t x);
void poly_zero(poly *p);
void poly_set_coeff(poly *p, int i, int64_t x);
void poly_add(poly *r, const poly *a, const poly *b);
void poly_sub(poly *r, const poly *a, const poly *b);
void poly_mul(poly *r, const poly *a, const poly *b);

void poly_sample_small(poly *p, prng *rng);
void poly_sample_uniform(poly *p, prng *rng);



void poly_frommsg(poly *p, const uint8_t msg[32]);
void poly_tomsg(uint8_t msg[32], const poly *p);



#endif



