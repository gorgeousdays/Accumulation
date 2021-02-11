#include<iostream>
#include<fstream>
#include<vector>
#include<conio.h>
#include "Menu.hpp"
#include "Child.hpp"
#include "List.hpp"
using namespace std;


//ö���� ����Switch_Menu()����
typedef enum Menulist
{
	Exit, Add, Change, Delete, Search, Show, Statistics
}MENULIST;


//����Ϊȫ�ֱ��� �򻯲��� ����ÿ����������Ҫ����
string name_i;
string birth_i;
bool sex_i;
string address_i;
double height_i;
double weight_i;
string father_name_i;
string father_phonenumber_i;
string mother_name_i;
string mother_phonenumber_i;
string remark_i;


//����������Ϣ
void Getmessage() {
	cout << "\n\t\t\t\t\t\t����������:"; cin >> name_i;
	cout << "\t\t\t\t\t\t�������������:"; cin >> birth_i;
	cout << "\t\t\t\t\t\t�������Ա�(0Ů/1��):"; cin >> sex_i;
	cout << "\t\t\t\t\t\t�������ַ:"; cin >> address_i;
	cout << "\t\t\t\t\t\t���������:"; cin >> height_i;
	cout << "\t\t\t\t\t\t����������:"; cin >> weight_i;
	cout << "\t\t\t\t\t\t��������:"; cin >> father_name_i;
	cout << "\t\t\t\t\t\t���׵绰:"; cin >> father_phonenumber_i;
	cout << "\t\t\t\t\t\tĸ������:"; cin >> mother_name_i;
	cout << "\t\t\t\t\t\tĸ�׵绰:"; cin >> mother_phonenumber_i;
	cout << "\t\t\t\t\t\t��ע��Ϣ:"; cin >> remark_i;
	cout << endl;
	Sleep(500);
}


/****************���ļ���ȡС������Ϣ*****************/
Menu::Menu() {
	ifstream infile("children.txt", ios::in);
	if (!infile)
	{
		cerr << "�ļ���ȡ����!" << endl;
		exit(1);
	}
	int i = 0;
	//����ȡ�ɹ�ʱ���ļ���Ϣ����children������
	while (infile >> name_i >> birth_i >> sex_i >> address_i >> height_i >> weight_i >> father_name_i >> father_phonenumber_i >>mother_name_i>>mother_phonenumber_i>> remark_i) 
	{
		children[i].setchild(name_i, birth_i, sex_i, address_i, height_i, weight_i, father_name_i, father_phonenumber_i,mother_name_i,mother_phonenumber_i,remark_i);
		i++;
	}
	children_num = i;
	infile.close();
	Switch_Menu();
}


/****************����������Ϣ����ļ�*****************/
Menu::~Menu(){
	ofstream outfile("children.txt", ios::out);
	if (!outfile)    //�����ļ��򿪲����Ƿ�ɹ������ɹ�����ʾ���˳���
	{
		cerr << "�ļ���ȡʧ��!" << endl;
		exit(1);
	}
	for (int i = 0; i < children_num;i++)
	{
		Sleep(100);
		outfile << children[i].name << " ";
		outfile << children[i].birth << " ";
		outfile << children[i].sex << " ";
		outfile << children[i].address << " ";
		outfile << children[i].height << " ";
		outfile << children[i].weight << " ";
		outfile << children[i].father_name << " ";
		outfile << children[i].father_phonenumber << " ";
		outfile << children[i].mother_name << " ";
		outfile << children[i].mother_phonenumber << " ";
		outfile << children[i].remark << " ";
		outfile << endl;
	}
	outfile.close();
}


/****************�˵����� ����ѡ��*****************/
int Menu::MenuSelect() {
	char c;
	do
	{
		system("cls");
		Draw3();
		printf("\n");
		printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
		printf("\t\t\t\t   ��              �׶�԰�༶��Ϣ����ϵͳ        ��\n");
		printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
		printf("\t\t\t\t   ����������������������������������������������������������������������������������������-��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 1. �����Ϣ                    2. �޸���Ϣ ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 3. ɾ����Ϣ                    4. ��ѯ��Ϣ ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 5. ��ʾȫ��                    6. ��Ů���� ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 0. �˳�����                                ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   ��������������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t\t\t  ����ѡ��(0-7):");
		c = _getch();  //��ȡ�ַ����ɼ�
	} while (c < '0' || c > '6');
	return c - '0';
}


/****************���ݲ˵�����ķ���ֵ  ��ת��Ӧ����*****************/
void Menu::Switch_Menu() {
	switch (MenuSelect())	//�˵�ѡ��
	{
	case Exit:		//�˳�����
		system("cls");
		Draw3();
		Quit();	//�˳��򷵻����˵�
		break;
	case Add:	//���С������Ϣ
		system("cls");
		Add_Information();
		Quit();
		break;
	case Change:	//�޸�С������Ϣ
		system("cls");
		Change_Information();
		Quit();
		break;
	case Delete:	//ɾ��С������Ϣ
		system("cls");
		Delete_Information();
		Quit();
		break;
	case Search:	//��ѯС������Ϣ ***ע��ʵ�����ֲ�ѯ***
		system("cls");
		Search_Information();
		Quit();
		break;
	case Show:		//��ʾ����С������Ϣ ****д����ʱע��ʵ����������*****
		system("cls");
		Show_Information();
		Quit();
		break;
	case Statistics:		//ͳ��С������Ů����
		system("cls");
		Statistics_Information();
		Quit();
		break;
	}
}

/****************�˳�����*****************/
void Menu::Quit() {
	char ch;
	printf("\n\n\t\t\t\tҪ���ص�¼���水�����\t\t�˳������밴Esc��\n");
	ch = _getch();
	if (ch == 0x1b)	//esc������
	{
		cout << "\n\t\t\t\t\t\t��лʹ��";
		Sleep(500);
	}
	//���½������˵�
	else {
		Switch_Menu();
	}
}


/****************������Ϣ����*****************/
void Menu::Add_Information(){
	char t;
	do {
		Getmessage();
		children[children_num].setchild(name_i, birth_i, sex_i, address_i, height_i, weight_i, father_name_i, father_phonenumber_i, mother_name_i, mother_phonenumber_i, remark_i);
		children_num++;
		cout << "\t\t\t\t\t\t������Ϣ�ɹ�!" << endl;
		cout << "\n\t\t\t\t\t\t" << "�Ƿ�������" ;
		cout << "\n\t\t\t\t\t\t" << "1:��";
		cout << "\n\t\t\t\t\t\t" << "2:��";
		t = _getch();
	} while (t == 49);
	cout << "\n\t\t\t\t\t\t����һ����" << children_num << "��С����";
}


/****************�޸���Ϣ����*****************/
void Menu::Change_Information() {
	string name_i2, father_phonenumber_i2;
	int i = 0;
	int position = 0;//�ڼ���С����
	cout << "\n\t\t\t\t\t\t������Ҫ������Ϣ��С���ѵ�����:"; cin >> name_i2;
	int judge = 0;//������ҵ����������ֵ�С����
	for (i = 0; i < children_num; i++) {
		if (children[i].name == name_i2) {
			judge++;
			position = i;
		}
	}
	//�������������С���� ��Ҫ������໤����Ϣ
	if (judge == 0) {
		cout << "\n\t\t\t\t\t\t�����ڸ�С������Ϣ��";
		Sleep(500);
	}
	else if (judge == 1) {
		cout << "\n\t\t\t\t\t\t��������ĺ����Ϣ";
		Getmessage();
		children[position].setchild(name_i, birth_i, sex_i, address_i, height_i, weight_i, father_name_i, father_phonenumber_i, mother_name_i, mother_phonenumber_i, remark_i);
		cout << "\t\t\t\t\t\t�޸���Ϣ�ɹ�!" << endl;
	}
	else {
		cout << "\t\t\t\t\t\t�������С���Ѹ��׵ĵ绰:"; cin >> father_phonenumber_i2;//��ֹ����ͬ�����
		for (i = 0; i < children_num; i++) {
			if (children[i].father_phonenumber == father_phonenumber_i2 && children[i].name == name_i2) {
				cout << "\n\t\t\t\t\t\t��������ĺ����Ϣ";
				Getmessage();
				children[i].setchild(name_i, birth_i, sex_i, address_i, height_i, weight_i, father_name_i, father_phonenumber_i, mother_name_i, mother_phonenumber_i, remark_i);
				cout << "\t\t\t\t\t\t�޸���Ϣ�ɹ�!" << endl;
				break;
			}
			else {
				cout << "\n\t\t\t\t\t\t�����ڸ�С������Ϣ��";
				Sleep(500);
			}
		}
	}
}


/****************ɾ����Ϣ����*****************/
void Menu::Delete_Information() {
	string name_i2, father_phonenumber_i2;
	int i = 0;
	int position = 0;//�ڼ���С����
	cout << "\n\t\t\t\t\t\t������Ҫɾ����Ϣ��С���ѵ�����:"; cin >> name_i2;
	int judge = 0;//������ҵ����������ֵ�С����
	for (i = 0; i < children_num; i++) {
		if (children[i].name == name_i2) {
			judge++;
			position = i;
		}
	}
	if (judge == 0) {
		cout << "\n\t\t\t\t\t\t�����ڸ�С������Ϣ��";
		Sleep(500);
	}
	else if (judge == 1){
		cout << "\n\t\t\t\t\t\tȷ��Ҫɾ���� ɾ���󲻿ɻָ� �����ɾ��������1��";
		char t;
		t = _getch();
		if (t == 49) {
			children_num--;
			for (int j = position; j < children_num; j++) {
				children[j] = children[j + 1];
			}
			cout << "\n\t\t\t\t\t\tɾ����Ϣ�ɹ���";
			cout << "\t\t\t\t\t\t����һ����" << children_num << "��С����";
		}
	}
	else{
		cout << "\n\t\t\t\t\t\t����������С���� ��Ҫ�������С���Ѹ��׵ĵ绰:"; cin >> father_phonenumber_i2;//��ֹ����ͬ�����
		for (i = 0; i < children_num; i++) {
			if (children[i].father_phonenumber == father_phonenumber_i2 && children[i].name == name_i2) {
				children_num--;
				for (int j = i; j < children_num; j++){
					children[j] = children[j + 1];
				}
				break;
			}
		}
		if (i == children_num) {
			cout << "\n\t\t\t\t\t\t�����ڸ�С������Ϣ��";
			Sleep(500);
		}
		else{
			cout << "\n\t\t\t\t\t\tɾ����Ϣ�ɹ���";
			cout << "\n\t\t\t\t\t\t����һ����" << children_num << "��С����";
		}
	}
}


/****************������Ϣ����*****************/
void Menu::Search_Information() {
	string children_name;
	int position = 0,num=0;
	vector<int>children_position;//�洢�ҵ���С����λ�� ���С�������� ��push_back ������������������С���ѵ���Ϣ
	char t;
	cout << "\n\t\t\t\t\t\t������Ҫ��ѯ��С���ѵ�����:";
	cin >> children_name;
	for (int i = 0; i < children_num; i++) {
		if (children_name == children[i].name) {
			children_position.push_back(i);
			num++;//�ҵ�һ��Ҫ���ҵ�С���Ѿͽ�����λ����Ϣ��ջ
		}
	}
	if (num == 0) {
		cout << "\n\t\t\t\t\t\tδ�ҵ���Ϣ����";
		Sleep(100);
	}
	else
	{
		cout << "\n\t\t\t\t\t\t��ѡ���ѯ������Ϣ?";
		cout << "\n\t\t\t\t\t\t1��ĸ������绰";
		cout << "\n\t\t\t\t\t\t2:סַ";
		cout << "\n\t\t\t\t\t\t3:������Ϣ";
		t = _getch();
		int i = 1;
		switch (t - 48) {
		case 1:
			cout << endl;
			for (vector<int>::iterator it = children_position.begin(); it != children_position.end(); it++) {
				position = *it;
				if (children_position.size() != 1) {
					cout << "\n\n\t\t\t��" << i << "��С���ѵ���Ϣ:";
					i++;
				}
				cout << "\n\n\t\t\t\t\t��������:" << children[position].father_name << "\t���׵绰:" << children[position].father_phonenumber;
				cout << "\n\n\t\t\t\t\tĸ������:" << children[position].mother_name << "\tĸ�׵绰:" << children[position].mother_phonenumber;
			}
			break;
		case 2:
			cout << endl;
			for (vector<int>::iterator it = children_position.begin(); it != children_position.end(); it++) {
				position = *it;
				if (children_position.size() != 1) {
					cout << "\n\n\t\t\t��" << i << "��С���ѵ���Ϣ:";
					i++;
				}
				cout << "\n\n\t\t\t\t\t\t��ͥסַ:" << children[position].address << endl;
			}
			break;
		case 3:
			cout << endl;
			for (vector<int>::iterator it = children_position.begin(); it != children_position.end(); it++) {
				position = *it;
				if (children_position.size() != 1) {
					cout << "\n\n\t\t\t��" << i << "��С���ѵ���Ϣ:";
					i++;
				}
				cout << "\n" << "\t��������" << "\t�Ա�" << "\tסַ" << "\t���" << "\t����" << "\t����" << "\t���׵绰" << "\tĸ��" << "\tĸ�׵绰" << "\t��ע";
				cout << endl;
				cout << children[position] << endl;
			}
			break;
		}
	}
	
}


/****************��ʾ��Ϣ����*****************/
//����� ���� ������ر�����
void Menu::Show_Information() {
	char t1, t2;
	cout << "\n\t\t\t\t\t\t��ѡ��Ҫ�������Ϣ";
	cout << "\n\t\t\t\t\t\t1:���";
	cout << "\n\t\t\t\t\t\t2:����";
	cout << "\n\t\t\t\t\t\t3:������ر�";
	cout << "\n";
	t1 = _getch();
	cout << "\n\t\t\t\t\t\t��ѡ������ʽ";
	cout << "\n\t\t\t\t\t\t1:���� �ɵ͵���";
	cout << "\n\t\t\t\t\t\t2:���� �ɸߵ���";
	t2 = _getch();
	int j = 0, k = 0;
	////value����ֵ rank�洢������Ӧ��λ�� ��̬�����ڴ� ��value 5 3 4 2 ��Ӧrank 1 3 2 4 ����������������
	double* value;
	int* rank;
	int f = 1 << sizeof(int) * 8 - 1;//��С��int��������
	value = (double*)malloc(sizeof(double) * children_num);
	rank = new int[children_num];
	cout << "\n\n\t\t\t\t\t\t����һ����" << children_num << "��С����" << "  ��Ϣ����:";
	cout.setf(ios::left);
	cout<< "\n\n" <<"����"<<"\t��������" << "\t�Ա�" << "\tסַ" << "\t���" << "\t����" << "\t����" << "\t���׵绰" << "\tĸ��" << "\tĸ�׵绰" << "\t��ע";
	switch (t1 - 48) {
	case 1:
		for (int i = 0; i < children_num; i++){
			value[i] = children[i].height;
		}
		for (int i = 0; i < children_num; i++){
			for (j = 0, k = 0; j < children_num; j++)
				if (value[k] < value[j])
					k = j;
			rank[i] = k;
			value[k] = f;
		}
		switch (t2 - 48) {
		case 1:
			for (int i = children_num - 1; i >= 0; i--){
				cout <<"\n" <<children[rank[i]].name;
				cout << children[rank[i]];
			}
			break;
		case 2:
			for (int i = 0; i < children_num; i++) {
				cout << "\n" << children[rank[i]].name;
				cout << children[rank[i]];
			}
			break;
		}
		break;
	case 2:
		for (int i = 0; i < children_num; i++) {
			value[i] = children[i].weight;
		}
		for (int i = 0; i < children_num; i++) {
			for (j = 0, k = 0; j < children_num; j++)
				if (value[k] < value[j])
					k = j;
			rank[i] = k;
			value[k] = f;
		}
		switch (t2 - 48){
		case 1:
			for (int i = children_num - 1; i >= 0; i--) {
				cout << "\n" << children[rank[i]].name;
				cout << children[rank[i]];
			}
			break;
		case 2:
			for (int i = 0; i < children_num; i++) {
				cout << "\n" << children[rank[i]].name;
				cout << children[rank[i]];
			}
			break;
		}
		break;
	case 3:
		for (int i = 0; i < children_num; i++) {
			value[i] = children[i].height / children[i].weight;
		}
		for (int i = 0; i < children_num; i++) {
			for (j = 0, k = 0; j < children_num; j++)
				if (value[k] < value[j])
					k = j;
			rank[i] = k;
			value[k] = f;
		}
		switch (t2 - 48) {
		case 1:
			for (int i = children_num - 1; i >= 0; i--) {
				cout << "\n" << children[rank[i]].name;
				cout << children[rank[i]];
			}
		break;
		case 2:
			for (int i = 0; i < children_num; i++) {
				cout << "\n" << children[rank[i]].name;
				cout << children[rank[i]];
			}
	    break;
		}
		break;
	}
	free(value);
	delete[]rank;
}


/****************ͳ���Ա���*****************/
//�Ż�Ϊ�������Ů����
void Menu::Statistics_Information() {
	boyname_node* boy_head = NULL, * boy_node = NULL, boy;
	girlname_node* girl_head = NULL, * girl_node = NULL, girl;
	double boy_num = 0, girl_num = 0;
	for (int i = 0; i < children_num; i++) {
		if (children[i].sex == 1) {
			boy_num++;
			boy_node = new  boyname_node();
			if (boy_node != NULL) {
				boy_node->boyname = children[i].name;
				boy_node->next = NULL;
				if (boy_head == NULL) {
					boy_head = boy_node;
				}
				else {
					boy_node->next = boy_head;
					boy_head = boy_node;
				}
			}
		}
		else {
			girl_num++;
			girl_node = new  girlname_node();
			if (girl_node != NULL) {
				girl_node->girlname = children[i].name;
				girl_node->next = NULL;
				if (girl_head == NULL) {
					girl_head = girl_node;
				}
				else {
					girl_node->next = girl_head;
					girl_head = girl_node;
				}
			}
		}
	}
	boy.set_boy_head(boy_head);
	girl.set_girl_head(girl_head);
	cout << "\n\t\t\t\t\t\t����" << boy_num << "���к�  ";
	cout << "\n\t\t\t\t\t\t����" << girl_num << "��Ů��  ";
	if (girl_num > boy_num)
		cout << "\n\t\t\t\t\t\t��Ů����Ϊ " << "1:" << girl_num / boy_num;
	else
		cout << "\n\t\t\t\t\t\t��Ů����Ϊ " << boy_num / girl_num << ":1";
	cout << "\n\n\t\t\t\t\t\t�Ƿ�Ҫ�鿴��Ů����";
	cout << "\n\t\t\t\t\t\t1:��������";
	cout << "\n\t\t\t\t\t\t2:Ů������";
	cout << "\n\t\t\t\t\t\t3:���鿴";
	char t;
	t = _getch();
	switch (t - 48) {
	case 1:
		cout << endl;
		boy.print();
		break;
	case 2:
		cout << endl;
		girl.print();
		break;
	case 3:
		break;
	}
}