#include "polyvec.h"

void polyvec_zero(polyvec *v)
{
    for (int i = 0; i < K; i++) {
        poly_zero(&v->v[i]);
    }
}

void polyvec_sample_small(polyvec *v, prng *rng)
{
    for (int i = 0; i < K; i++) {
        poly_sample_small(&v->v[i], rng);
    }
}

void polymat_sample_uniform(polymat *A, prng *rng)
{
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            poly_sample_small(&A->m[i][j], rng);
        }
    }
}

void polymat_vec_mul(polyvec *r, const polymat *A, const polyvec *v)
{
    poly tmp;
    polyvec input = *v;

    polyvec_zero(r);

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            poly_mul(&tmp, &A->m[i][j], &input.v[j]);
            poly_add(&r->v[i], &r->v[i], &tmp);
        }
    }
}

void polymat_transpose_vec_mul(polyvec *r, const polymat *A,
                               const polyvec *v)
{
    poly tmp;
    polyvec input = *v;

    polyvec_zero(r);

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            poly_mul(&tmp, &A->m[j][i], &input.v[j]);
            poly_add(&r->v[i], &r->v[i], &tmp);
        }
    }
}

void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b)
{
    for (int i = 0; i < K; i++) {
        poly_add(&r->v[i], &a->v[i], &b->v[i]);
    }
}

void polyvec_sub(polyvec *r, const polyvec *a, const polyvec *b)
{
    for (int i = 0; i < K; i++) {
        poly_sub(&r->v[i], &a->v[i], &b->v[i]);
    }
}

void polyvec_dot(poly *r, const polyvec *a, const polyvec *b)
{
    polyvec input_a = *a;
    polyvec input_b = *b;
    poly tmp;

    poly_zero(r);

    for (int i = 0; i < K; i++) {
        poly_mul(&tmp, &input_a.v[i], &input_b.v[i]);
        poly_add(r, r, &tmp);
    }
}
