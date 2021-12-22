#include <stdint.h>
#include <stdio.h>
#include "zcrypto/base64.h"

static inline uint8_t hex2num(char c) {
    if (c >= 'a') {
        return (uint8_t)(c - 'a' + 10);
    } else {
        return (uint8_t)(c - '0');
    }
}

static size_t hex_decode(const char *text, uint8_t *bin) {
    const char *p = text;
    uint8_t *bb   = bin;
    do {
        uint8_t x = hex2num(*p++);
        uint8_t y = hex2num(*p++);
        *bb++     = (uint8_t)