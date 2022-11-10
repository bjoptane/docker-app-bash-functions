
#include <string.h>
#include "rsa.h"
#include "utils.h"

#define DEBUG_DUMP 0
#if DEBUG_DUMP
#include <stdio.h>

static void _debug(const char *name, const uint32_t *data, size_t len) {
    static char text[RSA_BYTES * 2 + 2];
    for (size_t i = 0; i < len; ++i) {
        size_t j = (len - 1 - i) * 8;
        uint32_t x = data[i];
        text[j] = _hex((x >> 28) & 0xf);
        text[j + 1] = _hex((x >> 24) & 0xf);
        text[j + 2] = _hex((x >> 20) & 0xf);
        text[j + 3] = _hex((x >> 16) & 0xf);
        text[j + 4] = _hex((x >> 12) & 0xf);
        text[j + 5] = _hex((x >> 8) & 0xf);
        text[j + 6] = _hex((x >> 4) & 0xf);
        text[j + 7] = _hex(x & 0xf);
    }
    text[len * 8] = '\0';
    printf("%s = 0x%s\n", name, text);
}
#else
#define _debug(...)
#endif

typedef union {
    uint64_t u64;
    struct {
#if __ZCRYPO_BYTE_ORDER__ == 1
        uint32_t low;
        uint32_t high;
#elif __ZCRYPO_BYTE_ORDER__ == 2
        uint32_t high;
        uint32_t low;
#else
    #error Unknown endianness, please define __ZCRYPO_BYTE_ORDER__ to 1(little endian) or 2(big endian)
    // #define __ZCRYPO_BYTE_ORDER__ 1
    // #define __ZCRYPO_BYTE_ORDER__ 2