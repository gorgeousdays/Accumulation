#pragma once
#ifndef _INIT_H_
#define _INIT_H_
#include<iostream>
#include<Windows.h>
#include"user.hpp" 
#include"Draw.hpp"
using namespace std;
//init�����¼  ��ʵ��������ʱ����backspaceʵ�ֻ���
class Init :protected Draw {
public:
	Init();//��ʼ�� ��¼��ע��
	~Init() {
		system("cls");
		printf("\n\t\t\t\t\t\t���н��� ϵͳ����3���ر�");
		cout << "3  ";
		Sleep(1000);
		cout << "2  ";
		Sleep(1000);
		cout << "1...";
		Sleep(1000);
	}
	void Getusermessage();//���ļ��ж�ȡusers����Ϣ
	void Login();//��¼
	void isLogin();//�жϵ�¼�˺������Ƿ�ƥ��
	void Register();//ע��
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
	char input_password[20]="";//������˺�����
private:
	user users[10];//���ļ��ж�ȡ�Ѵ��ڵ�users��Ϣ
	bool login_success;//�Ƿ��¼�ɹ� true�����¼�ɹ�
};
#endif