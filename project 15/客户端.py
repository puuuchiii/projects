from Crypto.Util.number import inverse
import socket
import sys
import binascii
from random import randint

# Parameter Configuration
PRIME = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF
ORDER = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123
COEFFICIENT_A = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC
COEFFICIENT_B = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93
BASE_POINT_X = 0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2
BASE_POINT_Y = 0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0
BASE_POINT = (BASE_POINT_X, BASE_POINT_Y)


def add_points(point1, point2):
    if point1 == 0 and point2 == 0:
        return 0
    elif point1 == 0:
        return point2
    elif point2 == 0:
        return point1
    else:
        if point1[0] > point2[0]:
            point1, point2 = point2, point1
        slope_ratio = (point2[1] - point1[1]) * inverse(point2[0] - point1[0], PRIME) % PRIME

        res_point = [(slope_ratio ** 2 - point1[0] - point2[0]) % PRIME]
        res_point.append((slope_ratio * (point1[0] - res_point[0]) - point1[1]) % PRIME)

        return (res_point[0], res_point[1])


def double_point(point):
    slope_ratio = (3 * point[0] ** 2 + COEFFICIENT_A) * inverse(2 * point[1], PRIME) % PRIME

    res_point = [(slope_ratio ** 2 - 2 * point[0]) % PRIME]
    res_point.append((slope_ratio * (point[0] - res_point[0]) - point[1]) % PRIME)

    return (res_point[0], res_point[1])

def multiply_point(coefficient, point):
    duplicate = point
    res_point = 0
    binary_coefficient = bin(coefficient)[2:]
    num_digits = len(binary_coefficient)
    for i in reversed(range(num_digits)):
        if binary_coefficient[i] == '1':
            res_point = add_points(res_point, duplicate)
        duplicate = double_point(duplicate)

    return res_point
