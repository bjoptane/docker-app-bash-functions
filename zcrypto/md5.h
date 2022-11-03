#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

typedef struct {
    uint64_t len;
    uint32_t hash[4];
    uint8_t blk[64];
} md5_ctx_t;

void md5_init(md5_ctx_t *ctx);
void md5_updat