from gmssl import sm3, func
from Crypto.Util.number import inverse, long_to_bytes, bytes_to_long
import sys
import socket
import binascii
from random import randint

# Constants definition
P = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF
N = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123
A = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC
B = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93
G_X = 0x32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7
G_Y = 0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0
G = (G_X, G_Y)

# The Euclidean algorithm to find the greatest common divisor
def find_gcd(num1, num2):
    remainder = num1 % num2
    while remainder != 0:
        num1, num2 = num2, remainder
        quotient = num1 // num2
        remainder = num1 % num2
    return num2

# Extended Euclidean algorithm to solve a linear equation for x and y
def ext_euclidean(num1, num2):
    if num2 == 0:
        return 1, 0
    else:
        quotient = num1 // num2
        remainder = num1 % num2
        x_new, y_new = ext_euclidean(num2, remainder)
        x, y = y_new, x_new - quotient * y_new
    return x, y

# 返回乘法逆元
def get_multiplicative_inverse(num1, num2):
    # Save the absolute initial value of num2
    if num2 < 0:
        modulus = abs(num2)
    else:
        modulus = num2

    gcd_value = find_gcd(num1, num2)
    # Check if the greatest common divisor is 1. If it is not, there is no inverse
    if gcd_value == 1:
        x, y = ext_euclidean(num1, num2)
        inverse = x % modulus
        return inverse

    else:
        print("Does not exist!")

def Add(a, b):
    if a == 0 and b == 0:
        return 0
    elif a == 0:
        return b
    elif b == 0:
        return a
    else:
        if a[0] > b[0]:
            a, b = b, a
        slope = (b[1] - a[1]) * inverse(b[0] - a[0], P) % P

        r = [(slope ** 2 - a[0] - b[0]) % P]
        r.append((slope * (a[0] - r[0]) - a[1]) % P)

        return (r[0], r[1])

def Double(p):
    slope = (3 * p[0] ** 2 + A) * inverse(2 * p[1], P) % P

    r = [(slope ** 2 - 2 * p[0]) % P]
    r.append((slope * (p[0] - r[0]) - p[1]) % P)

    return (r[0], r[1])

def EC_mul(s, p):
    n = p
    r = 0
    s_binary = bin(s)[2:]
    s_length = len(s_binary)
    for i in reversed(range(s_length)):
        if s_binary[i] == '1':
            r = Add(r, n)
        n = Double(n)
    return r

def KDF(Z, klen):
    hlen = 256
    n = (klen // hlen) + 1
    if n >= 2 ** 32 - 1:
        raise ValueError("The hash length is too large!")
    K = ''
    for i in range(n):
        ct = (hex(i + 1)[2:]).rjust(32, '0')
        tmp_b = bytes.fromhex(Z + ct)
        Kct = sm3.sm3_hash(list(tmp_b))
        K += Kct
    bit_len = 256 * n
    K = (bin(int(K, 16))[2:]).rjust(bit_len, '0')
    K = K[:klen]
    return K


client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client.bind(('', 111))

print("等待建立连接...")

# step1
d2 = randint(1, N - 1)

# STEP3
x,address = client.recvfrom(1024)
x = int(x.decode(),16)
y,address = client.recvfrom(1024)
y = int(y.decode(),16)

T1 =(x,y)

# step4
T2 = EC_mul(inverse(d2, P), T1)
x2, y2 = hex(T1[0]), hex(T1[1])
client.sendto(x2.encode('utf-8'), address)
client.sendto(y2.encode('utf-8'), address)
print("连接已关闭")








