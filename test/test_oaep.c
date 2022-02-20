
#include <stdio.h>
#include <time.h>
#include "zcrypto/oaep.h"
#include "zcrypto/utils.h"

static void hex_dump(const char *name, const uint8_t *data, size_t len) {
    static char text[RSA_BYTES * 2 + 2];
    for (size_t i = 0; i < len; ++i) {
        uint8_t x = data[i];
        text[i * 2] = _hex((x >> 4) & 0xf);
        text[i * 2 + 1] = _hex(x & 0xf);
    }
    text[len * 2] = '\0';
    printf("%s: %s\n", name, text);
}

static inline uint32_t hex2num(char c) {
    if (c >= 'a') {
        return (uint32_t)(c - 'a' + 10);
    } else {
        return (uint32_t)(c - '0');
    }
}

static void str2bignum(uint32_t n[RSA_SIZE], const char *text) {
    for (size_t i = 0; i < RSA_SIZE; ++i) {
        size_t j = (RSA_SIZE - 1 - i) * 8;
        uint32_t x = hex2num(text[j]);
        x <<= 4; x |= hex2num(text[j + 1]);
        x <<= 4; x |= hex2num(text[j + 2]);
        x <<= 4; x |= hex2num(text[j + 3]);
        x <<= 4; x |= hex2num(text[j + 4]);
        x <<= 4; x |= hex2num(text[j + 5]);
        x <<= 4; x |= hex2num(text[j + 6]);
        x <<= 4; x |= hex2num(text[j + 7]);
        n[i] = x;
    }
}

static const char * find_start(const char *text) {
    const char *p = text;
    while (*p != 'x') {
        ++p;
    }
    ++p;
    return p;
}

int main() {
    rsa_ctx_t rsa;
    char line[RSA_BITS / 4 + 32];
    for (;;) {
        if (feof(stdin)) {
            break;
        }
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }