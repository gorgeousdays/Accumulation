#pragma once
#include<iostream>
#include"Child.hpp"
using namespace std;
void Child::setchild(string name_i, string birth_i, bool sex_i, string address_i, double height_i, double weight_i,string father_name_i, string father_phonenumber_i, string mother_name_i, string mother_phonenumber_i, string remark_i) {
	name = name_i;
	birth = birth_i;
	sex = sex_i;
	address = address_i;
	height = height_i;
	weight = weight_i;
	father_name = father_name_i;
	father_phonenumber =father_phonenumber_i;
	mother_name = mother_name_i;
	mother_phonenumber = mother_phonenumber_i;
	remark = remark_i;
}


//���صȺ� ʵ��С������Ϣ֮��ĸ�ֵ
Child& Child::operator =(const Child& children) {
	name = children.name;
	birth = children.birth;
	sex = children.sex;
	address = children.address;
	height = children.height;
	weight = children.weight;
	father_name = children.father_name;
	father_phonenumber = children.father_phonenumber;
	mother_name = children.mother_name;
	mother_phonenumber = children.mother_phonenumber;
	remark = children.remark;
	return *this;
}


//������� ʵ�����С������Ϣ����
ostream& operator<<(ostream& os, const Child& c)
{
	/*os << "\n\t\t\t\t\t\t��������:" <<c.birth;
	os << "\n\t\t\t\t\t\t�Ա�:";
	if (c.sex == 1)os << "��";
	else os << "Ů";
	os << "\n\t\t\t\t\t\t��ͥסַ:" << c.address;
	os << "\n\t\t\t\t\t\t���:" << c.height;
	os << "\n\t\t\t\t\t\t����:" << c.weight;
	os << "\n\t\t\t\t\t\t��������:" << c.father_name;
	os << "\n\t\t\t\t\t\t���׵绰:" << c.father_phonenumber;
	os << "\n\t\t\t\t\t\tĸ������:" << c.mother_name;
	os << "\n\t\t\t\t\t\tĸ�׵绰:" << c.mother_phonenumber;
	os << "\n\t\t\t\t\t\t��ע��Ϣ:" << c.remark;*/
	os.setf(ios::left);
	os <<"\t"<<c.birth;
	os << "\t";
	if (c.sex == 1)os << "��";
	else os << "Ů";
	os.setf(ios::left);
	os << "\t" << c.address;
	os.setf(ios::left);
	os << "\t" << c.height;
	os.setf(ios::left);
	os << "\t" << c.weight;
	os.setf(ios::left);
	os << "\t" << c.father_name;
	os.setf(ios::left);
	os.width(5);
	os << "\t" << c.father_phonenumber;
	os.setf(ios::left);
	os << "\t" << c.mother_name;
	os.setf(ios::left);
	os.width(5);
	os << "\t  " << c.mother_phonenumber;
	os.setf(ios::left);
	os << "\t" << c.remark;
	return os;
}