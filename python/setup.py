# code: utf-8

import os
from distutils.core import setup, Extension

name = "zcrypto"
ver = "0.1"

pydir = os.path.dirname(os.path.abspath(__file__))
rootdir = os.path.dirname(pydir)
libdir = os.path.join(rootdir, name)
src = ["../{}/{}".format(name, x) for