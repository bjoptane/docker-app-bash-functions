#include <stdio.h>
#include "zcrypto/hashlib.h"
#include "zcrypto/md5.h"
#include "zcrypto/sha1.h"
#include "zcrypto/sha256.h"
#include "zcrypto/sm3.h"

static void expect_equal(const char *name, const uint8_t *a, const uint8_t *b, size_t len) {
    if (memcmp(a, b, len) == 0) {
        printf("%s OK!\n", name);
    } else {
        printf("%s FAIL!\n", name);
    }
}

static void sm3_test() {
    uint8_t data1[] = {'a', 'b', 'c'};
    uint8_t digest1[32] = {
 