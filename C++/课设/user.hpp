#pragma once
#ifndef _USER_H_
#define _USER_H_
#include<iostream>
#include<cstring>
using namespace std;
class user {
public:
	user() {
		username = ""; password = "";
	}
	string showusername() {
		return username;
	}
	string showpassword() {
		return password;
	}
	void getusername(string name) {
		username = name;
	}
	void getpassword(string test_password) {
		password = test_password;
	}
protected:
	string username, password;
};
#endif 