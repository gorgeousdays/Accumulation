#pragma once
#ifndef _INIT_H_
#define _INIT_H_
#include<iostream>
#include<Windows.h>
#include"user.hpp" 
#include"Draw.hpp"
using namespace std;
//init负责登录  已实现输密码时输入backspace实现回退
class Init :protected Draw {
public:
	Init();//初始化 登录或注册
	~Init() {
		system("cls");
		printf("\n\t\t\t\t\t\t运行结束 系统将在3秒后关闭");
		cout << "3  ";
		Sleep(1000);
		cout << "2  ";
		Sleep(1000);
		cout << "1...";
		Sleep(1000);
	}
	void Getusermessage();//从文件中读取users的信息
	void Login();//登录
	void isLogin();//判断登录账号密码是否匹配
	void Register();//注册
	void setlogin_success(bool t) {
		login_success = t;
	};
	bool getlogin_success() {
		return login_success;
	};
	string getuser_i_name(int i) {
		return users[i].showusername();
	}
	string getuser_i_password(int i) {
		return users[i].showpassword();
	}
	string input_username; 
	char input_password[20]="";//输入的账号密码
private:
	user users[10];//从文件中读取已存在的users信息
	bool login_success;//是否登录成功 true代表登录成功
};
#endif