#pragma once
#include<iostream>
#include<cstring>
#include "khaibao.h"

using namespace std;

string noSpaceWord(string s){
	string ans;
	for(int i = 0; i < s.size(); i++ ){
		if(s[i] != ' '){
			ans += s[i];
		}
	}
	return ans;
}
