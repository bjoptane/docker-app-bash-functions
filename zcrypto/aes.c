#include "aes.h"
#include "utils.h"

static const uint8_t RCBOX[11] = {
    0x00, 0x01, 0x02, 0x04, 0