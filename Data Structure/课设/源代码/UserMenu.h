#pragma once
#include "Menu.h"
#include "AVLTree.h"
#include<conio.h>
//普通用户界面
class UserMenu :protected Menu {
    public:
        //传入两个参数，包括整棵树和当前用户对应的节点
        UserMenu(AVLTree* tree, TNode* user) {
            system("CLS");
            
			Switch_Menu(tree,user);
        }
        int MenuSelect(void) {
			char c;
			do
			{
				system("cls");
				Draw3();
				printf("\n");
				printf("\t\t\t\t   ╭═════════════════════════════════○●○●═══╮\n");
				printf("\t\t\t\t   │                 用户登录管理系统        │\n");
				printf("\t\t\t\t   ╰═══○●○●═════════════════════════════════╯\n");
				printf("\t\t\t\t   ┌───────────────────────────────────────────-┐\n");
				printf("\t\t\t\t   │                                            │\n");
				printf("\t\t\t\t   │ 1. 修改密码                    2. 注销账户 │\n");
				printf("\t\t\t\t   │                                            │\n");
				printf("\t\t\t\t   │                                            │\n");
				printf("\t\t\t\t   │ 0. 退出程序                                │\n");
				printf("\t\t\t\t   │                                            │\n");
				printf("\t\t\t\t   └────────────────────────────────────────────┘\n");
				printf("\t\t\t\t\t\t  请您选择(0-7):");
				c = _getch();  //获取字符不可见
			} while (c < '0' || c > '6');
			return c - '0';
        }
        void Switch_Menu(AVLTree *tree,TNode *user) {
			string new_password;
            switch (MenuSelect()){
				case 0:
					system("cls");
					Draw3();
					Quit(tree,user);	//退出或返回主菜单
					break;
				case 1:   //修改密码
					system("cls");
					cout << "\n\n\t\t\t\t请输入您的新密码:";
					cin >> new_password;
					user->setpassword(new_password);
					cout << "\n\n\t\t\t\t修改成功！！！";
					Quit(tree, user);
					break;
				case 2:   //注销账户
					system("cls");
					cout << "\n\n\t\t\t\t你确定要注销账户吗(y/n)？";
					char ch;
					ch = _getch();
					if (ch == 'y'){ 
						tree->deleteUser(user->getusername()); 
						cout << "\n\n\t\t\t\t注销成功！！！";
						cout << "\n\t\t\t\t\t\t感谢使用";
						Sleep(500);
					}
					else
					  Quit(tree, user);
            }
        }
};