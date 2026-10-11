# Toy Kyber

An educational public-key encryption project written in C and inspired by
Kyber/ML-KEM. It implements the main ideas with small, readable components so
the polynomial arithmetic and encryption flow are easier to study.

> **Warning:** This is a learning project, not a standards-compliant or
> production-safe implementation of Kyber/ML-KEM. Do not use it to protect
> real data.

## Implemented Features

- Polynomial arithmetic in `Z_q[x] / (x^N + 1)`
- Negacyclic polynomial multiplication
- Polynomial vector and matrix operations
- Toy pseudo-random number generator and coefficient sampling
- 32-byte message encoding and decoding
- Key generation, encryption, and decryption
- Round-trip testing across 100 deterministic seeds
- Warning-enabled and sanitizer-enabled builds

Current toy parameters:

```text
N = 256
Q = 3329
K = 2
```

## Project Structure

```text
params.h        Shared parameters
prng.h/.c       Toy pseudo-random number generator
poly.h/.c       Polynomial arithmetic and message conversion
polyvec.h/.c    Polynomial vector and matrix operations
indcpa.h/.c     Key generation, encryption, and decryption
main.c          100-seed round-trip test
Makefile        Build, run, sanitizer, and cleanup targets
```

## Build and Run

```bash
make
make run
```

Expected output:

```text
PASS: 100 seeds
```

Run with AddressSanitizer and UndefinedBehaviorSanitizer:

```bash
make sanitize
```

Remove generated build files:

```bash
make clean
```
