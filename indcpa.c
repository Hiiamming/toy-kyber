#include "indcpa.h"

void keygen(public_key *pk, secret_key *sk, prng *rng)
{
    polyvec e;

    polyvec_sample_small(&e, rng);
    polyvec_sample_small(&sk->s, rng);
    polymat_sample_uniform(&pk->A, rng);

    polymat_vec_mul(&pk->t, &pk->A, &sk->s);
    polyvec_add(&pk->t, &pk->t, &e);
}

void encrypt(ciphertext *ct, const public_key *pk,
             const uint8_t msg[32], prng *rng)
{
    poly mpoly;
    poly e2;
    polyvec r;
    polyvec e1;

    polyvec_sample_small(&r, rng);
    polyvec_sample_small(&e1, rng);
    poly_sample_small(&e2, rng);
    poly_frommsg(&mpoly, msg);

    polymat_transpose_vec_mul(&ct->u, &pk->A, &r);
    polyvec_add(&ct->u, &ct->u, &e1);

    polyvec_dot(&ct->v, &pk->t, &r);
    poly_add(&ct->v, &ct->v, &e2);
    poly_add(&ct->v, &ct->v, &mpoly);
}

void decrypt(uint8_t msg[32], const ciphertext *ct, const secret_key *sk)
{
    poly su;
    poly mpoly;

    polyvec_dot(&su, &sk->s, &ct->u);
    poly_sub(&mpoly, &ct->v, &su);
    poly_tomsg(msg, &mpoly);
}
