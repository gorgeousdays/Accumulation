#include<iostream>
#include<string>
#include<windows.h>
#include<fstream>
#include<conio.h>
#include"Init.hpp"
#include"user.hpp"

using namespace std;


/****************初始化*****************/
Init::Init() {
	Getusermessage();//读取用户信息
	setlogin_success(false);
	char welcome[] = { "即将进入幼儿园班级信息管理系统..." };
	SetConsoleTitle(L"幼儿园班级信息管理系统");  //控制台标题 加L防止报错 参见https://blog.csdn.net/Shayne_Lee/article/details/51354610?utm_source=app
	system("color f");
	printf("欢迎使用本系统！\n");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t");
	for (int i = 0; i < strlen(welcome); i++) {
		printf("%c", welcome[i]);
		Sleep(30);
	}
	system("CLS");
	Login();
}


/****************从文件读取user的账号密码信息*****************/
void Init::Getusermessage() {
	ifstream infile("user.txt", ios::in);
	if (!infile) {
		cerr << "get usermessage error!" << endl;
		exit(1);
	}
	string username1, password1;
	int k = 0, i = 0;
	while (!infile.eof()) {
		if (k == 0) {
			getline(infile, username1);
			users[i].getusername(username1);
			k = 1;
		}
		else {
			getline(infile, password1);
			users[i].getpassword(password1);
			k = 0;
			i++;
		}  //k=0读账号，k=1读密码  		
	}
	infile.close();
}


/****************登录*****************/
void Init::Login() {
	Draw3();
	printf("\n\t\t\t\t\t\t是否已拥有账号\n\n\t\t\t\t\t\t1已拥有\n\t\t\t\t\t\t2没有并注册\n\t\t\t\t\t\t选择：");
	int num;
	cin >> num;
	if (num == 1) {
		int ty = 3;
		while (ty!=0) {
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
			while ((a = _getch()) != '\r')
			{
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
			isLogin();
			if (getlogin_success()) {
				printf("\n\t\t\t\t\t\t登录成功！即将自动跳转至操作界面");
				Sleep(100);
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
		Register();
	}
}


/****************判断登录是否成功*****************/
void Init::isLogin() {
	for (int i = 0; i <= 9; i++) {
		if (getuser_i_name(i) == input_username && getuser_i_password(i) == input_password)
			setlogin_success(true);
	}
}


/****************注册*****************/
void Init::Register() {
	string register_username;
	char register_password_pass[20]="",register_password2_pass[20]="";
	char register_password[20]="", register_password2[20]="";
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
	if (strcmp(register_password,register_password2)==0)//两次输入密码一致则存入user.txt中并跳转到操作界面 不一致则重新注册 ******可完善为注册n次即退出*****
	{
		ofstream outfile("user.txt", ios::out | ios::app);
		if (!outfile) {
			cerr << "register error!" << endl;
			exit(1);
		}
		outfile << endl << register_username << "\n" << register_password;
		cout << "\n\n\t\t\t\t\t\t注册成功！  即将自动跳转至操作界面";
		Sleep(100);
		outfile.close();
		setlogin_success(true);
	}
	else {
		cout << "\n\t\t\t\t\t\t两次输入密码不一致，请重新注册";
		Sleep(1000);
		system("CLS");
		Draw3();
		Register();
	}
}