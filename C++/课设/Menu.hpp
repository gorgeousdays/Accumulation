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
    Menu();//将children.txt中数据读到内存
    ~Menu();//将操作完成后所有数据放回children.txt
    void Switch_Menu();//菜单栏
    int MenuSelect(); //菜单选择
    void Quit();  //按0退出程序
    void Add_Information(); //按1添加小朋友信息
    void Change_Information();//按2修改小朋友信息  可优化 只更改某一项
    void Delete_Information() ;//按3删除小朋友信息
    void Search_Information();//按4查询小朋友信息  两种查询
    void Show_Information();//按5显示所有小朋友信息 排序
    void Statistics_Information();//按6显示男女比例
private:
    Child* children = new Child[15];
    int children_num;//小朋友总人数
};
#endif