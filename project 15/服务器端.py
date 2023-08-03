from Crypto.Util.number import inverse
import socket
from random import randint

# Constants definition
P = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF
N = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123
A = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC
B = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93
G_X = 0x32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7
G_Y = 0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0
G = (G_X, G_Y)


def elliptic_curve_add(point1, point2):
    P_ = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF

    if point1 == 0 and point2 == 0:
        return 0
    elif point1 == 0:
        return point2
    elif point2 == 0:
        return point1
    elif point1[0] == point2[0]:
        if (point1[1] + point2[1]) % P_ == 0:
            return 0
        elif point1[1] == point2[1]:
            return Double(point1)
    else:
        if point1[0] > point2[0]:  # swap if px > qx
            temp_point = point1
            point1 = point2
            point2 = temp_point
        result = []
        slope = (point2[1] - point1[1]) * inverse(point2[0] - point1[0], P_) % P_  # slope
        result.append((slope ** 2 - point1[0] - point2[0]) % P_)
        result.append((slope * (point1[0] - result[0]) - point1[1]) % P_)
        return (result[0], result[1])

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

# Return multiplicative inverse
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
    if a == 0 and b == 0: return 0
    elif a == 0: return b
    elif b == 0: return a
    else:
        if a[0] > b[0]:
            a, b = b, a
        slope = (b[1] - a[1]) * inverse(b[0] - a[0], P) % P

        r = [(slope ** 2 - a[0] - b[0]) % P]
        r.append((slope * (a[0] - r[0]) - a[1]) % P)

        return (r[0], r[1])

def Double(p):
    slope = (3*p[0]**2 + A)*inverse(2*p[1], P) % P

    r = [(slope**2 - 2*p[0]) % P]
    r.append((slope*(p[0] - r[0]) - p[1])%P)

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



client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client.bind(('', 111))

print("等待建立连接...")

d2 = randint(1,N-1)
x,address = client.recvfrom(1024)
x = int(x.decode(),16)
y,address = client.recvfrom(1024)
y = int(y.decode(),16)
P1 = (x,y)
P1 = EC_mul(inverse(d2,P),P1)
P1 = Add(P1,(G_X,-G_Y))

x,address = client.recvfrom(1024)
x = int(x.decode(),16)
y,address = client.recvfrom(1024)
y = int(y.decode(),16)
Q1 = (x,y)
e,address = client.recvfrom(1024)
e = int(e.decode(),16)
k2 = randint(1,N-1)
k3 = randint(1,N-1)
Q2 = EC_mul(k2,G)
x1,y1 = EC_mul(k3,Q1)
x1,y1 = Add((x1,y1),Q2)
r =(x1 + e)%N
s2 = (d2 * k3)%N
s3 = (d2 * (r+k2))%N
client.sendto(hex(r).encode(),address)
client.sendto(hex(s2).encode(),address)
client.sendto(hex(s3).encode(),address)
print("连接已关闭")
