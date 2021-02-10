#pragma once
#include "Draw.h"
#include"AVLTree.h"
using namespace std;
class Init :protected Draw {
    public:
        Init();// 初始化 登录 注册
		~Init();//退出程序
		
	    void Getusermessage(AVLTree *tree);//从文件中读取users的信息
		void Saveusermessage(AVLTree* tree);
		TNode* Login(AVLTree *tree);
		void isLogin(AVLTree* tree,string username,string password);
		TNode* Register(AVLTree* tree);
		//修改登录状态
		void setlogin_success(int n) {
			login_success = n;
		};
	    //获取登录状态
		int getlogin_success() {
			return login_success;
		};
		string input_username;
		char input_password[20] = "";//输入的账号密码 采用char型可以实现退格与*打印
    private:
		int login_success=0;//是否登录成功 0为不成功  1为用户 2为管理员
};