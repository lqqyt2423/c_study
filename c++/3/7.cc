#include <iostream>
#include <string>

using namespace std;

int main() {
	string s("hello world!!!");
	// c ��һ�����ã���˸�ֵ��佫�ı� s ���ַ���ֵ
	for (auto &c : s)
		c = toupper(c);
	cout << s << endl;
}