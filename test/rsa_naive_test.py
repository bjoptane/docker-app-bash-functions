#!/usr/bin/python3

import random
from Crypto.PublicKey import RSA


K = 2048
LEN = K // 8
key = RSA.generate(K)
pkey = key.publickey()

print("## keys:")
print("E =", hex(pkey.e))
n = hex(pkey.n)
n = "0x" 