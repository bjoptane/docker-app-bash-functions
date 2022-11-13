#include "sha256.h"
#include "hash.h"
#include "utils.h"

static inline uint32_t CH(uint32_t X, uint32_t Y, uint32_t Z) {
    return (X & Y) ^ (~X & Z);
}

static inline uint32_t MAJ(uint32_t X, uint32_t Y, uint32_t Z) {
    return (