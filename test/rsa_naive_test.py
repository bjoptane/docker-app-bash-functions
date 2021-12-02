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
n = "0x" + "0" * (LEN * 2 + 2 - len(n)) + n[2:]
print("N =", n)
d = hex(key.key.d)
d = "0x" + "0" * (LEN * 2 + 2 - len(d