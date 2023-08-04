## implement sm2 2P sign with real network communication

### 实现步骤：
![图片](https://github.com/puuuchiii/projects/blob/main/project%2015/image/1.png)


数字签名生成算法的步骤如下：

A1: 将消息M与ZA进行拼接，表示为M = ZA | M。其中ZA是用户A的身份标识。

A2: 计算哈希值e = H(M)，按照本文4.2.3和4.2.2部分给出的细节，将哈希值e的数据类型转换为整数。

A3: 使用随机数发生器生成一个随机数k，满足1 ≤ k ≤ n - 1，其中n是椭圆曲线的阶。

A4: 计算椭圆曲线点(a1, 21) = k * G，按照本文4.2.7部分给出的细节，将椭圆曲线点的x坐标a1的数据类型转换为整数。

A5: 计算r = (e + a1) mod n，如果r = 0 或者 r + k = n，则返回到步骤A3重新生成随机数。

A6: 计算s = ((1 + dA)^-1 * (k - r * dA)) mod n，其中dA是用户A的私钥。如果s = 0，则返回到步骤A3重新生成随机数。

A7: 按照本文4.2.1部分给出的细节，将r和s的数据类型转换为字节串。此时，消息M的数字签名为(r, s)。

### 输出结果
![图片](https://github.com/puuuchiii/projects/blob/main/project%2015/image/2.jpg)
