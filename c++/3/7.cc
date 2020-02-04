#include <iostream>
#include <string>

using namespace std;

int main() {
	string s("hello world!!!");
	// c 是一个引用，因此赋值语句将改变 s 中字符的值
	for (auto &c : s)
		c = toupper(c);
	cout << s << endl;
}