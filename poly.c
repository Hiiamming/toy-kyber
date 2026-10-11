#include "poly.h"
#include <stdint.h>
#include <string.h>

int16_t mod_q(int64_t x) {
    x %= Q;
    
    if (x < 0) {
        x += Q;
    }

    return (int16_t)x;
}

void poly_zero(poly *p) {
    for (int i = 0; i < N; i++) {
        p->c[i] = 0;
    }
    // memset(p, 0, sizeof(poly));
}

void poly_set_coeff(poly *p, int i, int64_t x)
{
    p->c[i] = mod_q(x);
}

void poly_add(poly *r, const poly *a, const poly *b) {
    for (int i = 0; i < N; i ++) {
        r->c[i] = mod_q(a->c[i] + b->c[i]);
    }
}


void poly_sub(poly *r, const poly *a, const poly *b) {
    for (int i = 0; i < N; i ++) {
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
            }
            else {
                tmp[d] += (int64_t)a->c[i] * b->c[j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        r->c[i] = mod_q(tmp[i]);
    }
}

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

void poly_sample_small(poly *p, prng *rng) {
    for (int i = 0; i < N; i++) {
        int x = prng_next(rng) % 3;
        x -= 1;

        p->c[i] = (int16_t)x;
    }
}

void poly_sample_uniform(poly *p, prng *rng) {
    for (int i = 0; i < N; i++) {
        int x = prng_next(rng) % Q;
        p->c[i] = (int16_t)x;
    }
}

void polyvec_zero(polyvec *v) {
    for (int i = 0; i < K; i++) {
        poly_zero(&v->v[i]);
    }
}

void polyvec_sample_small(polyvec *v, prng *rng) {
    for (int i = 0; i < K; i++) {
        poly_sample_small(&v->v[i], rng);
    }
}

void polymat_sample_uniform(polymat *A, prng *rng) {
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            poly_sample_small(&A->m[i][j], rng);
        }
    }
}

void polymat_vec_mul(polyvec *r, const polymat *A, const polyvec *v) {
    poly tmp2;
    polyvec tmp1 = *v;

    polyvec_zero(r);

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            poly_mul(&tmp2, &A->m[i][j], &tmp1.v[j]);
            poly_add(&r->v[i], &r->v[i], &tmp2);
        }
    }
}

void polymat_transpose_vec_mul(polyvec *r, const polymat *A, const polyvec *v) {
    poly tmp2;
    polyvec tmp1 = *v;

    polyvec_zero(r);

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            poly_mul(&tmp2, &A->m[j][i], &tmp1.v[j]);
            poly_add(&r->v[i], &r->v[i], &tmp2);
        }
    }
}

void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b) {
    for (int i = 0; i < K; i++) {
        poly_add(&r->v[i], &a->v[i], &b->v[i]);
    }
}

void polyvec_sub(polyvec *r, const polyvec *a, const polyvec *b) {
    for (int i = 0; i < K; i++) {
        poly_sub(&r->v[i], &a->v[i], &b->v[i]);
    }
}

void polyvec_dot(poly *r, const polyvec *a, const polyvec *b) {
    polyvec tmp_a = *a;
    polyvec tmp_b = *b;

    poly tmp;

    poly_zero(r);

    for (int i = 0l; i < K; i++) {
        poly_mul(&tmp, &tmp_a.v[i], &tmp_b.v[i]);
        poly_add(r, r, &tmp);
    }
}

void keygen(public_key *pk, secret_key *sk, prng *rng) {
    polyvec e;

    polyvec_sample_small(&e, rng);
    polyvec_sample_small(&sk->s, rng);
    polymat_sample_uniform(&pk->A, rng);

    polymat_vec_mul(&pk->t, &pk->A, &sk->s);
    polyvec_add(&pk->t, &pk->t, &e);

}

void poly_frommsg(poly *p, const uint8_t msg[32]) {
    for (int i = 0; i < N; i++) {
        int bit = (msg[i / 8] >> (i % 8)) & 1;
        
        if (bit) {
            p->c[i] = (Q+1) / 2;
        }

        else {
            p->c[i] = 0;
        }
    }
}

void poly_tomsg(uint8_t msg[32], const poly *p) {
    memset(msg, 0, 32);

    for (int i = 0 ; i < N; i++) {
        int x = mod_q(p->c[i]);

        int bit = ((2 * x + Q / 2) / Q) & 1;
        msg[i / 8] |= bit << (i % 8);
    }
}

void encrypt(ciphertext *ct, const public_key *pk, const uint8_t msg[32], prng *rng) {
    poly mpoly;
    poly e2;
    polyvec r;
    polyvec e1;
    
    polyvec_sample_small(&r, rng);
    polyvec_sample_small(&e1, rng);
    poly_sample_small(&e2, rng);
    poly_frommsg(&mpoly, msg);

    // u = A.T * r + e1
    polymat_transpose_vec_mul(&ct->u, &pk->A, &r);
    polyvec_add(&ct->u, &ct->u, &e1);

    // v = t.T * r + e2 + m
    polyvec_dot(&ct->v, &pk->t, &r);
    poly_add(&ct->v, &ct->v, &e2);
    poly_add(&ct->v, &ct->v, &mpoly);
}

void decrypt(uint8_t msg[32], const ciphertext *ct, const secret_key *sk) {
    // m' = v - s.T * u
    poly su;
    poly mpoly;

    polyvec_dot(&su, &sk->s, &ct->u);
    poly_sub(&mpoly, &ct->v, &su);

    poly_tomsg(msg, &mpoly);

}
