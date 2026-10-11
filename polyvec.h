#ifndef POLYVEC_H
#define POLYVEC_H

#include "poly.h"
#include "prng.h"

typedef struct {
    poly v[K];
} polyvec;

typedef struct {
    poly m[K][K];
} polymat;

void polyvec_zero(polyvec *v);
void polyvec_sample_small(polyvec *v, prng *rng);

void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b);
void polyvec_sub(polyvec *r, const polyvec *a, const polyvec *b);
void polyvec_dot(poly *r, const polyvec *a, const polyvec *b);

void polymat_vec_mul(polyvec *r, const polymat *A, const polyvec *v);
void polymat_transpose_vec_mul(polyvec *r, const polymat *A, const polyvec *v);
void polymat_sample_uniform(polymat *A, prng *rng);

#endif