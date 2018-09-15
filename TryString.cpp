//
// Created by fandahao2017 on 2018/9/7.
//

#include "string"
#include "iostream"
#include "cctype"
#include "dbg.h"
#include <vector>

using std::string;
using std::cout;
int main(){
	string s = "fandahao";
	std::vector<string> v = {"a", "b"};
	for (auto &item : s) {
		cout << item;
	}
	std::cout << std::endl;
	debug_v("s", s);
	for (char & i : s) {
		// It is terrible that TOUPPER actually returns an integer.
		i = toupper(i);
		cout << i;
	}
	cout << std::endl;
	return 0;
}


