#pragma once
#include<iostream>
#include<cstring>
using namespace std;
//用于统计男女信息


class node {
    public:
		virtual void print() = 0;//运用纯虚函数
};



//用链表存储男女姓名 在统计男女性别后可以进行输出姓名操作
class boyname_node:protected node{
    private:
	     string boyname;
	     boyname_node* next;
		 boyname_node* boy__head;//头节点 用于输出
		 friend class Menu;
    public:
		//头节点的建立
		void set_boy_head(boyname_node* boy_head){
			boy__head = boy_head;
		}
		//输出函数
		void print();
};



class girlname_node :protected node {
private:
	string girlname;
	girlname_node* next;
	girlname_node* girl__head;//头节点 用于输出
	friend class Menu;
public:
	//头节点的建立
	void set_girl_head(girlname_node* girl_head) {
		girl__head = girl_head;
	}
	//输出函数
	void print();
};