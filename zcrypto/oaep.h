#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "rsa.h"

// see https://tools.ietf.org/html/rfc8017
// using SHA256
// NOTICE: you has to ensure that messag