
#include "sha1.h"
#include "hash.h"
#include "utils.h"

static inline uint32_t _f0(uint32_t B, uint32_t C, uint32_t D) {
    return (B & C) | (~B & D);
}

static inline uint32_t _f1(uint32_t B, uint32_t C, uint32_t D) {
    return B ^ C ^ D;
}

static inline uint32_t _f2(uint32_t B, uint32_t C, uint32_t D) {
    return (B & C) | (B & D) | (C & D);
}

static inline uint32_t _f3(uint32_t B, uint32_t C, uint32_t D) {
    return B ^ C ^ D;
}

#define K0 0x5a827999ul
#define K1 0x6ed9eba1ul
#define K2 0x8f1bbcdcul
#define K3 0xca62c1d6ul

void sha1_blk_update(uint32_t hash[5], const uint8_t data[64]) {
    uint32_t W[80];
    for (int i = 0; i < 16; ++i) {
        W[i] = _load_be_u32(data + i * 4);
    }
    for (int i = 16; i < 80; ++i) {
        W[i] = _lshift(W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16], 1);
    }
    uint32_t A = hash[0];
    uint32_t B = hash[1];
    uint32_t C = hash[2];
    uint32_t D = hash[3];
    uint32_t E = hash[4];

    #define ROUND(N, i) do { \
        uint32_t temp = _lshift(A, 5) + _f##N(B, C, D) + E + W[i] + K##N; \
        E = D; \
        D = C; \
        C = _lshift(B, 30); \
        B = A; \
        A = temp; \
    } while (0)

    for (int i = 0; i < 20; ++i) {
        ROUND(0, i);
    }
    for (int i = 20; i < 40; ++i) {
        ROUND(1, i);
    }
    for (int i = 40; i < 60; ++i) {
        ROUND(2, i);
    }
    for (int i = 60; i < 80; ++i) {
        ROUND(3, i);
    }

    #undef ROUND

    hash[0] += A;
    hash[1] += B;
    hash[2] += C;