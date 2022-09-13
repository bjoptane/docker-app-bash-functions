#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define AES_FUNC_DEF_NO_IV(KEY, MODE, EN) void aes_ ## KEY ## _ ## MODE ## _ ## EN (const uint8_t *, size_t, const uint8_t*, uint8_t*)
#define AES_FUNC_DEF_HAS_IV(KEY, MODE, EN) void aes_ ## KEY ## _ ## MODE ## _ ## EN (const uint8_t *, const uint