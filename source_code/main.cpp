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
			cout << "请输入数字选择功能：\n\t"
				<< "1.为字符串生成MD5摘要\n\t"
				<< "2.为文件生成MD5摘要\n\t"
				<< "3.验证文件完整性\n\t"
				<< "(按q退出程序)\n";
			cin >> num;
		} while (num[0] != '1'&&num[0] != '2'&&num[0] != '3'&&num[0] != 'q');
		switch (num[0]) {
		case '1':
			cout << "\n请输入需要生成摘要的字符串：\n\t";
			cin.get();
			getline(cin, raw);
			cout << "MD5(\""
				<< raw << "\") = "
				<< md5_module.computeString(raw) << endl << endl;
			break;
		case '2':
			cout << "\n请输入需要生成摘要的文件路径：\n\t";
			cin >> filepath;
			file.open(filepath, ios::binary);
			if (!file.is_open()) {
				cout << "打开文件失败!!请检查路径！" << endl;
				break;
			}
			cout << "The MD5 value of file(\""
				<< filepath << "\") is\n\t"
				<< md5_module.computeFile(&file, filepath, true) << endl << endl;
			file.close();
			break;
		case '3':
			cout << "\n请输入需要检查的文件路径：\n\t";
			cin >> filepath;
			file.open(filepath, ios::binary);
			if (!file.is_open()) {
				cout << "打开文件失败!!请检查路径！" << endl;
				break;
			}
			while (num[0] != '1' && num[0] != '2') {
				cout << "\n请选择验证方式：\n\t"
					<< "1.手动输入 md5 值\n\t"
					<< "2.使用同目录下的 md5 文件\n";
				cin >> num;
			}
			if (num[0] == '1') {
				cout << "请输入 md5 值：\n\t";
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
			cout << "未知指令!!请输入数字1-3或输入q！\n";
			break;
		}
	}
	return 0;
}