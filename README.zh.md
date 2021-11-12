# zcrypto
一个为受限环境（比如STM32）写的加密相关操作的库。

*支持功能*:
* base64
* hash
    * SM3
    * MD5
    * SHA1
    * SHA256
* block cipher algorithm
    * AES(128, 192, 256)
    * SM4
* block cipher mode
    * ECB
    * CBC
    * CFB
    * OFB
* asymmetric key encryption
    * RSA(2048)

## 分组密码

支持：AES（192、169，256）， SM4，模式支持ECB，CBC，CFB，OFB。
支持两种风格的API。一种是：`aes_{keylen}_{mode}_{en/de}crypt`和`sm4_{mode}_{en/de}crypt`，这是做一次性加密（解密）的。
另一种是`aes_{en/de}crypt(aes_ctx_t*, ...)`和`sm4_{en/de}crypt(sm4_ctx_t*, ...)`，这种可以调用多次，
对流数据进行加密（解密）。具体使用请看`test/test_{aes/sm4}.c`。

## HASH算法

支持SM3，MD5，SHA1，SHA256。使用`{alg}_init`初始化，使用`{alg}_update`更新数据，使用`{