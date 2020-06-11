#include "md5.h"

/*将字符串填充到512bit(64B)对齐，顺便将数据复制到类内*/
void md5::stringPadding(string a, unsigned long long pad_file_len)
{
	//用64bit记录原文长度，文件长度使用参数
	unsigned long long former_length = (pad_file_len > 0 ? pad_file_len : a.length()) * 8;
	//计算要填充的长度和填充后的长度
	int pad_len = a.length() % 64 < 56 ? 64 - a.length() % 64 : 128 - a.length() % 64;
	len = a.length() + pad_len;
	//定义缓冲区，读入数据
	char *temp = new char[len];
	strcpy_s(temp, len, a.c_str());
	//填充数据，这里使用memset填充0，然后填充开头的1
	memset(&temp[a.length()], 0, pad_len);
	temp[a.length()] = 0x80;
	//填充64Bit的长度
	memcpy_s(&temp[len-8], 8, &former_length, sizeof(former_length));
	//将填充好的数据复制到内部整形指针data中
	data = new unsigned[len / 4];
	memcpy_s(data, len, temp, len);
	return;
}

#define make_func(name) \
 inline unsigned name##name(unsigned a, unsigned b, unsigned c, unsigned d, unsigned k, unsigned s, unsigned i) { \
	return b + rol((a + name(b, c, d) + k + T(i)), s);}
/*定义FF,GG,HH,II*/
make_func(F)/* FF[abcd, k, s, i]*/
make_func(G)/* GG[abcd, k, s, i]*/
make_func(H)/* HH[abcd, k, s, i]*/
make_func(I)/* II[abcd, k, s, i]*/
/*执行FF,GG,HH,II*/
#define exec_ABCD(name,k,s,i) A = name(A, B, C, D, block[k], s, i)
#define exec_DABC(name,k,s,i) D = name(D, A, B, C, block[k], s, i)
#define exec_CDAB(name,k,s,i) C = name(C, D, A, B, block[k], s, i)
#define exec_BCDA(name,k,s,i) B = name(B, C, D, A, block[k], s, i)

/*对一个512bit消息块循环运算*/
void md5::blockLoop(unsigned * block)
{
	/*for (int i = 0; i < 16; i++) {
		printf("%08x ", block[i]);
	}*/
	unsigned A0 = A, B0 = B, C0 = C, D0 = D;
	/*第一轮运算*/
	exec_ABCD(FF, 0, 7, 1); exec_DABC(FF, 1, 12, 2); exec_CDAB(FF, 2, 17, 3); exec_BCDA(FF, 3, 22, 4);
	exec_ABCD(FF, 4, 7, 5); exec_DABC(FF, 5, 12, 6); exec_CDAB(FF, 6, 17, 7); exec_BCDA(FF, 7, 22, 8);
	exec_ABCD(FF, 8, 7, 9); exec_DABC(FF, 9, 12, 10); exec_CDAB(FF, 10, 17, 11); exec_BCDA(FF, 11, 22, 12);
	exec_ABCD(FF, 12, 7, 13); exec_DABC(FF, 13, 12, 14); exec_CDAB(FF, 14, 17, 15); exec_BCDA(FF, 15, 22, 16);
	
	//printf("A:%08x\nB:%08x\nC:%08x\nD:%08x\n", A, B, C, D);
	/*第二轮运算*/
	exec_ABCD(GG, 1, 5, 17); exec_DABC(GG, 6, 9, 18); exec_CDAB(GG, 11, 14, 19); exec_BCDA(GG, 0, 20, 20);
	exec_ABCD(GG, 5, 5, 21); exec_DABC(GG, 10, 9, 22); exec_CDAB(GG, 15, 14, 23); exec_BCDA(GG, 4, 20, 24);
	exec_ABCD(GG, 9, 5, 25); exec_DABC(GG, 14, 9, 26); exec_CDAB(GG, 3, 14, 27); exec_BCDA(GG, 8, 20, 28);
	exec_ABCD(GG, 13, 5, 29); exec_DABC(GG, 2, 9, 30); exec_CDAB(GG, 7, 14, 31); exec_BCDA(GG, 12, 20, 32);
	
	//printf("A:%08x\nB:%08x\nC:%08x\nD:%08x\n", A, B, C, D);
	/*第三轮运算*/
	exec_ABCD(HH, 5, 4, 33); exec_DABC(HH, 8, 11, 34); exec_CDAB(HH, 11, 16, 35); exec_BCDA(HH, 14, 23, 36);
	exec_ABCD(HH, 1, 4, 37); exec_DABC(HH, 4, 11, 38); exec_CDAB(HH, 7, 16, 39); exec_BCDA(HH, 10, 23, 40);
	exec_ABCD(HH, 13, 4, 41); exec_DABC(HH, 0, 11, 42); exec_CDAB(HH, 3, 16, 43); exec_BCDA(HH, 6, 23, 44);
	exec_ABCD(HH, 9, 4, 45); exec_DABC(HH, 12, 11, 46); exec_CDAB(HH, 15, 16, 47); exec_BCDA(HH, 2, 23, 48);
	
	//printf("A:%08x\nB:%08x\nC:%08x\nD:%08x\n", A, B, C, D);
	/*第四轮运算*/
	exec_ABCD(II, 0, 6, 49); exec_DABC(II, 7, 10, 50); exec_CDAB(II, 14, 15, 51); exec_BCDA(II, 5, 21, 52);
	exec_ABCD(II, 12, 6, 53); exec_DABC(II, 3, 10, 54); exec_CDAB(II, 10, 15, 55); exec_BCDA(II, 1, 21, 56);
	exec_ABCD(II, 8, 6, 57); exec_DABC(II, 15, 10, 58); exec_CDAB(II, 6, 15, 59); exec_BCDA(II, 13, 21, 60);
	exec_ABCD(II, 4, 6, 61); exec_DABC(II, 11, 10, 62); exec_CDAB(II, 2, 15, 63); exec_BCDA(II, 9, 21, 64);

	/*更新变量*/
	A += A0; B += B0; C += C0; D += D0;
	//printf("A:%08x\nB:%08x\nC:%08x\nD:%08x\n", A, B, C, D);
}

void md5::dataLoop() {
	for (int index = 0; index < len / 4; index += 16) {
		blockLoop(&data[index]);
	}
}

/*小端转大端*/
unsigned s2b(unsigned a) {
	return ((a << 24) & 0xFF000000) | ((a << 8) & 0x00FF0000) | ((a >> 8) & 0x0000FF00) | ((a >> 24) & 0x000000FF);
}

string md5::cntMd5()
{
	char temp[64];//这里有大小端问题
	sprintf_s(temp, sizeof(temp), "%08x%08x%08x%08x", s2b(A), s2b(B), s2b(C), s2b(D));
	return string(temp);
}
