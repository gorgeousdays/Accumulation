#pragma once
#include<iostream>
#include<cstring>
using namespace std;
//����ͳ����Ů��Ϣ


class node {
    public:
		virtual void print() = 0;//���ô��麯��
};



//������洢��Ů���� ��ͳ����Ů�Ա����Խ��������������
class boyname_node:protected node{
    private:
	     string boyname;
	     boyname_node* next;
		 boyname_node* boy__head;//ͷ�ڵ� �������
		 friend class Menu;
    public:
		//ͷ�ڵ�Ľ���
		void set_boy_head(boyname_node* boy_head){
			boy__head = boy_head;
		}
		//�������
		void print();
};



class girlname_node :protected node {
private:
	string girlname;
	girlname_node* next;
	girlname_node* girl__head;//ͷ�ڵ� �������
	friend class Menu;
public:
	//ͷ�ڵ�Ľ���
	void set_girl_head(girlname_node* girl_head) {
		girl__head = girl_head;
	}
	//�������
	void print();
};