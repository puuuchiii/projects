## Project9: AES / SM4 software implementation
### SM4 流程图
![图片](https://github.com/puuuchiii/projects/blob/main/project%209/image/3.png)

### 轮密钥生成
![图片](https://github.com/puuuchiii/projects/blob/main/project%209/image/1.png)
![图片](https://github.com/puuuchiii/projects/blob/main/project%209/image/2.png)

### 加密过程
将明文分组成128位的数据块，然后通过32轮的轮函数进行加密。每轮轮函数包括以下步骤：
1.轮密钥加：将当前轮的轮密钥与数据块按位异或。
2.S盒变换：通过非线性的S盒变换，对数据块中的每个字节进行替换。
3.线性变换：通过线性的P盒变换，对数据块中的每个字节进行置换。
4.循环移位：对数据块中的每个字节进行循环移位操作。

### 解密过程：
与加密过程类似，将密文分组成128位的数据块，然后通过32轮的轮函数进行解密。解密过程与加密过程的主要区别在于轮密钥的使用顺序是相反的
![图片](https://github.com/puuuchiii/projects/blob/main/project%209/image/4.png)
