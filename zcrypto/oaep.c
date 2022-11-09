
#include "sha256.h"
#include "oaep.h"

static void bytes2num(uint32_t *num, const uint8_t *bytes, size_t len) {
    for (size_t j = 0; j < len; j += 4) {
        size_t i = (len - j) / 4 - 1;
        num[i] = bytes[j];
        num[i] <<= 8; num[i] |= bytes[j + 1];
        num[i] <<= 8; num[i] |= bytes[j + 2];
        num[i] <<= 8; num[i] |= bytes[j + 3];
    }
}

static void num2bytes(uint8_t *bytes, const uint32_t *num, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        uint32_t x = num[i];
        size_t j = (len - 1 - i) * 4;
        bytes[j] = (x >> 24) & 0xff;
        bytes[j + 1] = (x >> 16) & 0xff;
        bytes[j + 2] = (x >> 8) & 0xff;
        bytes[j + 3] = (x) & 0xff;
    }
}


static void mgf1(uint8_t *mask, size_t mlen, const uint8_t *seed, size_t slen) {
    uint32_t cnt[1] = {0};
    uint8_t bb[4] = {0};
    sha256_ctx_t ctx;
    for (uint32_t i = 0; i < mlen / HASH_BYTES; ++i) {
        num2bytes(bb, cnt, 1);
        sha256_init(&ctx);
        sha256_update(&ctx, seed, slen);
        sha256_update(&ctx, bb, 4);
        sha256_digest(&ctx, mask + HASH_BYTES * i);
        ++cnt[0];
    }
    size_t r = mlen % HASH_BYTES;
    if (r != 0) {
        uint8_t hh[HASH_BYTES] = {0};
        num2bytes(bb, cnt, 1);
        sha256_init(&ctx);
        sha256_update(&ctx, seed, slen);
        sha256_update(&ctx, bb, 4);
        sha256_digest(&ctx, hh);
        memcpy(mask + mlen / HASH_BYTES * HASH_BYTES, hh, r);
    }
}

static inline void _xor(uint8_t *src, const uint8_t *dst, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        src[i] ^= dst[i];
    }
}

static const uint8_t EMPTY_LABLE_HASH[HASH_BYTES] = {
    0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14, 0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
    0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c, 0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55,
};

/*
OAEP padding: https://tools.ietf.org/html/rfc8017

                    +----------+------+--+-------+
               DB = |  lHash   |  PS  |01|   M   |
                    +----------+------+--+-------+
                                   |
         +----------+              |
         |   seed   |              |
         +----------+              |
               |                   |
               |-------> MGF ---> xor
               |                   |
      +--+     V                   |
      |00|    xor <----- MGF <-----|