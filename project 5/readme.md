## **Project5:Impl Merkle Tree following RFC6962**

### 说明：

Merkle tree是一种数据结构，以它的提出者默克尔命名，根据默克尔树的性质也可以叫哈希树，是一种典型的二叉树。默克尔树由根，分支（中间的非叶节点），叶节点组成。典型的Merkle tree如下所示：


![图片](https://github.com/puuuchiii/projects/blob/main/project%20%205/image/1.png)

而本项目要实现符合RFC6962的Merkle tree：

1.空列表的哈希是空字符串的哈希：

MTH({}) = SHA-256()

2.具有一个条目的列表的哈希（也称为叶哈希）为：

MTH({d(0)}) = SHA-256(0x00 || d(0))

3.对于n>1，设k为小于n的两个的最大幂（即k<n<=2k）。然后递归地将n元素列表D[n]的Merkle树散列定义为

MTH(D[n]) = SHA-256(0x01 || MTH(D[0:k]) || MTH(D[k:n]))

其中||是串联，D[k1:k2]表示长度（k2-k1）的列表{D（k1），D（k1+1），…，D（k2-1）}。

某个元素在Merkle tree的存在性证明以下图为例：

![图片](https://github.com/puuuchiii/projects/blob/main/project%20%205/image/2.png)

以上图为例说明：假设要检查 H 节点是否在这棵树中，那么我们需要 TH，HG，HEF，HABCD，HABCDEFGH，这些节点的哈希值。然后将 TH通过 hash 函数转换成 HH，接着按照相似的流程 hash(HG, HH)，hash(HGH, HEF), …最终我们只需要比较这一次 hash 的 HABCDEFGH 和区块头中存储的 HABCDEFGH 是否一致即可。

要证某个元素不在Merkle tree里可以证紧挨着这个元素比这个元素小的和大的都在Merkle tree里来证明这个元素不在Merkle tree里（比如要证1.5不在Merkle tree里可通过证1和2在Merkle tree里）。

### 实现：

本项目用python完成。

### 结果：

因为证某个元素在Merkle tree里时我想把证明时需要的相关节点比较清楚的显示出来，所以证明时我建立了一个有9个叶节点的Merkle tree来用作展示：

![图片](https://github.com/puuuchiii/projects/blob/main/project%20%205/image/3.png)

