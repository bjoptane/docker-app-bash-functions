#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#if defined(__BYTE_ORDER__)
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define __ZCRYPO_BYTE_ORDER__ 1
    #else
        #define __ZCRYPO_BYTE_ORDER__ 2
    #endif
#else
    #error Unknown