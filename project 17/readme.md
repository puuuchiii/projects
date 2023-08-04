

## Project17：比较Firefox和谷歌的记住密码插件的实现区别

### 典型登录流程

互联网服务的典型登录流程是将您的用户名和密码发送到服务器，在那里他们对其进行哈希处理，将其与存储的哈希进行比较，如果正确，服务器将向您发送您的数据。
![图片](https://github.com/puuuchiii/projects/blob/main/project%2017/image/1.png)



Firefox 帐户和 Firefox Sync（我们的底层同步服务）的方式差异在于，您从不向我们发送密码。我们将您计算机上的密码转换为两个不同的、不相关的值。使用一个值，则无法派生另一个值[0]我们将派生自您的密码的身份验证令牌作为等效密码发送到服务器。从密码短语派生的加密密钥永远不会离开您的计算机。
![图片](https://github.com/puuuchiii/projects/blob/main/project%2017/image/2.png)
### PBKDF2的工作流程

PBKDF2实际上就是将伪散列函数PRF（pseudorandom function）应用到输入的密码、salt中，生成一个散列值，然后将这个散列值作为一个加密key，应用到后续的加密过程中，以此类推，将这个过程重复很多次，从而增加了密码破解的难度，这个过程也被称为是密码加强。

我们看一个标准的PBKDF2工作的流程图：

![](https://img-blog.csdnimg.cn/88e5f33cb69041ca92d8c50416e1aa91.png)

从图中可以看到，初始的密码跟salt经过PRF的操作生成了一个key，然后这个key作为下一次加密的输入和密码再次经过PRF操作，生成了后续的key，这样重复很多次，生成的key再做异或操作，生成了最终的T，然后把这些最终生成的T合并，生成最终的密码。

根据2000年的建议，一般来说这个遍历次数要达到1000次以上，才算是安全的。当然这个次数也会随着CPU计算能力的加强发生变化。这个次数可以根据安全性的要求自行调整。

有了遍历之后，为什么还需要加上salt呢？加上salt是为了防止对密码进行彩虹表攻击。也就是说攻击者不能预选计算好特定密码的hash值，因为不能提前预测，所以安全性得以提高。标准salt的长度推荐是64bits，美国国家标准与技术研究所推荐的salt长度是128 bits。
### Argon2
#### 参数调整

两个版本的算法都可以实现参数化：

-   **时间**开销，它定义了执行的时间
-   **内存**开销，它定义了内存的使用情况
-   **并行**程度，它定义了线程的数量

这意味着你可以分别调整这些参数，并根据你的用例、威胁模型和硬件规范来量身定制安全约束。

#### 权衡攻击

除此之外，Argon2 尤其能抵挡**排名权衡攻击**，这使得在现场可编程逻辑门阵列上进行低成本攻击变得更加困难：虽然，最近的现场可编程逻辑门阵列已经嵌入 RAM 区块，但是，内存带宽仍然是一个限制，并且为了减少内存带宽要求，攻击者必须为了 Argon2 使用更多的计算资源。




**参考文献**

> ### onepw protocol
> Ryan Kelly edited this page on Nov 26, 2015 · [43
> revisions](https://github.com/mozilla/fxa-auth-server/wiki/onepw-protocol/_history)
> ### Password Hashing: Scrypt, Bcrypt and ARGON2
>  ### https://github.com/mozilla/fxa-auth-server/wiki/onepw-protocol#vs-old-sync
