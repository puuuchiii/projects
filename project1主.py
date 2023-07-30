import random

T = [0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,
     0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,0x79CC4519,
     0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,
     0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,
     0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,
     0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,
     0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,
     0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A,0x7A879D8A]

def _left(n,k):
    k=k % 32
    m=str(bin(n))
    m=m.split('0b')[1]
    m=(32-len(m))*'0'+m
    return int(m[k:]+m[:k],2)

def ff(x, y, z, j):
    result = 0
    if 0 <=j <= 15:
        result = x ^ y ^ z
    elif 16<=j<=63:
        result = (x & y) | (x & z) | (y & z)
    return result

def gg(x, y, z, j):
    result = 0
    if 0 <=j <= 15:
        result = x ^ y ^ z
    elif 16<=j<=63:
        result = (x & y) | (~x & z)
    return result

def p(n, mode):
    result = 0
    if mode == 0:
        result = n ^ _left(n, 9) ^ _left(n, 17)
    elif mode == 1:
        result = n ^ _left(n, 15) ^ _left(n, 23)
    return result

def cut(text,num):  
    m=[]
    for i in range(0, len(text), num):
        m.append(text[i:i+num])
    return m

def pad(s):               
    r = ""
    x = ""
    for i in s:
        l = (8 - len((x + bin(ord(i))).split('0b')[1])) % 8
        r = r + l * '0' + (x + bin(ord(i))).split('0b')[1]
    k=512-(64+(len(r)+1))%512
    m=r+'1'+k*'0'
    length=bin(len(r)).split('0b')[1]
    m=m+(64-len(length))*'0'+length
    m=cut(m,512)
    return m

def cf(iv,m):
    w1 = cut(m, 32)
    w2 = []
    for j in range(16):
        w1[j]=int(w1[j],2)
    for j in range(16, 68):
        t = p((w1[j - 16] ^ w1[j - 9] ^ _left(w1[j - 3] ,15)),1) ^ _left(w1[j - 13] ,7) ^ w1[j - 6]
        w1.append(t)
    for j in range(64):
        t = w1[j] ^ w1[j + 4]
        w2.append(t)
    A=cut(iv,8)
    for i in range(8):
        A[i]=int(A[i],16)
    for j in range(64):
        ss1=_left((_left(A[0],12)+A[4]+_left(T[j],j))%(2**32),7)%(2**32)
        ss2=(ss1^_left(A[0],12))%(2**32)
        tt1=(ff(A[0],A[1],A[2],j)+A[3]+ss2+w2[j])%(2**32)
        tt2=(gg(A[4],A[5],A[6],j)+A[7]+ss1+w1[j])%(2**32)
        A[3]=A[2]
        A[2]=_left(A[1],9)
        A[1]=A[0]
        A[0]=tt1
        A[7]=A[6]
        A[6]=_left(A[5],19)
        A[5]=A[4]
        A[4]=p((tt2),0)
    b=''
    for i in range(8):
        A[i]=str(hex(A[i])).split('0x')[1]
        k=8-len(A[i])
        b=b+k*'0'+A[i]
    c=int(b,16)^int(iv,16)
    c=hex(c).split('0x')[1]
    if len(c)<64:
        c="0"*(64-len(c))+str(c)
    return c

def SM3(p):
    iv = '7380166f4914b2b9172442d7da8a0600a96f30bc163138aae38dee4db0fb0e4e'
    for i in pad(p):
        if i != '':
            iv = cf(iv, i)
    return iv

def Birthday_Attack(n):#实现SM3生日攻击的前n位碰撞
    for i in range(2**128):
        a1=random.randint(0,2**n)
        a2=random.randint(0,2**n)
        b1=str(a1)
        b2=str(a2)
        c1=SM3(b1)[0:int(n/4)]
        c2=SM3(b2)[0:int(n/4)]
        if(c1==c2 and b1!=b2):
            print("生日攻击成功")
            print(b1)
            print(SM3(b1))
            print(b2)
            print(SM3(b2))
            break
        else:
            print("生日攻击失败")
            
Birthday_Attack(20)#可根据需要将函数变量n改为任何整数


