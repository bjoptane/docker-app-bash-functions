#include <assert.h>
#include "hash.h"
#include "hashlib.h"
#include "sm3.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "utils.h"

void hash_init(hash_ctx_t *ctx, int alg) {
    assert(alg == HASH_ALG_SM3 || alg == HASH_ALG_MD5 || alg == HASH_ALG_SHA1 || alg == HASH_ALG_SHA256);
    memset(ctx, 0, sizeof(hash_ctx_t));
    ctx->alg = alg;
    switch (alg) {
        case HASH_ALG_SM3:
            ctx->hlen = 8;
            sm3_hash_init(ctx->hash);
            break;
        case HASH_ALG_MD5:
            ctx->hlen 