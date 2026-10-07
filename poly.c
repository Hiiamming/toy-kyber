#include "poly.h"
#include <stdint.h>

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
