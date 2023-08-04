
![图片](https://github.com/puuuchiii/projects/blob/main/project%2016/image/16.png)

通过修改project 15代码，我们可以利用T1 - C1 =(x2,y2) = d(私钥）* C1 =kP,巧妙地利用C2进行解密

在《SM2椭圆曲线公钥密码算法》中，我们可以更加清楚地看到加密和解密的整个流程


![图片](https://github.com/puuuchiii/projects/blob/main/project%2016/image/sm2%E5%8A%A0%E5%AF%86.png)
![图片](https://github.com/puuuchiii/projects/blob/main/project%2016/image/sm2%E8%A7%A3%E5%AF%86.png)
关键代码如下：
```
### step1  
d1 = randint(1, N - 1)  
d2 = randint(1, N - 1)  
### step2  
### Encrypt:  
k = randint(1, N - 1)  
C_1 = EC_mul(k, G)  
P_K = EC_mul(inverse(d1 * d2, P) - 1, G)     # public key  
G_2 = EC_mul(k, P_K)  
t = KDF('{:064X}'.format(G_2[0]) + '{:064X}'.format(G_2[1]), 64)  
msg = "111"  
msg = hex(int(binascii.b2a_hex(msg.encode()).decode(), 16)).upper()[2:]  
print(msg)  
C_2 = hex(int(msg, 16) ^ int(t, 2))[2:].upper()  
C_3 = sm3.sm3_hash(list(bytes.fromhex('{:064X}'.format(G_2[0]) + msg + '{:064X}'.format(G_2[1]))))  
  
### step2  
C = str(C_1[0]) + str(C_1[1]) + C_2 + C_3  
if C_1 != 0:  
    T1 = EC_mul(inverse(d1, P), C_1)  
    x, y = hex(T1[0]), hex(T1[1])  
    client.sendto(x.encode('utf-8'), address)  
    client.sendto(y.encode('utf-8'), address)  
  
x2, address = client.recvfrom(1024)  
x2 = int(x2.decode(), 16)  
y2, address = client.recvfrom(1024)  
y2 = int(y2.decode(), 16)  
  
T2 = (x2, y2)  
  
### step4  
T2 = EC_mul(inverse(d2, P), T1)  
G_3 = Add(T2,(C_1[0],-C_1[1]))  
t = KDF('{:064X}'.format(G_2[0]) + '{:064X}'.format(G_2[1]), 64)  
M = hex(int(C_2, 16) ^ int(t, 2))[2:].upper()  
print(M)
```
