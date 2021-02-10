#pragma once
#include <iostream>
#include<cstring>
using namespace std;
//树的节点存储用户信息密码以及该节点对应高度信息 函数实现获取以及修改参数值的功能
class TNode {
    public:
        TNode* left = NULL,*right=NULL;
        TNode() {
            username = "";
            password = "";
            height = 0;
        }
        TNode(string new_username, string new_password){
            username = new_username;
            password = new_password;
            height = 0;
        }
        //获取节点的用户信息以及高度
        string getusername(){
            return username;
        }

        string getpassword(){
            return password;
        }

        int getheight(){
            if (this != NULL)return height;
            else return -1;
        }
        //修改节点的用户信息以及高度
        void setusername(string new_username){
            username = new_username;
        }

        void setpassword(string new_password){
            password=new_password;
        }

        void setheight(int new_height) {
            height = new_height;
        }
    private:
        string username;
        string password;
        int height;//节点高度
};
