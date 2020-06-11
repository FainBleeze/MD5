#include <iostream>
#include <string>
#include <fstream>
#include "md5.h"
using namespace std;

int main() {
	md5 md5_module;
	while (1) {
		string num = "", raw = "";
		//char* s = NULL; int len = 0;
		string filepath = "";
		ifstream file;
		do {
			cout << "------------------------------------------------\n";
			cout << "����������ѡ���ܣ�\n\t"
				<< "1.Ϊ�ַ�������MD5ժҪ\n\t"
				<< "2.Ϊ�ļ�����MD5ժҪ\n\t"
				<< "3.��֤�ļ�������\n\t"
				<< "(��q�˳�����)\n";
			cin >> num;
		} while (num[0] != '1'&&num[0] != '2'&&num[0] != '3'&&num[0] != 'q');
		switch (num[0]) {
		case '1':
			cout << "\n��������Ҫ����ժҪ���ַ�����\n\t";
			cin.get();
			getline(cin, raw);
			cout << "MD5(\""
				<< raw << "\") = "
				<< md5_module.computeString(raw) << endl << endl;
			break;
		case '2':
			cout << "\n��������Ҫ����ժҪ���ļ�·����\n\t";
			cin >> filepath;
			file.open(filepath, ios::binary);
			if (!file.is_open()) {
				cout << "���ļ�ʧ��!!����·����" << endl;
				break;
			}
			cout << "The MD5 value of file(\""
				<< filepath << "\") is\n\t"
				<< md5_module.computeFile(&file, filepath, true) << endl << endl;
			file.close();
			break;
		case '3':
			cout << "\n��������Ҫ�����ļ�·����\n\t";
			cin >> filepath;
			file.open(filepath, ios::binary);
			if (!file.is_open()) {
				cout << "���ļ�ʧ��!!����·����" << endl;
				break;
			}
			while (num[0] != '1' && num[0] != '2') {
				cout << "\n��ѡ����֤��ʽ��\n\t"
					<< "1.�ֶ����� md5 ֵ\n\t"
					<< "2.ʹ��ͬĿ¼�µ� md5 �ļ�\n";
				cin >> num;
			}
			if (num[0] == '1') {
				cout << "������ md5 ֵ��\n\t";
				cin >> raw;
				cout << md5_module.checkByString(&file, filepath, raw);
			}
			else {
				cout << md5_module.checkByFile(&file, filepath);
			}
			file.close();
			break;
		case 'q':
			return 0;
		default:
			cout << "δָ֪��!!����������1-3������q��\n";
			break;
		}
	}
	return 0;
}