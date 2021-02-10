#pragma once
#include <iostream>
using namespace std;
//影子树的节点存储用户信息、行列坐标以及对应的左右子树
class ShadowTreeNode{
    public:
        string username = "";
        int level = 0,column=0;
        ShadowTreeNode *left = NULL,*right=NULL;
};

