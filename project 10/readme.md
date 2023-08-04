# **report on the application of this deduce technique in Ethereum with ECDSA**

### **一、ECDSA概述**

ECDSA（Elliptic Curve Digital Signature Algorithm）是一种基于椭圆曲线密码学的数字签名算法。它是由美国国家标准与技术研究院（NIST）于1999年发布，并广泛应用于现代密码学和安全通信领域。

ECDSA利用椭圆曲线上的离散对数难题（Elliptic Curve Discrete Logarithm Problem，ECDLP）的困难性来保证数字签名的安全性。相比传统的RSA数字签名算法，ECDSA在相同的安全强度下，具有更短的密钥长度和更高的计算效率。

ECDSA包含三个主要的算法：密钥生成算法（Key Generation），签名算法（Sign），验证算法（Verify）。通过生成公钥和私钥，使用私钥对消息进行签名，再通过公钥验证签名的有效性。

ECDSA的安全性建立在椭圆曲线离散对数难题的困难性上，该难题在目前的计算能力下被认为是不可解的。因此，ECDSA成为了许多应用领域中的常用数字签名算法，如加密货币、数字证书、安全通信等。

### **二、ECC的实现**

![图片](https://github.com/puuuchiii/projects/blob/main/project%2010/image/3.png)


**签名过程：**

1.  选择一条椭圆曲线Ep(a, b)和基点G。
2.  选择私钥k（k < n），其中n是基点G的阶，然后计算公钥K = kG。
3.  生成一个随机数r（r < n），计算点R = rG。
4.  将原数据和点R的坐标值x、y作为参数，计算哈希值Hash = SHA1(原数据, x, y)。
5.  计算签名值s ≡ r - Hash * k (mod n)。
6.  如果签名中的r或s等于0，则重新从第3步开始执行。

**验证过程：**

1.  接收方在收到消息m和签名值(r, s)后，进行以下运算。
2.  计算临时点(x1, y1) = sG + Hash(m) * K。
3.  计算临时值r1 ≡ x1 (mod n)。
4.  验证等式：r1 ≡ r (mod n)。
5.  如果等式成立，则接受签名；否则，签名无效。


