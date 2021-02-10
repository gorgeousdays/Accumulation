#pragma once
#include"Init.h"
#include"AVLTree.h"
#include"UserMenu.h"
#include"AdminMenu.h"
#include<conio.h>
#include<iostream>
#include<fstream>
/****************��ʼ��*****************/
Init::Init() {
	auto* tree=new AVLTree;
	Getusermessage(tree);//��ȡ�û���Ϣ
	setlogin_success(0);
	char welcome[] = { "���������û���¼ϵͳ..." };
	SetConsoleTitle(L"�û���¼ϵͳ");  //����̨���� ��L��ֹ���� �μ�https://blog.csdn.net/Shayne_Lee/article/details/51354610?utm_source=app
	system("color f");
	printf("��ӭʹ�ñ�ϵͳ��\n");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t");
	for (int i = 0; i < strlen(welcome); i++) {
		printf("%c", welcome[i]);
		Sleep(50);
	}
	system("CLS");
	
	TNode *nowUser=Login(tree);//��ǰ�û����
	if (getlogin_success() == 1) {
		AdminMenu(tree, nowUser);
	}
	else if(getlogin_success() == 2) {
		UserMenu(tree, nowUser);
	}
	Saveusermessage(tree);//�洢�û���Ϣ���ļ�
}

Init::~Init() {
	system("cls");
	printf("\n\t\t\t\t\t\t���н��� ϵͳ����3���ر�");
	cout << "3  ";
	Sleep(1000);
	cout << "2  ";
	Sleep(1000);
	cout << "1...";
	Sleep(1000);
}

/****************���ļ���ȡuser���˺�������Ϣ*****************/
void Init::Getusermessage(AVLTree *tree){
	tree->getmessage();
}

void Init::Saveusermessage(AVLTree* tree) {
	tree->savemessage(tree->root);
}

//��¼ע����� ʵ�ֻ�ȡ��¼�˺����빦�� 
TNode* Init::Login(AVLTree *tree) {
	Draw3();
	printf("\n\t\t\t\t\t\t�Ƿ���ӵ���˺�\n\n\t\t\t\t\t\t1��ӵ��\n\t\t\t\t\t\t2û�в�ע��\n\t\t\t\t\t\tѡ��");
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
			printf("\n\t\t\t\t\t\t�������ν�ǿ���˳� �㻹��%d���������", ty);
			printf("\n\n\t\t\t\t\t\t�����������˺�����:\n\n\n\n\t\t\t\t\t\t�˺�:");
			input_username = "";
			int i = 0;//�ж�����λ�� i+1=����λ��
			char input_password_pass[20] = "";//���������������  char�Ϳ�ʵ��������*���˸�
			cin >> input_username;
			printf("\n\n\t\t\t\t\t\t����:");
			char a;
			while ((a = _getch()) != '\r'){
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

			isLogin(tree, input_username, input_password);
			if (getlogin_success()!=0) {
				printf("\n\t\t\t\t\t\t��¼�ɹ��������Զ���ת����������");
				Sleep(100);
				return tree->SearchTNode(tree->root,input_username);
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
		return Register(tree);
	}
}

//���������˺������ж��Ƿ��¼�ɹ� �Լ���¼���
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


//ע��
TNode* Init::Register(AVLTree* tree) {
	string register_username;
	char register_password_pass[20] = "", register_password2_pass[20] = "";
	char register_password[20] = "", register_password2[20] = "";
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
	if (strcmp(register_password, register_password2) == 0)//������������һ�������user.txt�в���ת���������� ��һ��������ע�� ******������Ϊע��n�μ��˳�*****
    {
		tree->addUser(register_username, register_password);
		cout << "\n\n\t\t\t\t\t\tע��ɹ���  �����Զ���ת����������";
		Sleep(100);
		setlogin_success(2);
		return tree->SearchTNode(tree->root,register_username);
	}
	else {
		cout << "\n\t\t\t\t\t\t�����������벻һ�£�������ע��";
		Sleep(1000);
		system("CLS");
		Draw3();
		Register(tree);
	}
}