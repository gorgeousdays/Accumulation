#pragma once
#pragma once
#pragma once
#include<iostream>
using namespace std;
class Child {
     private:
        string name;
        string birth;
        bool sex;//1��ʾ�� 0��ʾŮ
        string address;
        double height;
        double weight;
        string father_name,mother_name;//�໤������
        string father_phonenumber,mother_phonenumber;//�໤�˵绰
        string remark;//��ע
    public:
        void setchild(string name_i, string birth_i, bool sex_i, string address_i, double height_i, double weight_i, string father_name_i, string father_phonenumber_i,string mother_name_i,string mother_phonenumber_i, string remark_i);
        Child& operator =(const Child& children);
        friend ostream& operator<<(ostream& os, const Child& c);
        friend class Menu;
};