#include <stdio.h>
#include <stdint.h>
#include "poly.h"

int main() {
    poly a, b, r;

    poly_zero(&a);
    poly_zero(&b);

    a.c[0] = 3000;
    a.c[1] = 100;

    b.c[0] = 1000;
    b.c[1] = 200;

    poly_add(&r, &a, &b);

    printf("%d %d\n", r.c[0], r.c[1]);

    poly_sub(&r, &a, &b);

    printf("%d %d\n", r.c[0], r.c[1]);

    // expected:
    // 671 300
    // 2000 3229


    return 0;
}