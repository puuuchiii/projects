## **Project2**：实现****SM3****的****rho****攻击

### 代码说明：

Rho攻击是一种碰撞攻击，旨在找到两个不同的输入消息，经过SM3哈希后具有相同的哈希值。

Rho攻击基于哈希函数的性质和哈希碰撞的概率。它通过不断迭代初始输入，使用哈希函数生成下一个输入，然后检查生成的哈希值是否与之前的某个哈希值相同。如果发现两个不同的输入生成了相同的哈希值，那么就找到了一个碰撞，即两个输入具有相同的哈希值。

在SM3的Rho攻击中，通常使用的迭代函数是 a = 2*a + 1，然后将 a 输入到SM3哈希函数中进行计算。通过不断迭代生成输入并计算哈希值，攻击者希望找到具有相同哈希值的两个不同的输入。

注意：想要实现前多少位的Rho攻击就把Rho_attck(n)中的n改为多少。

### 实现方式：

Python

结果：

![图片](https://github.com/puuuchiii/projects/blob/main/project%202/image/3.png)
以实现前40位的Rho攻击为例：
![图片](https://github.com/puuuchiii/projects/blob/main/project%202/image/4.png)


