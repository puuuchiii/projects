
# 创新创业实践项目

## 小组成员

| 姓名   | 班级          | 学号             | github账号|
| ------ | ------------- | ----------------| ---------|
|陈于思 | 2021级密码2班陈于思 | 202100141118 | puuuchiii|

## 项目列表

### SM3

- [x] Implement the naive birthday attack of reduced `SM3`

      项目要求实现SM3的生日攻击.
      本项目首先用python实现了SM3算法，然后定义了Birthday_Attack函数，参数n为攻击的目标位数，表示要实现SM3生日攻击的前n位碰撞。

      在函数内，使用for循环枚举所有可能的输入a1和a2（0到2^n之间的随机整数）。
      将a1和a2转换为字符串，并计算其对应的哈希值c1和c2。取c1和c2的前n/4位作为比较值（因为c1、c2的一位为一个字节，所以n/4为一位）。
      如果c1和c2相等，且a1不等于a2，则表示找到了碰撞，打印攻击成功信息，输出a1、c1、a2和c2，并结束循环。
      如果循环结束时没有找到碰撞，则攻击失败。

      项目最后展示了攻击的结果，具体结果见project1 readme.md

      
- [x] Implement the Rho method of reduced `SM3`
      
      Rho攻击是一种碰撞攻击，旨在找到两个不同的输入消息，经过SM3哈希后具有相同的哈希值。

      Rho攻击基于哈希函数的性质和哈希碰撞的概率。
      它通过不断迭代初始输入，使用哈希函数生成下一个输入，然后检查生成的哈希值是否与之前的某个哈希值相同。
      如果发现两个不同的输入生成了相同的哈希值，那么就找到了一个碰撞，即两个输入具有相同的哈希值。

      在SM3的Rho攻击中，通常使用的迭代函数是 a = 2*a + 1，
      然后将 a 输入到SM3哈希函数中进行计算。
      通过不断迭代生成输入并计算哈希值，攻击者希望找到具有相同哈希值的两个不同的输入。
      项目通过python 实现，具体结果见project 2 readme.md

注意：想要实现前多少位的Rho攻击就把Rho_attck(n)中的n改为多少。
- [x] Implement length extension attack for `SM3`, `SHA256`, etc.

      本项目实现了SM3的长度扩展攻击。长度扩展攻击即攻击者不知道原始消息a，
      知道H(a）和a的长度，通过长度扩展攻击，攻击者可以知道H(a+pad+附加消息)。
      
      
- [x] Do your best to optimize `SM3` implementation (software)
      
      项目通过优化SM3的消息拓展部分，在运算W[0]—W[15]的过程中，运用了for循环展开来进行优化，
      而在运算W[16]—W[67]的即W1[0]—W1[63]的过程中，运用了SIMD指令集进行优化。
      
      项目通过c++实现，优化前所用时间为2063ms,优化后的时间为1672ms.
- [x] Implement Merkle Tree following [RFC6962](https://www.rfc-editor.org/info/rfc6962)

      假设要检查 H 节点是否在这棵树中，那么我们需要 TH，HG，HEF，HABCD，HABCDEFGH，这些节点的哈希值。
      然后将 TH通过 hash 函数转换成 HH，接着按照相似的流程 hash(HG, HH)，hash(HGH, HEF), …
      最终我们只需要比较这一次 hash 的 HABCDEFGH 和区块头中存储的 HABCDEFGH 是否一致即可。

      要证某个元素不在Merkle tree里可以证紧挨着这个元素比这个元素小的和大的都在Merkle tree里,
      来证明这个元素不在Merkle tree里（比如要证1.5不在Merkle tree里可通过证1和2在Merkle tree里）。
      本项目由python 实现，证明了点1.5不在建立的mekel树中。      
### SM2

- [x] Report on the application of this deduce technique in Ethereum with `ECDSA`
- [ ] Implement `SM2` with [RFC6979](https://www.rfc-editor.org/info/rfc6979)
- [ ] Verify the some pitfalls with proof-of-concept code
- [ ] Implement the above `ECMH` scheme
- [ ] Implement a `PGP` scheme with `SM2`

- [x] Implement `SM2` 2P sign with real network communication
- [x] Implement `SM2` 2P decrypt with real network communication
- [x] 比较Firefox和谷歌的记住密码插件的实现区别



### AES
- [x] AES impl with ARM instruction
      
      在ARMv8架构上使用AES内部函数进行AES加密和解密操作，并利用ARMv8的AES扩展指令来优化AES算法的执行。
      通过使用C内部函数，可以更方便地访问这些指令，以实现更高效的加密和解密功能。

      在ARM架构的SIMD（单指令多数据）指令集中，AESE（AES single round encryption）表示AES的单轮加密操作，
      其中包括AddRoundKey、SubBytes和ShiftRows。
- [x] AES / SM4 software implementation

### Application
- [x] send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself
- [x] forge a signature to pretend that you are Satoshi

      
- [x] Schnorr Bacth
- [x] research report on MPT
