#include <assert.h>
#include "hash.h"
#include "hashlib.h"
#include "sm3.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "utils.h"

void hash_init(hash_ctx_t *ctx, i