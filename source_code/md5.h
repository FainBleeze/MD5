#pragma once
#include <string>
#include <fstream>
using namespace std;

/*ѭ������*/
static inline unsigned rol(unsigned val, int size)
{
	unsigned res = val << size;
	res |= val >> (32 - size);
	return res;
}

/*�ĸ������Ի�������*/
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
/*��ȡT[i]*/
static inline unsigned T(unsigned i) {
	return 4294967296 * abs(sin(i));
}

/*�ĸ���ʼ����*/
#define intA 0x67452301
#define intB 0xefcdab89
#define intC 0x98badcfe
#define intD 0x10325476

class md5
{
private:
	/*��ʼ����*/
	unsigned A;
	unsigned B;
	unsigned C;
	unsigned D;
	/*�������ԭ��*/
	unsigned* data = NULL;
	/*ԭ���ֽڳ���*/
	unsigned len;
private:
	/*������ݵ�512bit�ı���*/
	void stringPadding(string a, unsigned long long pad_file_len = 0);
	/*��һ��512bit��Ϣ��ѭ������*/
	void blockLoop(unsigned* block);
	void dataLoop();
	string cntMd5();
public:
	/*���ݳ�ʼ��*/
	void initialize();
	string computeString(string s);
	string computeFile(ifstream* file, string filepath, bool genMd5File = false);
	string checkByString(ifstream* file, string filepath, string md5_code);
	string checkByFile(ifstream* file, string filepath);
};

