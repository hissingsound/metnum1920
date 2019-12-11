#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

string ask_nim() {
	string nim_s;
	cout << "Masukkan NIM: ";
	cin >> nim_s;

	return nim_s;
}

double numeralize(string &nim) {
	int res = 0;
	res += (nim.at(nim.size()-2)-'0');
	res += (nim.at(nim.size()-1)-'0');

	if (res >= 10) {
		res = res % 10 + res / 10;
	}

	double res_d = (double) res;
	return res_d;	
}

double prompt_nim() {
	string _nim = ask_nim();
	double nim = numeralize(_nim);
	
	return nim;
}