#ifndef POLY_H
#define POLY_H

#include <stdint.h>

#define N 256
#define Q 3329
#define K 2

typedef struct{ 
    int16_t c[N];
} poly;

int16_t mod_q(int64_t x);
void poly_zero(poly *p);
void poly_add(poly *r, const poly *a, const poly *b);
void poly_sub(poly *r, const poly *a, const poly *b);

#endif



