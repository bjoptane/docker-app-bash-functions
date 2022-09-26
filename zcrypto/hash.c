#include <assert.h>
#include "hash.h"
#include "utils.h"

void _hash_update(hash_blk_update_func blk_update, uint32_t *hash, uint8_t *blk, const uint8_t *data, size_t len, uint64_t *total) {
    size_t offset = *total % HASH_BLK_SIZE;
    if (offset + len < HASH_BLK_SIZE) {
        memcpy(blk + offset, data, len);
        *total += len;
        return;
    }

    const uint8_t *end = data + len;
    const uint8_t *p   = data;
    if (offset != 0) {
        mem