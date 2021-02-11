#include<iostream>
#include<fstream>
#include<vector>
#include<conio.h>
#include "Menu.hpp"
#include "Child.hpp"
#include "List.hpp"
using namespace std;


//枚举类 用于Switch_Menu()函数
typedef enum Menulist
{
	Exit, Add, Change, Delete, Search, Show, Statistics
}MENULIST;


//设置为全局变量 简化操作 不必每个函数都需要定义
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


//负责输入信息
void Getmessage() {
	cout << "\n\t\t\t\t\t\t请输入姓名:"; cin >> name_i;
	cout << "\t\t\t\t\t\t请输入出生年月:"; cin >> birth_i;
	cout << "\t\t\t\t\t\t请输入性别(0女/1男):"; cin >> sex_i;
	cout << "\t\t\t\t\t\t请输入地址:"; cin >> address_i;
	cout << "\t\t\t\t\t\t请输入身高:"; cin >> height_i;
	cout << "\t\t\t\t\t\t请输入体重:"; cin >> weight_i;
	cout << "\t\t\t\t\t\t父亲姓名:"; cin >> father_name_i;
	cout << "\t\t\t\t\t\t父亲电话:"; cin >> father_phonenumber_i;
	cout << "\t\t\t\t\t\t母亲姓名:"; cin >> mother_name_i;
	cout << "\t\t\t\t\t\t母亲电话:"; cin >> mother_phonenumber_i;
	cout << "\t\t\t\t\t\t备注信息:"; cin >> remark_i;
	cout << endl;
	Sleep(500);
}


/****************从文件读取小朋友信息*****************/
Menu::Menu() {
	ifstream infile("children.txt", ios::in);
	if (!infile)
	{
		cerr << "文件读取错误!" << endl;
		exit(1);
	}
	int i = 0;
	//当读取成功时从文件信息读入children对象中
	while (infile >> name_i >> birth_i >> sex_i >> address_i >> height_i >> weight_i >> father_name_i >> father_phonenumber_i >>mother_name_i>>mother_phonenumber_i>> remark_i) 
	{
		children[i].setchild(name_i, birth_i, sex_i, address_i, height_i, weight_i, father_name_i, father_phonenumber_i,mother_name_i,mother_phonenumber_i,remark_i);
		i++;
	}
	children_num = i;
	infile.close();
	Switch_Menu();
}


/****************将处理后的信息输回文件*****************/
Menu::~Menu(){
	ofstream outfile("children.txt", ios::out);
	if (!outfile)    //测试文件打开操作是否成功，不成功则提示后退出。
	{
		cerr << "文件读取失败!" << endl;
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


/****************菜单界面 返回选择*****************/
int Menu::MenuSelect() {
	char c;
	do
	{
		system("cls");
		Draw3();
		printf("\n");
		printf("\t\t\t\t   ╭═════════════════════════════════○●○●═══╮\n");
		printf("\t\t\t\t   │              幼儿园班级信息管理系统        │\n");
		printf("\t\t\t\t   ╰═══○●○●═════════════════════════════════╯\n");
		printf("\t\t\t\t   ┌───────────────────────────────────────────-┐\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 1. 添加信息                    2. 修改信息 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 3. 删除信息                    4. 查询信息 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 5. 显示全部                    6. 男女比例 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 0. 退出程序                                │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   └────────────────────────────────────────────┘\n");
		printf("\t\t\t\t\t\t  请您选择(0-7):");
		c = _getch();  //获取字符不可见
	} while (c < '0' || c > '6');
	return c - '0';
}


/****************根据菜单界面的返回值  跳转相应函数*****************/
void Menu::Switch_Menu() {
	switch (MenuSelect())	//菜单选择
	{
	case Exit:		//退出程序
		system("cls");
		Draw3();
		Quit();	//退出或返回主菜单
		break;
	case Add:	//添加小朋友信息
		system("cls");
		Add_Information();
		Quit();
		break;
	case Change:	//修改小朋友信息
		system("cls");
		Change_Information();
		Quit();
		break;
	case Delete:	//删除小朋友信息
		system("cls");
		Delete_Information();
		Quit();
		break;
	case Search:	//查询小朋友信息 ***注意实现两种查询***
		system("cls");
		Search_Information();
		Quit();
		break;
	case Show:		//显示所有小朋友信息 ****写代码时注意实现两种排序*****
		system("cls");
		Show_Information();
		Quit();
		break;
	case Statistics:		//统计小朋友男女比例
		system("cls");
		Statistics_Information();
		Quit();
		break;
	}
}

/****************退出函数*****************/
void Menu::Quit() {
	char ch;
	printf("\n\n\t\t\t\t要返回登录界面按任意键\t\t退出程序请按Esc键\n");
	ch = _getch();
	if (ch == 0x1b)	//esc键按下
	{
		cout << "\n\t\t\t\t\t\t感谢使用";
		Sleep(500);
	}
	//重新进入主菜单
	else {
		Switch_Menu();
	}
}


/****************增加信息函数*****************/
void Menu::Add_Information(){
	char t;
	do {
		Getmessage();
		children[children_num].setchild(name_i, birth_i, sex_i, address_i, height_i, weight_i, father_name_i, father_phonenumber_i, mother_name_i, mother_phonenumber_i, remark_i);
		children_num++;
		cout << "\t\t\t\t\t\t增加信息成功!" << endl;
		cout << "\n\t\t\t\t\t\t" << "是否继续添加" ;
		cout << "\n\t\t\t\t\t\t" << "1:是";
		cout << "\n\t\t\t\t\t\t" << "2:否";
		t = _getch();
	} while (t == 49);
	cout << "\n\t\t\t\t\t\t现在一共有" << children_num << "个小朋友";
}


/****************修改信息函数*****************/
void Menu::Change_Information() {
	string name_i2, father_phonenumber_i2;
	int i = 0;
	int position = 0;//第几个小朋友
	cout << "\n\t\t\t\t\t\t请输入要更改信息的小朋友的姓名:"; cin >> name_i2;
	int judge = 0;//计算查找到几个该名字的小朋友
	for (i = 0; i < children_num; i++) {
		if (children[i].name == name_i2) {
			judge++;
			position = i;
		}
	}
	//如果存在重名的小朋友 则要再输入监护人信息
	if (judge == 0) {
		cout << "\n\t\t\t\t\t\t不存在该小朋友信息！";
		Sleep(500);
	}
	else if (judge == 1) {
		cout << "\n\t\t\t\t\t\t请输入更改后的信息";
		Getmessage();
		children[position].setchild(name_i, birth_i, sex_i, address_i, height_i, weight_i, father_name_i, father_phonenumber_i, mother_name_i, mother_phonenumber_i, remark_i);
		cout << "\t\t\t\t\t\t修改信息成功!" << endl;
	}
	else {
		cout << "\t\t\t\t\t\t请输入该小朋友父亲的电话:"; cin >> father_phonenumber_i2;//防止出现同名情况
		for (i = 0; i < children_num; i++) {
			if (children[i].father_phonenumber == father_phonenumber_i2 && children[i].name == name_i2) {
				cout << "\n\t\t\t\t\t\t请输入更改后的信息";
				Getmessage();
				children[i].setchild(name_i, birth_i, sex_i, address_i, height_i, weight_i, father_name_i, father_phonenumber_i, mother_name_i, mother_phonenumber_i, remark_i);
				cout << "\t\t\t\t\t\t修改信息成功!" << endl;
				break;
			}
			else {
				cout << "\n\t\t\t\t\t\t不存在该小朋友信息！";
				Sleep(500);
			}
		}
	}
}


/****************删除信息函数*****************/
void Menu::Delete_Information() {
	string name_i2, father_phonenumber_i2;
	int i = 0;
	int position = 0;//第几个小朋友
	cout << "\n\t\t\t\t\t\t请输入要删除信息的小朋友的姓名:"; cin >> name_i2;
	int judge = 0;//计算查找到几个该名字的小朋友
	for (i = 0; i < children_num; i++) {
		if (children[i].name == name_i2) {
			judge++;
			position = i;
		}
	}
	if (judge == 0) {
		cout << "\n\t\t\t\t\t\t不存在该小朋友信息！";
		Sleep(500);
	}
	else if (judge == 1){
		cout << "\n\t\t\t\t\t\t确定要删除吗 删除后不可恢复 若坚持删除则输入1！";
		char t;
		t = _getch();
		if (t == 49) {
			children_num--;
			for (int j = position; j < children_num; j++) {
				children[j] = children[j + 1];
			}
			cout << "\n\t\t\t\t\t\t删除信息成功！";
			cout << "\t\t\t\t\t\t现在一共有" << children_num << "个小朋友";
		}
	}
	else{
		cout << "\n\t\t\t\t\t\t存在重名的小朋友 需要再输入该小朋友父亲的电话:"; cin >> father_phonenumber_i2;//防止出现同名情况
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
			cout << "\n\t\t\t\t\t\t不存在该小朋友信息！";
			Sleep(500);
		}
		else{
			cout << "\n\t\t\t\t\t\t删除信息成功！";
			cout << "\n\t\t\t\t\t\t现在一共有" << children_num << "个小朋友";
		}
	}
}


/****************查找信息函数*****************/
void Menu::Search_Information() {
	string children_name;
	int position = 0,num=0;
	vector<int>children_position;//存储找到的小朋友位置 如果小朋友重名 则push_back 方便最后输出所有重名小朋友的信息
	char t;
	cout << "\n\t\t\t\t\t\t请输入要查询的小朋友的姓名:";
	cin >> children_name;
	for (int i = 0; i < children_num; i++) {
		if (children_name == children[i].name) {
			children_position.push_back(i);
			num++;//找到一个要查找的小朋友就将他的位置信息入栈
		}
	}
	if (num == 0) {
		cout << "\n\t\t\t\t\t\t未找到信息！！";
		Sleep(100);
	}
	else
	{
		cout << "\n\t\t\t\t\t\t请选择查询哪类信息?";
		cout << "\n\t\t\t\t\t\t1父母姓名与电话";
		cout << "\n\t\t\t\t\t\t2:住址";
		cout << "\n\t\t\t\t\t\t3:所有信息";
		t = _getch();
		int i = 1;
		switch (t - 48) {
		case 1:
			cout << endl;
			for (vector<int>::iterator it = children_position.begin(); it != children_position.end(); it++) {
				position = *it;
				if (children_position.size() != 1) {
					cout << "\n\n\t\t\t第" << i << "个小朋友的信息:";
					i++;
				}
				cout << "\n\n\t\t\t\t\t父亲姓名:" << children[position].father_name << "\t父亲电话:" << children[position].father_phonenumber;
				cout << "\n\n\t\t\t\t\t母亲姓名:" << children[position].mother_name << "\t母亲电话:" << children[position].mother_phonenumber;
			}
			break;
		case 2:
			cout << endl;
			for (vector<int>::iterator it = children_position.begin(); it != children_position.end(); it++) {
				position = *it;
				if (children_position.size() != 1) {
					cout << "\n\n\t\t\t第" << i << "个小朋友的信息:";
					i++;
				}
				cout << "\n\n\t\t\t\t\t\t家庭住址:" << children[position].address << endl;
			}
			break;
		case 3:
			cout << endl;
			for (vector<int>::iterator it = children_position.begin(); it != children_position.end(); it++) {
				position = *it;
				if (children_position.size() != 1) {
					cout << "\n\n\t\t\t第" << i << "个小朋友的信息:";
					i++;
				}
				cout << "\n" << "\t出生年月" << "\t性别" << "\t住址" << "\t身高" << "\t体重" << "\t父亲" << "\t父亲电话" << "\t母亲" << "\t母亲电话" << "\t备注";
				cout << endl;
				cout << children[position] << endl;
			}
			break;
		}
	}
	
}


/****************显示信息函数*****************/
//按身高 体重 身高体重比排序
void Menu::Show_Information() {
	char t1, t2;
	cout << "\n\t\t\t\t\t\t请选择要排序的信息";
	cout << "\n\t\t\t\t\t\t1:身高";
	cout << "\n\t\t\t\t\t\t2:体重";
	cout << "\n\t\t\t\t\t\t3:身高体重比";
	cout << "\n";
	t1 = _getch();
	cout << "\n\t\t\t\t\t\t请选择排序方式";
	cout << "\n\t\t\t\t\t\t1:正序 由低到高";
	cout << "\n\t\t\t\t\t\t2:逆序 由高到低";
	t2 = _getch();
	int j = 0, k = 0;
	////value存在值 rank存储排序后对应的位次 动态分配内存 如value 5 3 4 2 对应rank 1 3 2 4 方便后面正序倒序输出
	double* value;
	int* rank;
	int f = 1 << sizeof(int) * 8 - 1;//最小的int型正整数
	value = (double*)malloc(sizeof(double) * children_num);
	rank = new int[children_num];
	cout << "\n\n\t\t\t\t\t\t现在一共有" << children_num << "个小朋友" << "  信息如下:";
	cout.setf(ios::left);
	cout<< "\n\n" <<"姓名"<<"\t出生年月" << "\t性别" << "\t住址" << "\t身高" << "\t体重" << "\t父亲" << "\t父亲电话" << "\t母亲" << "\t母亲电话" << "\t备注";
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


/****************统计性别函数*****************/
//优化为否输出男女姓名
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
	cout << "\n\t\t\t\t\t\t共有" << boy_num << "个男孩  ";
	cout << "\n\t\t\t\t\t\t共有" << girl_num << "个女孩  ";
	if (girl_num > boy_num)
		cout << "\n\t\t\t\t\t\t男女比例为 " << "1:" << girl_num / boy_num;
	else
		cout << "\n\t\t\t\t\t\t男女比例为 " << boy_num / girl_num << ":1";
	cout << "\n\n\t\t\t\t\t\t是否要查看男女姓名";
	cout << "\n\t\t\t\t\t\t1:男生姓名";
	cout << "\n\t\t\t\t\t\t2:女生姓名";
	cout << "\n\t\t\t\t\t\t3:不查看";
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