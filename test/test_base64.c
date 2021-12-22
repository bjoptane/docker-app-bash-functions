#include <stdint.h>
#include <stdio.h>
#include "zcrypto/base64.h"

static inline uint8_t hex2num(char c) {
    if (c >= 'a') {
        return (uint8_t)(c - 'a' + 10);
    } else {
        return (uint8_