#pragma once
#include <iostream>
using namespace std;
//Ӱ�����Ľڵ�洢�û���Ϣ�����������Լ���Ӧ����������
class ShadowTreeNode{
    public:
        string username = "";
        int level = 0,column=0;
        ShadowTreeNode *left = NULL,*right=NULL;
};

