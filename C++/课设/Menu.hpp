#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#pragma once
#include<iostream>
#include "Draw.hpp"
#include "Child.hpp"
using namespace std;
class Menu :protected Draw{
public:
    Menu();//��children.txt�����ݶ����ڴ�
    ~Menu();//��������ɺ��������ݷŻ�children.txt
    void Switch_Menu();//�˵���
    int MenuSelect(); //�˵�ѡ��
    void Quit();  //��0�˳�����
    void Add_Information(); //��1���С������Ϣ
    void Change_Information();//��2�޸�С������Ϣ  ���Ż� ֻ����ĳһ��
    void Delete_Information() ;//��3ɾ��С������Ϣ
    void Search_Information();//��4��ѯС������Ϣ  ���ֲ�ѯ
    void Show_Information();//��5��ʾ����С������Ϣ ����
    void Statistics_Information();//��6��ʾ��Ů����
private:
    Child* children = new Child[15];
    int children_num;//С����������
};
#endif