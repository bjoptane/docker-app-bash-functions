#include "sm3.h"
#include "hash.h"
#include "utils.h"

#define T0 0x79cc4519ul
#define T1 0x7a879d8aul

static inline uint32_t _p0(uint32_t x) {
    return x ^ _lshift(x, 9) ^ _lshift(