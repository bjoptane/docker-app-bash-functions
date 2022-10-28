
#include "md5.h"
#include "hash.h"
#include "utils.h"

static const uint32_t TT[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static inline uint32_t F(uint32_t B, uint32_t C, uint32_t D) {
    return (B & C) | (~B & D);
}

static inline uint32_t G(uint32_t B, uint32_t C, uint32_t D) {
    return (B & D) | (C & ~D);
}

static inline uint32_t H(uint32_t B, uint32_t C, uint32_t D) {
    return B ^ C ^ D;
}

static inline uint32_t I(uint32_t B, uint32_t C, uint32_t D) {
    return C ^ (B | ~D);
}

#define FF(A, B, C, D, X, T, S) A = B + _lshift(A + F(B, C, D) + X + T, S)
#define GG(A, B, C, D, X, T, S) A = B + _lshift(A + G(B, C, D) + X + T, S)
#define HH(A, B, C, D, X, T, S) A = B + _lshift(A + H(B, C, D) + X + T, S)
#define II(A, B, C, D, X, T, S) A = B + _lshift(A + I(B, C, D) + X + T, S)

void md5_blk_update(uint32_t hash[4], const uint8_t data[64]) {
    uint32_t W[16];
    for (int i = 0; i < 16; ++i) {
        W[i] = _load_le_u32(data + i * 4);
    }
    uint32_t A = hash[0];
    uint32_t B = hash[1];