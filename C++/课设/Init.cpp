#include<iostream>
#include<string>
#include<windows.h>
#include<fstream>
#include<conio.h>
#include"Init.hpp"
#include"user.hpp"

using namespace std;


/****************��ʼ��*****************/
Init::Init() {
	Getusermessage();//��ȡ�û���Ϣ
	setlogin_success(false);
	char welcome[] = { "���������׶�԰�༶��Ϣ����ϵͳ..." };
	SetConsoleTitle(L"�׶�԰�༶��Ϣ����ϵͳ");  //����̨���� ��L��ֹ���� �μ�https://blog.csdn.net/Shayne_Lee/article/details/51354610?utm_source=app
	system("color f");
	printf("��ӭʹ�ñ�ϵͳ��\n");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t");
	for (int i = 0; i < strlen(welcome); i++) {
		printf("%c", welcome[i]);
		Sleep(30);
	}
	system("CLS");
	Login();
}


/****************���ļ���ȡuser���˺�������Ϣ*****************/
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
		}  //k=0���˺ţ�k=1������  		
	}
	infile.close();
}


/****************��¼*****************/
void Init::Login() {
	Draw3();
	printf("\n\t\t\t\t\t\t�Ƿ���ӵ���˺�\n\n\t\t\t\t\t\t1��ӵ��\n\t\t\t\t\t\t2û�в�ע��\n\t\t\t\t\t\tѡ��");
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
			printf("\n\t\t\t\t\t\t�������ν�ǿ���˳� �㻹��%d���������", ty);
			printf("\n\n\t\t\t\t\t\t�����������˺�����:\n\n\n\n\t\t\t\t\t\t�˺�:");
			input_username = "";
			int i = 0;//�ж�����λ�� i+1=����λ��
			char input_password_pass[20] = "";//���������������  char�Ϳ�ʵ��������*���˸�
			cin >> input_username;
			printf("\n\n\t\t\t\t\t\t����:");
			char a;
			while ((a = _getch()) != '\r')
			{
				if (a == '\b') {
					i--;
					printf("\b \b");//���������һ����ӡ�ո�����һ��
					continue;
				}
				input_password_pass[i++] = a;
				putchar('*');
			}
			memset(input_password, '\0', sizeof(input_password));//ÿ�ν�����ֵ��Ҫ�жϵ�����ǰ���Ƚ����߱�Ϊ��
			for (int j = 0; j <= i - 1; j++) {
				input_password[j] = input_password_pass[j];
			}
			cout << endl;
			isLogin();
			if (getlogin_success()) {
				printf("\n\t\t\t\t\t\t��¼�ɹ��������Զ���ת����������");
				Sleep(100);
				break;
			}
			ty--;
		}
		if (ty == 0) {
			printf("\n\n\t\t\t\t\t\t�Բ����㲻�ܽ���ϵͳ �����ر�ϵͳ");
			Sleep(500);
			exit(0);
		}
	}
	else {
		Register();
	}
}


/****************�жϵ�¼�Ƿ�ɹ�*****************/
void Init::isLogin() {
	for (int i = 0; i <= 9; i++) {
		if (getuser_i_name(i) == input_username && getuser_i_password(i) == input_password)
			setlogin_success(true);
	}
}


/****************ע��*****************/
void Init::Register() {
	string register_username;
	char register_password_pass[20]="",register_password2_pass[20]="";
	char register_password[20]="", register_password2[20]="";
	printf("\n\t\t\t\t\t\tע��:�����������˺�����:\n\n\n\n\t\t\t\t\t\t�˺�:");
	cin >> register_username;
	printf("\n\n\t\t\t\t\t\t����:");
	char a;
	//������*���ֲ����˸�Ĵ���ʵ�ֻ���ͬ��¼����
	int i = 0;
	while ((a = _getch()) != '\r') //getch�ڽ������������Ļ����ʾ
	{
		if (a == '\b') {
			i--;
			printf("\b \b");//���������һ����ӡ�ո�����һ��
			continue;
		}
		register_password_pass[i++] = a;
		putchar('*');
	}
	for (int j = 0; j <= i - 1; j++) {
		register_password[j] = register_password_pass[j];
	}
	printf("\n\t\t\t\t\t\t���ٴ���������:");
	i = 0;
	while ((a = _getch()) != '\r')
	{
		if (a == '\b') {
			i--;
			printf("\b \b");//���������һ����ӡ�ո�����һ��
			continue;
		}
		register_password2_pass[i++] = a;
		putchar('*');
	}
	for (int j = 0; j <= i - 1; j++) {
		register_password2[j] = register_password2_pass[j];
	}
	if (strcmp(register_password,register_password2)==0)//������������һ�������user.txt�в���ת���������� ��һ��������ע�� ******������Ϊע��n�μ��˳�*****
	{
		ofstream outfile("user.txt", ios::out | ios::app);
		if (!outfile) {
			cerr << "register error!" << endl;
			exit(1);
		}
		outfile << endl << register_username << "\n" << register_password;
		cout << "\n\n\t\t\t\t\t\tע��ɹ���  �����Զ���ת����������";
		Sleep(100);
		outfile.close();
		setlogin_success(true);
	}
	else {
		cout << "\n\t\t\t\t\t\t�����������벻һ�£�������ע��";
		Sleep(1000);
		system("CLS");
		Draw3();
		Register();
	}
}