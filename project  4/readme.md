

## **Project4: do your best to optimize SM3 implementation (software)**

### 说明：

本文件夹的两个文件一个是优化前的代码，一个是优化后的代码。

本项目的优化主要体现在SM3的消息扩展部分，即如下：

![输入图片说明](/imgs/2023-08-02/UHWAhmdqsKWRPz2X.png)

在运算W[0]—W[15]的过程中，运用了for循环展开来进行优化，如下：

```
W[0] = cpu_to_be32(pblock[0]);

W[1] = cpu_to_be32(pblock[1]);

W[2] = cpu_to_be32(pblock[2]);

W[3] = cpu_to_be32(pblock[3]);

W[4] = cpu_to_be32(pblock[4]);

W[5] = cpu_to_be32(pblock[5]);

W[6] = cpu_to_be32(pblock[6]);

W[7] = cpu_to_be32(pblock[7]);

W[8] = cpu_to_be32(pblock[8]);

W[9] = cpu_to_be32(pblock[9]);

W[10] = cpu_to_be32(pblock[10]);

W[11] = cpu_to_be32(pblock[11]);

W[12] = cpu_to_be32(pblock[12]);

W[13] = cpu_to_be32(pblock[13]);

W[14] = cpu_to_be32(pblock[14]);

W[15] = cpu_to_be32(pblock[15]);
```

在运算W[16]—W[67]的即W1[0]—W1[63]的过程中，运用了SIMD指令集进行优化：

```
for (j = 16; j < 68; j += 4) {

o = _mm_loadu_si128((__m128i*)(W + j - 3));

o = _mm_andnot_si128(_mm_setr_epi32(0, 0, 0, 0xffffffff), o);

o = _mm_rotl_epi32(o, 15);

p = _mm_loadu_si128((__m128i*)(W + j - 9));

o = _mm_xor_si128(o, p);

p = _mm_loadu_si128((__m128i*)(W + j - 16));

o = _mm_xor_si128(o, p);

p = _mm_rotl_epi32(o, (23 - 15));

p = _mm_xor_si128(p, o);

p = _mm_rotl_epi32(p, 15);

o = _mm_xor_si128(o, p);

p = _mm_loadu_si128((__m128i*)(W + j - 13));

p = _mm_rotl_epi32(p, 7);

o = _mm_xor_si128(o, p);

p = _mm_loadu_si128((__m128i*)(W + j - 6));

o = _mm_xor_si128(o, p);

q = _mm_shuffle_epi32(o, 0);

q = _mm_and_si128(q, _mm_setr_epi32(0, 0, 0, 0xffffffff));

p = _mm_rotl_epi32(q, 15);

p = _mm_xor_si128(p, q);

p = _mm_rotl_epi32(p, 9);

q = _mm_xor_si128(q, p);

q = _mm_rotl_epi32(q, 6);

o = _mm_xor_si128(o, q);

_mm_storeu_si128((__m128i*)(W + j), o);

}

for (j = 0; j < 64; j += 4)

{

a = _mm_loadu_si128((__m128i*)(W + j)); //每次4个并行计算W1[j]数组中的值

b = _mm_loadu_si128((__m128i*)(W + j + 4));

c = _mm_xor_si128(a, b);

_mm_storeu_si128((__m128i*)(W1 + j), c);

}
```

![输入图片说明](/imgs/2023-08-02/uS1dCAO71AuY4sXC.png)

实现：

本项目用c++完成。

![输入图片说明](/imgs/2023-08-02/GP3AZLprIC0KR6Sg.png)
