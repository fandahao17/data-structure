//
// Created by fandahao2017 on 2018/9/7.
//

#include "string"
#include "iostream"
#include "cctype"

using std::string;
using std::cout;
int main(){
  string s = "fandahao";
  for (auto &item : s) {
    cout << item;
  }
  for (decltype(s.size()) i = 0; i < s.size(); ++i) {
    // It is terrible that TOUPPER actually returns an integer.
    s[i] = toupper(s[i]);
    cout << s[i];
  }
  cout << std::endl;
  return 0;
}


