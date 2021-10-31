######################################
# building variables
######################################
DEBUG = 1

#######################################
# binaries
#######################################
# PREFIX = arm-none-eabi-
PREFIX =
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

WARNS = -Wall -Wextra -Wuninitialized -Wsign-conversion
CFLAGS = -std=c11 $(WARNS)

ifeq ($(DEBUG), 1)
CFLAGS += -g
else
CFLAGS += -O2
endif

LIBS = -lc -lm
LIBDIR =
LDFLAGS = $(LIBDIR) $(LIBS)


BUILD_DIR = build

SOURCES = \
zcrypto/aes.c \
zcrypto/base64.c \
zcrypto/hash.c \
zcrypto/hashlib.c \
zcrypto/md5.c \
zcrypto/oaep.c \
zcrypto/rsa.c \
zcrypto/sha1.c \
zcrypto/