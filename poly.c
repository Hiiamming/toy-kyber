#include "poly.h"

#include <string.h>

int16_t mod_q(int64_t x)
{
    x %= Q;

    if (x < 0) {
        x += Q;
    }

    return (int16_t)x;
}

void poly_zero(poly *p)
{
    for (int i = 0; i < N; i++) {
        p->c[i] = 0;
    }
}

void poly_set_coeff(poly *p, int i, int64_t x)
{
    p->c[i] = mod_q(x);
}

void poly_add(poly *r, const poly *a, const poly *b)
{
    for (int i = 0; i < N; i++) {
        r->c[i] = mod_q(a->c[i] + b->c[i]);
    }
}

void poly_sub(poly *r, const poly *a, const poly *b)
{
    for (int i = 0; i < N; i++) {
        r->c[i] = mod_q(a->c[i] - b->c[i]);
    }
}

void poly_mul(poly *r, const poly *a, const poly *b)
{
    int64_t tmp[N] = {0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int d = i + j;

            if (d >= N) {
                d -= N;
                tmp[d] -= (int64_t)a->c[i] * b->c[j];
            } else {
                tmp[d] += (int64_t)a->c[i] * b->c[j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        r->c[i] = mod_q(tmp[i]);
    }
}

void poly_sample_small(poly *p, prng *rng)
{
    for (int i = 0; i < N; i++) {
        int x = (int)(prng_next(rng) % 3);
        x -= 1;
        p->c[i] = (int16_t)x;
    }
}

void poly_sample_uniform(poly *p, prng *rng)
{
    for (int i = 0; i < N; i++) {
        int x = (int)(prng_next(rng) % Q);
        p->c[i] = (int16_t)x;
    }
}

void poly_frommsg(poly *p, const uint8_t msg[32])
{
    for (int i = 0; i < N; i++) {
        int bit = (msg[i / 8] >> (i % 8)) & 1;
        p->c[i] = bit ? (Q + 1) / 2 : 0;
    }
}

void poly_tomsg(uint8_t msg[32], const poly *p)
{
    memset(msg, 0, 32);

    for (int i = 0; i < N; i++) {
        int x = mod_q(p->c[i]);
        int bit = ((2 * x + Q / 2) / Q) & 1;
        msg[i / 8] |= (uint8_t)(bit << (i % 8));
    }
}
