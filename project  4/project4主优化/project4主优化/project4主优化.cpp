// project4主优化.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
#define SM3_DIGEST_LENGTH	32
#define SM3_BLOCK_SIZE		64
#define SM3_HMAC_SIZE		(SM3_DIGEST_LENGTH)
#include <string>
#include <windows.h>
#include <immintrin.h>
#define cpu_to_be32(v) (((v)>>24) | (((v)>>8)&0xff00) | (((v)<<8)&0xff0000) | ((v)<<24))
# define _mm_rotl_epi32(X,i) _mm_xor_si128(_mm_slli_epi32((X),(i)), _mm_srli_epi32((X),32-(i)))
typedef struct {
	uint32_t digest[8];
	int nblocks;
	unsigned char block[64];
	int num;
} sm3_ctx_t;

void sm3_init(sm3_ctx_t* ctx);
void sm3_update(sm3_ctx_t* ctx, const unsigned char* data, size_t data_len);
void sm3_final(sm3_ctx_t* ctx, unsigned char digest[SM3_DIGEST_LENGTH]);
void sm3_compress(uint32_t digest[8], const unsigned char block[SM3_BLOCK_SIZE]);
void sm3(const unsigned char* data, size_t datalen,
	unsigned char digest[SM3_DIGEST_LENGTH]);

void sm3_init(sm3_ctx_t* ctx)
{
	ctx->digest[0] = 0x7380166F;
	ctx->digest[1] = 0x4914B2B9;
	ctx->digest[2] = 0x172442D7;
	ctx->digest[3] = 0xDA8A0600;
	ctx->digest[4] = 0xA96F30BC;
	ctx->digest[5] = 0x163138AA;
	ctx->digest[6] = 0xE38DEE4D;
	ctx->digest[7] = 0xB0FB0E4E;

	ctx->nblocks = 0;
	ctx->num = 0;
}

void sm3_update(sm3_ctx_t* ctx, const unsigned char* data, size_t data_len)
{
	if (ctx->num) {
		unsigned int left = SM3_BLOCK_SIZE - ctx->num;
		if (data_len < left) {
			memcpy(ctx->block + ctx->num, data, data_len);
			ctx->num += data_len;
			return;
		}
		else {
			memcpy(ctx->block + ctx->num, data, left);
			sm3_compress(ctx->digest, ctx->block);
			ctx->nblocks++;
			data += left;
			data_len -= left;
		}
	}
	while (data_len >= SM3_BLOCK_SIZE) {
		sm3_compress(ctx->digest, data);
		ctx->nblocks++;
		data += SM3_BLOCK_SIZE;
		data_len -= SM3_BLOCK_SIZE;
	}
	ctx->num = data_len;
	if (data_len) {
		memcpy(ctx->block, data, data_len);
	}
}

void sm3_final(sm3_ctx_t* ctx, unsigned char* digest)
{
	int i;
	uint32_t* pdigest = (uint32_t*)digest;
	uint32_t* count = (uint32_t*)(ctx->block + SM3_BLOCK_SIZE - 8);

	ctx->block[ctx->num] = 0x80;

	if (ctx->num + 9 <= SM3_BLOCK_SIZE) {
		memset(ctx->block + ctx->num + 1, 0, SM3_BLOCK_SIZE - ctx->num - 9);
	}
	else {
		memset(ctx->block + ctx->num + 1, 0, SM3_BLOCK_SIZE - ctx->num - 1);
		sm3_compress(ctx->digest, ctx->block);
		memset(ctx->block, 0, SM3_BLOCK_SIZE - 8);
	}

	count[0] = cpu_to_be32((ctx->nblocks) >> 23);
	count[1] = cpu_to_be32((ctx->nblocks << 9) + (ctx->num << 3));

	sm3_compress(ctx->digest, ctx->block);
	for (i = 0; i < sizeof(ctx->digest) / sizeof(ctx->digest[0]); i++) {
		pdigest[i] = cpu_to_be32(ctx->digest[i]);
	}
}

#define ROTATELEFT(X,n)  (((X)<<(n)) | ((X)>>(32-(n))))

#define P0(x) ((x) ^  ROTATELEFT((x),9)  ^ ROTATELEFT((x),17))
#define P1(x) ((x) ^  ROTATELEFT((x),15) ^ ROTATELEFT((x),23))

#define FF0(x,y,z) ( (x) ^ (y) ^ (z))
#define FF1(x,y,z) (((x) & (y)) | ( (x) & (z)) | ( (y) & (z)))

#define GG0(x,y,z) ( (x) ^ (y) ^ (z))
#define GG1(x,y,z) (((x) & (y)) | ( (~(x)) & (z)) )


void sm3_compress(uint32_t digest[8], const unsigned char block[64])
{
	int j;
	uint32_t W[68], W1[64];
	const uint32_t* pblock = (const uint32_t*)block;
	__m128i a,b,c,o,p,q;

	uint32_t A = digest[0];
	uint32_t B = digest[1];
	uint32_t C = digest[2];
	uint32_t D = digest[3];
	uint32_t E = digest[4];
	uint32_t F = digest[5];
	uint32_t G = digest[6];
	uint32_t H = digest[7];
	uint32_t SS1, SS2, TT1, TT2, T[64];

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
		a = _mm_loadu_si128((__m128i*)(W + j));    //每次4个并行计算W1[j]数组中的值
		b = _mm_loadu_si128((__m128i*)(W + j + 4));
		c = _mm_xor_si128(a, b);
		_mm_storeu_si128((__m128i*)(W1 + j), c);

	}


	for (j = 0; j < 16; j++) {

		T[j] = 0x79CC4519;
		SS1 = ROTATELEFT((ROTATELEFT(A, 12) + E + ROTATELEFT(T[j], j)), 7);
		SS2 = SS1 ^ ROTATELEFT(A, 12);
		TT1 = FF0(A, B, C) + D + SS2 + W1[j];
		TT2 = GG0(E, F, G) + H + SS1 + W[j];
		D = C;
		C = ROTATELEFT(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = ROTATELEFT(F, 19);
		F = E;
		E = P0(TT2);
	}

	for (j = 16; j < 64; j++) {

		T[j] = 0x7A879D8A;
		SS1 = ROTATELEFT((ROTATELEFT(A, 12) + E + ROTATELEFT(T[j], j)), 7);
		SS2 = SS1 ^ ROTATELEFT(A, 12);
		TT1 = FF1(A, B, C) + D + SS2 + W1[j];
		TT2 = GG1(E, F, G) + H + SS1 + W[j];
		D = C;
		C = ROTATELEFT(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = ROTATELEFT(F, 19);
		F = E;
		E = P0(TT2);
	}

	digest[0] ^= A;
	digest[1] ^= B;
	digest[2] ^= C;
	digest[3] ^= D;
	digest[4] ^= E;
	digest[5] ^= F;
	digest[6] ^= G;
	digest[7] ^= H;
}

void sm3(const unsigned char* msg, size_t msglen,
	unsigned char dgst[SM3_DIGEST_LENGTH])
{
	sm3_ctx_t ctx;

	sm3_init(&ctx);
	sm3_update(&ctx, msg, msglen);
	sm3_final(&ctx, dgst);

	memset(&ctx, 0, sizeof(sm3_ctx_t));
}

string DecToHex(int str) {
	string hex = "", a = "";
	if (str <= 15)
		a += '0';
	int temp = 0;
	while (str >= 1) {
		temp = str % 16;
		if (temp < 10 && temp >= 0) {
			hex = to_string(temp) + hex;
		}
		else {
			hex = char(('a' + (temp - 10))) + hex;
		}
		str = str / 16;
	}
	return a + hex;
}

int main()
{
	unsigned char msg[] = "12345678";
	size_t msg_len = strlen((const char*)msg);
	unsigned char dgst1[SM3_DIGEST_LENGTH];
	double start = GetTickCount();
	for (int i = 0; i < 1000000; i++)
		sm3(msg, msg_len, dgst1);
	double end = GetTickCount();
	double last = end - start;
	cout << "所用时间：" << endl;
	cout << last << "ms" << endl;
	sm3(msg, msg_len, dgst1);
	cout << "hash值：" << endl;
	for (int i = 0; i < SM3_DIGEST_LENGTH; i++) {
		cout << DecToHex(int(dgst1[i]));
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
