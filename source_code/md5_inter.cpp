#include "md5.h"

void md5::initialize()
{
	A = intA; B = intB; C = intC; D = intD;
	len = 0;
	if (data != NULL)
		delete data;
}

string md5::computeString(string s)
{
	initialize();//初始化
	stringPadding(s);//填充字节
	dataLoop();//循环计算
	return cntMd5();//生成摘要
}

string md5::computeFile(ifstream * file, string filepath, bool genMd5File)
{
	initialize();//初始化
	char buf[512];
	memset(buf, 0, sizeof(buf));
	unsigned long long file_len = 0;
	for (file->read(buf, 512); !file->eof(); file->read(buf, 512)) {
		file_len += file->gcount();
		blockLoop((unsigned*)buf);
		memset(buf, 0, sizeof(buf));
	}
	file_len += file->gcount();
	//printf("len:%d", file_len);
	stringPadding(string(buf), file_len);//最后一部分填充字节
	dataLoop();//最后一部分循环计算

	string res = cntMd5();
	if (genMd5File) {
		string md5_path = filepath.append(".md5");
		ofstream md5_file;
		md5_file.open(md5_path, ios::ate);
		if (!md5_file.is_open()) {
			printf("创建md5文件失败!!"); return "";
		}
		md5_file << res;
		md5_file.close();
	}
	return res;
}

string md5::checkByString(ifstream * file, string filepath, string md5_code)
{
	string res = "重新计算 " + filepath+" 的md5值为：\n\t";
	string cmptRes = computeFile(file, filepath);
	res += cmptRes;
	res += "\n您输入的 md5 值为：\n\t";
	res += md5_code;
	if (cmptRes == md5_code) {
		res += "\n匹配：文件完整！\n\n";
	}
	else {
		res += "\n不匹配：文件已被修改！\n\n";
	}
	return res;
}

string md5::checkByFile(ifstream * file, string filepath)
{
	string res = "重新计算 " + filepath + " 的md5值为：\n\t";
	string cmptRes = computeFile(file, filepath);
	res += cmptRes;
	string md5_code;
	string md5path = filepath.append(".md5");
	ifstream md5_file;
	md5_file.open(md5path);
	if (!md5_file.is_open()) {
		res += "\n" + md5path + " 文件不存在，无法测试完整性！！\n\n";
		return res;
	}
	md5_file >> md5_code;
	md5_file.close();
	res += "\n原先计算的 md5 值为：\n\t";
	res += md5_code;
	if (cmptRes == md5_code) {
		res += "\n匹配：文件完整！\n\n";
	}
	else {
		res += "\n不匹配：文件已被修改！\n\n";
	}
	return res;
}
