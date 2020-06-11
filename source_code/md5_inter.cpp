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
	initialize();//��ʼ��
	stringPadding(s);//����ֽ�
	dataLoop();//ѭ������
	return cntMd5();//����ժҪ
}

string md5::computeFile(ifstream * file, string filepath, bool genMd5File)
{
	initialize();//��ʼ��
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
	stringPadding(string(buf), file_len);//���һ��������ֽ�
	dataLoop();//���һ����ѭ������

	string res = cntMd5();
	if (genMd5File) {
		string md5_path = filepath.append(".md5");
		ofstream md5_file;
		md5_file.open(md5_path, ios::ate);
		if (!md5_file.is_open()) {
			printf("����md5�ļ�ʧ��!!"); return "";
		}
		md5_file << res;
		md5_file.close();
	}
	return res;
}

string md5::checkByString(ifstream * file, string filepath, string md5_code)
{
	string res = "���¼��� " + filepath+" ��md5ֵΪ��\n\t";
	string cmptRes = computeFile(file, filepath);
	res += cmptRes;
	res += "\n������� md5 ֵΪ��\n\t";
	res += md5_code;
	if (cmptRes == md5_code) {
		res += "\nƥ�䣺�ļ�������\n\n";
	}
	else {
		res += "\n��ƥ�䣺�ļ��ѱ��޸ģ�\n\n";
	}
	return res;
}

string md5::checkByFile(ifstream * file, string filepath)
{
	string res = "���¼��� " + filepath + " ��md5ֵΪ��\n\t";
	string cmptRes = computeFile(file, filepath);
	res += cmptRes;
	string md5_code;
	string md5path = filepath.append(".md5");
	ifstream md5_file;
	md5_file.open(md5path);
	if (!md5_file.is_open()) {
		res += "\n" + md5path + " �ļ������ڣ��޷����������ԣ���\n\n";
		return res;
	}
	md5_file >> md5_code;
	md5_file.close();
	res += "\nԭ�ȼ���� md5 ֵΪ��\n\t";
	res += md5_code;
	if (cmptRes == md5_code) {
		res += "\nƥ�䣺�ļ�������\n\n";
	}
	else {
		res += "\n��ƥ�䣺�ļ��ѱ��޸ģ�\n\n";
	}
	return res;
}
