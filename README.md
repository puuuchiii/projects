
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

      ECDSA包含三个主要的算法：密钥生成算法（Key Generation），签名算法（Sign），验证算法（Verify）。通过生成公钥和私钥，使用私钥对消息进行签名，再通过公钥验证签名的有效性。
      签名过程：

      选择一条椭圆曲线Ep(a, b)和基点G。
      选择私钥k（k < n），其中n是基点G的阶，然后计算公钥K = kG。
      生成一个随机数r（r < n），计算点R = rG。
      将原数据和点R的坐标值x、y作为参数，计算哈希值Hash = SHA1(原数据, x, y)。
      计算签名值s ≡ r - Hash * k (mod n)。
      如果签名中的r或s等于0，则重新从第3步开始执行。
      在本实验中，公钥为（14，6），签名为（5，-20），签名验证通过
- [ ] Implement `SM2` with [RFC6979](https://www.rfc-editor.org/info/rfc6979)
- [ ] Verify the some pitfalls with proof-of-concept code
- [ ] Implement the above `ECMH` scheme
- [ ] Implement a `PGP` scheme with `SM2`

- [x] Implement `SM2` 2P sign with real network communication

      数字签名生成算法的步骤如下：

      A1: 将消息M与ZA进行拼接，表示为M = ZA | M。其中ZA是用户A的身份标识。
      A2: 计算哈希值e = H(M)，按照本文4.2.3和4.2.2部分给出的细节，将哈希值e的数据类型转换为整数。
      A3: 使用随机数发生器生成一个随机数k，满足1 ≤ k ≤ n - 1，其中n是椭圆曲线的阶。
      A4: 计算椭圆曲线点(a1, 21) = k * G，按照本文4.2.7部分给出的细节，将椭圆曲线点的x坐标a1的数据类型转换为整数。
      A5: 计算r = (e + a1) mod n，如果r = 0 或者 r + k = n，则返回到步骤A3重新生成随机数。
      A6: 计算s = ((1 + dA)^-1 * (k - r * dA)) mod n，其中dA是用户A的私钥。如果s = 0，则返回到步骤A3重新生成随机数。
      利用python 里的socket 模块实现，具体签名结果见readme.Md
- [x] Implement `SM2` 2P decrypt with real network communication
      
      和上面的实现思路非常相似，本质上是给SM2的签名算法中添加了解密算法。
      B1：从C中取出比特串C1，按本文本第1部分4.2.3和4.2.9给出的细节，将C1的数据类型转换为椭圆曲线上的点，验证C1是否满足椭圆曲线方程，若不满足则报错并退出；
      B2：计算椭圆曲线点S=[h]C1，若S是无穷远点，则报错并退出；
      B3：计算[dB]C1=(x2,y2)，按本文本第1部分4.2.5和4.2.4给出的细节，将坐标x2、y2的数据类型转
      换为比特串；
      B4：计算t=KDF(x2 ∥ y2, klen)，若t为全0比特串，则报错并退出；
      B5：从C中取出比特串C2，计算M′ = C2 ⊕ t；
      B6：计算u = Hash(x2 ∥ M′ ∥ y2)，从C中取出比特串C3，若u ̸= C3，则报错并退出；
      实验结果证明，发送明文与解密后消息一致
- [x] 比较Firefox和谷歌的记住密码插件的实现区别
      
      PBKDF2:
      PBKDF2实际上就是将伪散列函数PRF（pseudorandom function）应用到输入的密码、salt中，
      生成一个散列值，然后将这个散列值作为一个加密key，应用到后续的加密过程中，以此类推，
      将这个过程重复很多次，从而增加了密码破解的难度，这个过程也被称为是密码加强。
      Argon2:
      Argon2 尤其能抵挡排名权衡攻击，这使得在现场可编程逻辑门阵列上进行低成本攻击变得更加困难：虽然，最近的现场可编程逻辑门阵列已经嵌入 RAM 区块，但是，内存带宽仍然是一个限制，并且为了减少内存带宽要求，攻击者必须为了 Argon2 使用更多的计算资源。
### AES
- [x] AES impl with ARM instruction
      
      在ARMv8架构上使用AES内部函数进行AES加密和解密操作，并利用ARMv8的AES扩展指令来优化AES算法的执行。
      通过使用C内部函数，可以更方便地访问这些指令，以实现更高效的加密和解密功能。

      在ARM架构的SIMD（单指令多数据）指令集中，AESE（AES single round encryption）表示AES的单轮加密操作，
      其中包括AddRoundKey、SubBytes和ShiftRows。
- [x] AES / SM4 software implementation
      
      C++编程实现ECDSA签名方案的一个伪造。如果已知中本聪的公钥，同理可以忽略私钥，仅仅通过已有签名和公钥实现存在性伪造。
      具体结果见project 19 的 readme.md
### Application
- [x] send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself
- [x] forge a signature to pretend that you are Satoshi

      
- [x] Schnorr Bacth

      Schnorr Signature实现方法
      ·Key Generation 
      
      ·P-dG 
      
      ·Sign on given message M 
      
      · randomiy k,1et R=kG e-hash(RIIM) 
      
      ·s=k+ed mod n 
      
      ·Signature is:(R,s) 
      
      ·Verify (R,s) of Mwith P 
      
      ·Check sG vs R+eP sG=(k+ed)G-kG+edG-R+eP
      本项目使用C++编程实现 首先根据以上签名方案实现基础的Schnorr 签名。 然后根据老师PPT中方法，实现批量验签
- [x] research report on MPT

      以上介绍的MPT树，可以用来存储内容为任何长度的key-value数据项。倘若数据项的key长度没有限制时，当树中维护的数据量较大时，仍然会造成整棵树的深度变得越来越深，会造成以下影响：

      1.查询一个节点可能会需要许多次IO读取，效率低下
      
      2.系统易遭受Dos攻击，攻击者可以通过在合约中存储特定的数据，“构造”一棵拥有一条很长路径的树，然后不断地调用SLOAD指令读取该树节点的内容，造成系统执行效率极度下降
      
      3.所有的key其实是一种明文的形式进行存储
      
      为了解决以上问题，在以太坊中对MPT再进行了一次封装，对数据项的key进行了一次哈希计算，因此最终作为参数传入到MPT接口的数据项其实是 (sha3(key), value)
