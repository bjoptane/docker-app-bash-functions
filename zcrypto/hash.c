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
        memcpy(blk + offset, p, HASH_BLK_SIZE - offset);
        blk_update(hash, blk);
        p += HASH_BLK_SIZE - offset;
    }
    for (; p + HASH_BLK_SIZE <= end; p += HASH_BLK_SIZE) {
        blk_update(hash, p);
    }
    if (p < end) {
        memcpy(blk, p, (size_t)(end - p));
    }
    *total += len;
}

#define BLK_DATA_SZIE (HASH_BLK_SIZE - 8