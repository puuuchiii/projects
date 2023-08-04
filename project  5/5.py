import random
import string
import hashlib

def sha256(data):
    hash_object = hashlib.sha256()
    hash_object.update(data.encode('utf-8'))
    hash_value = hash_object.hexdigest()
    return hash_value

class Merkeltree:
    def __init__(self, value):
        self.v = value
        self.root, self.leaves = self.merkel()

    def merkel(self):
        l = []
        leaves = dict() 
        if len(self.v) == 0:
            l = sha256()
            return l, []
        elif len(self.v) == 1:
            l.append(sha256('0x00'+self.v[0]))
            return l, []
        else:
            for i in self.v:
                l.append(sha256(i))
            while len(l) > 1:
                t = []
                if len(l) % 2 == 0:
                    while len(l) > 1:
                        a = l.pop(0)
                        leaves[a] = 0
                        b = l.pop(0)
                        leaves[b] = 1
                        t.append(sha256('0x01'+a+b))
                    l = t
                else:
                    last = l.pop(-1)
                    while len(l) > 1:
                        a = l.pop(0)
                        leaves[a] = 0
                        b = l.pop(0)
                        leaves[b] = 1
                        t.append(sha256('0x01'+a+b))
                    t.append(last)
                    leaves[last] = 1
                    l = t
            return l[0], leaves

    def p(self, x, l):
        k = 0
        t = []
        if len(l) == 2:
            t.append(l[(x + 1) % 2])
            return t
        elif len(l) > 2:
            for i in range(1, len(l)):
                if 2**i >= len(l):
                    k = 2**(i - 1)
                    break
            if x < k:
                t.extend(self.p(x, l[0:k]))
                t.append(self.q(l[k:len(l)])) 
                return t
            elif x >= k:
                t.extend(self.p(x - k, l[k:len(l)]))
                t.append(self.q(l[0:k])) 
                return t
        else:
            return t

    def q(self, l):
        k = 0
        if len(l) == 1:
            return l[0]
        elif len(l) == 2:
            return sha256('0x01'+l[0]+l[1])
        else:
            for i in range(0, len(l)):
                if 2**i >= len(l):
                    k = 2**(i - 1)
                    break
            return sha256('0x01'+self.q(l[0:k])+self.q(l[k:len(l)]))

    def path(self, x):
        l = []
        if len(self.v) > 1:
            for i in range(0, len(self.v)):
                l.append(sha256(self.v[i]))
            return self.p(x, l)
        elif len(self.v) == 1:
            return []
        else:
            return -1

    def inclusion(self, x, n):
        path = self.path(x)
        hash = sha256(n)
        for i in path:
            if self.leaves[i] == 0:
                hash = sha256('0x01'+i+hash)
            else:
                hash = sha256('0x01'+hash+i)
        if hash == self.root:
            return True,path
        else:
            return False

a = []
for i in range(100000):
    a.append(str(i))
print("建立一个有十万个叶节点的mekel树：")
tree = Merkeltree(a)
print("建立成功！其根hash为:\n", tree.root)
b=['1', '2', '3', '4', '5','6', '7', '8','9']
print("建立一个有9个叶节点的mekel树：")
t = Merkeltree(b)
print("建立成功！其根hash为:\n", t.root)
print("证明2在这个mekel树里：")
m,n=t.inclusion(1, '2')
if m:
    print("证明成功")
    print('证明时需要的相关节点:', n)
print("证明1.5不在这个mekel树里：")
m1,n1=t.inclusion(0, '1')
m2,n2=t.inclusion(1, '2')
if m1 and m2:
    print("证明成功")

