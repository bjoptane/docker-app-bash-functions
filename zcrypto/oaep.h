#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "rsa.h"

// see https://tools.ietf.org/html/rfc8017
// using SHA256
// NOTICE: you has to ensure that message length <= MSG_MAX_LEN
// NOTICE: you has to call `srand` yourself to set rand seed
#define HASH_BYTES 32
#