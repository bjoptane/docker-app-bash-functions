#!/usr/bin/python3

import string
import sys
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Hash import SHA256


if len(sys.argv) <= 1:
    print("rsa_oaep_test.py gen | verify")
    sys.exit(0)

cmd = sys.argv[1]
if cmd != "gen" and cmd != "verify":
    print("rsa_oaep_test.py gen | verify")
    sys.exit(0)

if cmd == "gen":
    K = 2048
    LEN = K // 8
    key = RSA.generate(K)
    kk = key.exportKey()
    print(kk.decode("utf-8"))
    print()
    pubKey = key.publickey()
    print("E =", hex(pubKey.e))
    n = hex(pubKey.n)
    n = "0x" + "0" * (LEN * 2 + 2 - len(n)) + n[2:]
    print("N =", n)
    print()

elif cmd == "verify":
    text = sys.stdin.read()
    p = text.find("\n\n")
    keydata = text[:p]
    key = RSA.importKey(keydata)
    