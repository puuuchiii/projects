## Project21: Schnorr Bacth

### Schnorr Signature实现方法

·Key Generation 
·P-dG 
·Sign on given message M 
· randomiy k,1et R=kG e-hash(RIIM) 
·s=k+ed mod n 
·Signature is:(R,s) 
·Verify (R,s) of Mwith P 
·Check sG vs R+eP sG=(k+ed)G-kG+edG-R+eP

本项目使用C++编程实现
首先根据以上签名方案实现基础的Schnorr 签名。
然后根据老师PPT中方法，实现批量验签

### 批量验签
![图片](https://github.com/puuuchiii/projects/blob/main/project%2021/image/1.png)

### 输出结果
![图片](https://github.com/puuuchiii/projects/blob/main/project%2021/image/2.png)
