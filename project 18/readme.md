## Project18: send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself
### 介绍

比特币测试币是一种用于模拟比特币网络交易的虚拟货币，用于开发和测试新的应用程序和功能。它们没有真实价值，主要在测试网络中使用，这里我们也使用这种测试币进行测试。比特币测试币分为Testnet和Regtest两种类型。Testnet是由比特币社区维护的公共测试网络，可通过水龙头获取。

### 实现方式
在比特币测试地址获取网站https://www.bitaddress.org/?testnet=true，获得测试地址
![图片](https://github.com/puuuchiii/projects/blob/main/project%2018/image/1.png)
mybeGUL4pq6crixQHWEuDNquGUxDgWtpKD 是我的地址

登录Faucets网站，输入我的地址获取一定数量的免费测试用币
![图片](https://github.com/puuuchiii/projects/blob/main/project%2018/image/2.png)
 
最后查询本次交易信息
![图片](https://github.com/puuuchiii/projects/blob/main/project%2018/image/5.png)
 
写脚本来爬取网页，解析tx信息，可以得到更多交易细节。
### 运行结果
脚本运行结果如下：
![图片](https://github.com/puuuchiii/projects/blob/main/project%2018/image/6.png)

在这里可以看到交易的地址、交易的哈希值、交易的大小、交易的生效时间，交易的输入输出等

