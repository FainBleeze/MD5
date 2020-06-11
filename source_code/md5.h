#pragma once
#include <string>
#include <fstream>
using namespace std;

/*循环左移*/
static inline unsigned rol(unsigned val, int size)
{
	unsigned res = val << size;
	res |= val >> (32 - size);
	return res;
}

/*四个非线性基本函数*/
static inline unsigned F(unsigned x, unsigned y, unsigned z){
	return (x&y) | (~x&z);
}
static inline unsigned G(unsigned x, unsigned y, unsigned z){
	return (x&z) | (y&~z);
}
static inline unsigned H(unsigned x, unsigned y, unsigned z){
	return x^y^z;
}
static inline unsigned I(unsigned x, unsigned y, unsigned z){
	return y ^ (x | ~z);
}
/*获取T[i]*/
static inline unsigned T(unsigned i) {
	return 4294967296 * abs(sin(i));
}

/*四个初始向量*/
#define intA 0x67452301
#define intB 0xefcdab89
#define intC 0x98badcfe
#define intD 0x10325476

class md5
{
private:
	/*初始变量*/
	unsigned A;
	unsigned B;
	unsigned C;
	unsigned D;
	/*待处理的原文*/
	unsigned* data = NULL;
	/*原文字节长度*/
	unsigned len;
private:
	/*填充数据到512bit的倍数*/
	void stringPadding(string a, unsigned long long pad_file_len = 0);
	/*对一个512bit消息块循环运算*/
	void blockLoop(unsigned* block);
	void dataLoop();
	string cntMd5();
public:
	/*数据初始化*/
	void initialize();
	string computeString(string s);
	string computeFile(ifstream* file, string filepath, bool genMd5File = false);
	string checkByString(ifstream* file, string filepath, string md5_code);
	string checkByFile(ifstream* file, string filepath);
};

