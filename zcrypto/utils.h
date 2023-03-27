#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#if defined(__BYTE_ORDER__)
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define __ZCRYPO_BYTE_ORDER__ 1
    #else
        #define __ZCRYPO_BYTE_ORDER__ 2
    #endif
#else
    #error Unknown endianness, please define __ZCRYPO_BYTE_ORDER__ to 1(little endian) or 2(big endian)
    // #define __ZCRYPO_BYTE_ORDER__ 1
    // #define __ZCRYPO_BYTE_ORDER__ 2
#endif


#if __ZCRYPO_BYTE_ORDER__ == 1

static inline uint32_t _load_le_u32(const uint8_t bs[4]) {
    return *(uint32_t*)bs;
}

static inline uint32_t _load_be_u32(const uint8_t bs[4]) {
    return ((uint32_t)bs[0] << 24) | ((uint32_t)bs[1] << 16) | ((uint32_t)bs[2] << 8) | bs[3];
}

static inline void _store_le_u32(const uint32_t x, uint8_t bs[4]) {
    *(uint32_t*)bs = x;
}

static inline void _store_be_u32(const uint32_t x, uint8_t bs[4]) {
    bs[0] = (x >> 24) & 0xff;
    bs[1] = (x >> 16) & 0xff;
    bs[2] = (x >> 8) & 0xff;
    bs[3] = (x) & 0xff;
}

static inline void _store_le_u64(const uint64_t x, uint8_t bs[8]) {
    *(uint64_t*)bs = x;
}

static inline void _store_be_u64(const uint64_t x, uint8_t bs[8]) {
    bs[0] = (x >> 56) & 0xff;
    bs[1] = (x >> 48) & 0xff;
    bs[2] = (x >> 40) & 0xff;
    bs[3] = (x >> 32) & 0xff;
    bs[4] = (x >> 24) & 0xff;
    bs[5] = (x >> 16) & 0xff;
    bs[6] = (x >> 8) & 0xff;
    bs[7] = (x) & 0xff;
}

#else

static inline uint32_t _load_le_u32(const uint8_t bs[4]) {
    return ((uint32_t)bs[3] << 24) | ((uint32_t)bs[2] << 16) | ((uint32_t)bs[1] << 8) | bs[0];
}

static inline uint32_t _load_be_u32(const uint8_t bs[4]) {
    return *(uint32_t*)bs;
}

static inline void _store_le_u32(const uint32_t x, uint8_t bs[4]) {
    bs[3] = (x >> 24) & 0xff;
    bs[2] = (x >> 16) & 0xff;
    bs[1] = (x >> 8) & 0xff;
    bs[0] = (x) & 0xff;
}

static inline void _store_be_u32(const uint32_t x, uint8_t bs[4]) {
    *(uint32_t*)bs = x;
}

static inline void _store_le_u64(const uint64_t x, uint8_t bs[8]) {
    bs[7] = (x >> 56) & 0xff;
    bs[6] = (x >> 48) & 0xff;
    bs[5] = (x >> 40) & 0xff;
    bs[4] = (x >> 32) & 0xff;
    bs[3] = (x >> 24) & 0xff;
    bs[2] = (x >> 16) & 0xff;
    bs[1] = (x >> 8