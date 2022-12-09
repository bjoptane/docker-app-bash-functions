#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

typedef struct {
    uint64_t len;
    uint32_t hash[8];
    uint8_t blk[64];
