#include <stdio.h>
#include <stdint.h>
#include "poly.h"

int main() {
    // printf("%d\n", mod_q(3330));
    // printf("%d\n", mod_q(-1));
    // printf("%d\n", mod_q(3329));
    // printf("%d\n", mod_q(-3330));

    // int32_t a = 2000000; // 2 triệu
    // int32_t b = 2000000; // 2 triệu

    // int64_t x = a * b; // Kết quả mong muốn: 4 * 10^12 (vượt 32-bit nhưng vừa khít 64-bit)
    // printf("%ld\n", x);
    poly a;

    a.c[0] = 123;
    a.c[100] = 456;

    printf("%d\n", a.c[0]);
    printf("%d\n", a.c[100]);

    poly_zero(&a);

    printf("%d\n", a.c[0]);
    printf("%d\n", a.c[100]);



    return 0;
}