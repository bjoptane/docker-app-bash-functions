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
        *bb++     = (uint8_t)((x << 4) | y);
    } while (*p != '\n');
    return (size_t)(bb - bin);
}

#define NUM 1000
char line[NUM * 2 + 8];  // reserve space for prefix and tail '\n\0'
uint8_t binary[NUM + 4];
uint8_t binary2[NUM + 4];
uint8_t text[NUM * 4 / 3 + 8];

int main() {
    size_t xl1 = 0, xl2 = 0;
    int cnt = 0, err1 = 0, err2 = 0;
    for (;;) {
        if (feof(stdin)) {
            break;
        }
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        if (line[0] == 'H') {