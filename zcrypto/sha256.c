#include "sha256.h"
#include "hash.h"
#include "utils.h"

static inline uint32_t CH(uint32_t X, uint32_t Y, uint32_t Z) {
    return (X & Y) ^ (~X & Z);
}

static inline uint32_t MAJ(uint32_t X, uint32_t Y, uint32_t Z) {
    return (X & Y) ^ (X & Z) ^ (Y & Z);
}

static inline uint32_t BSIG0(uint32_t X) {
    return _rshift(X, 2) ^ _rshift(X, 13) ^ _rshift(X, 22);
}

static inline uint32_t BSIG1(uint32_t X) {
    return _rshift(X, 6) ^ _rshift(X, 11) ^ _rshift(X, 25);
}

static inline uint32_t SSIG0(uint32_t X) {
    return _rshift(X, 7) ^ _rshift(X, 18) ^ (X >> 3);
}

static inline uint32_t SSIG1(uint32_t X) {
    return _rshift(X, 17) ^ _rshift(X, 19) ^ (X >> 10);
}

static const uint32_t K[] = {
    0x428a2f98ul, 0x71374491ul, 0xb5c0fbcful, 0xe9b5dba5ul,
    0x3956c25bul, 0x59f111f1ul, 0x923f82a4ul, 0xab1c5ed5ul,
    0xd807aa98ul, 0x12835b01ul, 0x243185beul, 0x550c7dc3ul,
    0x72be5d74ul, 0x80deb1feul, 0x9bdc06a7ul, 0xc19bf174ul,
    0xe49b69c1ul, 0xefbe4786ul, 0x0fc19dc6ul, 0x240ca1ccul,
    0x2de92c6ful, 0x4a7484aaul, 0x5cb0a9dcul, 0x76f988daul,
    0x983e5152ul, 0xa831c66dul, 0xb00327c8ul, 0xbf597fc7ul,
    0xc6e00bf3ul, 0xd5a79147ul, 0x06ca6351ul, 0x14292967ul,
    0x27b70a85ul, 0x2e1b2138ul, 0x4d2c6dfcul, 0x53380d13