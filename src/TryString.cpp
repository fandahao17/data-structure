//
// Created by fandahao2017 on 2018/9/7.
//

#include "iostream"
#include "string"
#include "cctype"
#include "dbg.h"
#include <vector>

using std::string;
using std::cout;
int main(){
	string fan = "fandahao";
	std::vector<string> v = {"a", "b"};
	for (auto &item : fan) {
		cout << item;
	}
	std::cout << std::endl;
	debug_v("s", fan);
	for (char & i : fan) {
		// It is terrible that TOUPPER actually returns an integer.
		i = toupper(i);
		cout << i;
	}
	cout << std::endl;
	return 0;
}


