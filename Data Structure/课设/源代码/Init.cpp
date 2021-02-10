#pragma once
#include"Init.h"
#include"AVLTree.h"
#include"UserMenu.h"
#include"AdminMenu.h"
#include<conio.h>
#include<iostream>
#include<fstream>
/****************初始化*****************/
Init::Init() {
	auto* tree=new AVLTree;
	Getusermessage(tree);//读取用户信息
	setlogin_success(0);
	char welcome[] = { "即将进入用户登录系统..." };
	SetConsoleTitle(L"用户登录系统");  //控制台标题 加L防止报错 参见https://blog.csdn.net/Shayne_Lee/article/details/51354610?utm_source=app
	system("color f");
	printf("欢迎使用本系统！\n");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t");
	for (int i = 0; i < strlen(welcome); i++) {
		printf("%c", welcome[i]);
		Sleep(50);
	}
	system("CLS");
	
	TNode *nowUser=Login(tree);//当前用户身份
	if (getlogin_success() == 1) {
		AdminMenu(tree, nowUser);
	}
	else if(getlogin_success() == 2) {
		UserMenu(tree, nowUser);
	}
	Saveusermessage(tree);//存储用户信息到文件
}

Init::~Init() {
	system("cls");
	printf("\n\t\t\t\t\t\t运行结束 系统将在3秒后关闭");
	cout << "3  ";
	Sleep(1000);
	cout << "2  ";
	Sleep(1000);
	cout << "1...";
	Sleep(1000);
}

/****************从文件读取user的账号密码信息*****************/
void Init::Getusermessage(AVLTree *tree){
	tree->getmessage();
}

void Init::Saveusermessage(AVLTree* tree) {
	tree->savemessage(tree->root);
}

//登录注册界面 实现获取登录账号密码功能 
TNode* Init::Login(AVLTree *tree) {
	Draw3();
	printf("\n\t\t\t\t\t\t是否已拥有账号\n\n\t\t\t\t\t\t1已拥有\n\t\t\t\t\t\t2没有并注册\n\t\t\t\t\t\t选择：");
	int num;
	cin >> num;
	if (num == 1) {
		int ty = 3;
		while (ty != 0) {
			if (ty < 3) {
				system("CLS");
				Draw1();
				Draw2();
			}
			printf("\n\t\t\t\t\t\t超出三次将强制退出 你还有%d次输入机会", ty);
			printf("\n\n\t\t\t\t\t\t请输入您的账号密码:\n\n\n\n\t\t\t\t\t\t账号:");
			input_username = "";
			int i = 0;//判断密码位数 i+1=密码位数
			char input_password_pass[20] = "";//用于输入密码过渡  char型可实现密码中*的退格
			cin >> input_username;
			printf("\n\n\t\t\t\t\t\t密码:");
			char a;
			while ((a = _getch()) != '\r'){
				if (a == '\b') {
					i--;
					printf("\b \b");//输错密码退一个打印空格再退一个
					continue;
				}
				input_password_pass[i++] = a;
				putchar('*');
			}
			memset(input_password, '\0', sizeof(input_password));//每次将过渡值给要判断的密码前都先将后者变为空
			for (int j = 0; j <= i - 1; j++) {
				input_password[j] = input_password_pass[j];
			}
			cout << endl;

			isLogin(tree, input_username, input_password);
			if (getlogin_success()!=0) {
				printf("\n\t\t\t\t\t\t登录成功！即将自动跳转至操作界面");
				Sleep(100);
				return tree->SearchTNode(tree->root,input_username);
				break;
			}
			ty--;
		}
		if (ty == 0) {
			printf("\n\n\t\t\t\t\t\t对不起你不能进入系统 即将关闭系统");
			Sleep(500);
			exit(0);
		}
	}
	else {
		return Register(tree);
	}
}

//根据输入账号密码判断是否登录成功 以及登录身份
void Init::isLogin(AVLTree *tree,string username,string password) {
	TNode* FindNode=tree->SearchTNode(tree->root,username);
	if (FindNode== NULL||(FindNode->getpassword()!=password)) {
		setlogin_success(0);
	}
	else {
		if (username == "admin") setlogin_success(1);
		else setlogin_success(2);
	}
}


//注册
TNode* Init::Register(AVLTree* tree) {
	string register_username;
	char register_password_pass[20] = "", register_password2_pass[20] = "";
	char register_password[20] = "", register_password2[20] = "";
	printf("\n\t\t\t\t\t\t注册:请输入您的账号密码:\n\n\n\n\t\t\t\t\t\t账号:");
	cin >> register_username;
	printf("\n\n\t\t\t\t\t\t密码:");
	char a;
	//密码以*出现并可退格的代码实现基本同登录代码
	int i = 0;
	while ((a = _getch()) != '\r') //getch在接受输入后不在屏幕上显示
	{
		if (a == '\b') {
			i--;
			printf("\b \b");//输错密码退一个打印空格再退一个
			continue;
		}
		register_password_pass[i++] = a;
		putchar('*');
	}
	for (int j = 0; j <= i - 1; j++) {
		register_password[j] = register_password_pass[j];
	}
	printf("\n\t\t\t\t\t\t请再次输入密码:");
	i = 0;
	while ((a = _getch()) != '\r')
	{
		if (a == '\b') {
			i--;
			printf("\b \b");//输错密码退一个打印空格再退一个
			continue;
		}
		register_password2_pass[i++] = a;
		putchar('*');
	}
	for (int j = 0; j <= i - 1; j++) {
		register_password2[j] = register_password2_pass[j];
	}
	if (strcmp(register_password, register_password2) == 0)//两次输入密码一致则存入user.txt中并跳转到操作界面 不一致则重新注册 ******可完善为注册n次即退出*****
    {
		tree->addUser(register_username, register_password);
		cout << "\n\n\t\t\t\t\t\t注册成功！  即将自动跳转至操作界面";
		Sleep(100);
		setlogin_success(2);
		return tree->SearchTNode(tree->root,register_username);
	}
	else {
		cout << "\n\t\t\t\t\t\t两次输入密码不一致，请重新注册";
		Sleep(1000);
		system("CLS");
		Draw3();
		Register(tree);
	}
}