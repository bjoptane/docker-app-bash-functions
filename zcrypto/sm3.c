#include "sm3.h"
#include "hash.h"
#include "utils.h"

#define T0 0x79cc4519ul
#define T1 0x7a879d8aul

static inline uint32_t _p0(uint32_t x) {
    return x ^ _lshift(x, 9) ^ _lshift(x, 17);
}

static inline uint32_t _p1(uint32_t x) {
    return x ^ _lshift(x, 15) ^ _lshift(x, 23);
}

static inline uint32_t _ff0(uint32_t x, uint32_t y, uint32_t z) {
    return x ^ y ^ z;
}

static inline uint32_t _ff1(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) | (x & z) | (y & z);
}

static inline uint32_t _gg0(uint32_t x, uint32_t y, uint32_t z) {
    return x ^ y ^ z;
}

static inline uint32_t _gg1(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) | ((~x) & z);
}

#define CF(A, B, C, D, E, F, G, H, TT, FF, GG, i) \
do { \
    uint32_t SS1 = _lshift(_lshift(A, 12) + E + _lshift(TT, i % 32), 7); \
    uint32_t SS2 = SS1 ^ _lshift(A, 12); \
    uint32_t TT1 = FF(A, B, C) + D + SS2 + (W[i] ^ W[i + 4]);  /* W'(j) = W(j) ^ W(j + 4) */ \
    uint32_t TT2 = GG(E, F, G) + H + SS1 + W[i