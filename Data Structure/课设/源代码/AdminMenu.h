#pragma once
#include"Menu.h"
class AdminMenu:Menu{
    public:
        AdminMenu(AVLTree* tree, TNode* user) {
            system("CLS");
            Switch_Menu(tree, user);
        }
        int MenuSelect() {
			char c;
			do
			{
				system("cls");
				Draw3();
				printf("\n");
				printf("\t\t\t\t   ╭═════════════════════════════════○●○●═══╮\n");
				printf("\t\t\t\t   │             用户登录管理系统(管理员)        │\n");
				printf("\t\t\t\t   ╰═══○●○●═════════════════════════════════╯\n");
				printf("\t\t\t\t   ┌───────────────────────────────────────────-┐\n");
				printf("\t\t\t\t   │                                            │\n");
				printf("\t\t\t\t   │ 1. 修改密码                    2. 删除用户 │\n");
				printf("\t\t\t\t   │                                            │\n");
				printf("\t\t\t\t   │ 3. 添加用户                    4. 打印AVL树│\n");
				printf("\t\t\t\t   │                                            │\n");
				printf("\t\t\t\t   │ 0. 退出程序                                │\n");
				printf("\t\t\t\t   │                                            │\n");
				printf("\t\t\t\t   └────────────────────────────────────────────┘\n");
				printf("\t\t\t\t\t\t  请您选择(0-7):");
				c = _getch();  //获取字符不可见
			} while (c < '0' || c > '6');
			return c - '0';
        }
		void Switch_Menu(AVLTree* tree, TNode* user) {
			string new_username;
			string new_password;
			switch (MenuSelect()) {
			case 0:
				system("cls");
				Draw3();
				Quit(tree, user);	//退出或返回主菜单
				break;
			case 1:   //修改密码
				system("cls");
				cout << "\n\n\t\t\t\t请输入您的新密码:";
				cin >> new_password;
				user->setpassword(new_password);
				cout << "\n\n\t\t\t\t修改成功！！！";
				Quit(tree, user);
				break;
			case 2:   //删除指定用户
				system("cls");
				cout << "\n\t\t\t\t\t\t请输入要删除的账号用户名：";
				cin >> new_username;
				if (tree->SearchTNode(tree->root, new_username) != NULL) {
					tree->deleteUser((tree->SearchTNode(tree->root,new_username))->getusername());
					cout << "\n\t\t\t\t\t\t删除成功！！！";
				}
				else cout << "\n\t\t\t\t\t\t不存在该用户！";
				Quit(tree, user);
				break;
			case 3:    //添加用户
				system("cls");
				cout << "\n\n\t\t\t\t请输入添加账户的用户名：";
				cin >> new_username;
				cout << "\n\n\t\t\t\t请输入添加账户的密码：";
				cin >> new_password;
				tree->addUser(new_username, new_password);
				cout << "\n\n\t\t\t\t添加成功！！！";
				Quit(tree, user);
				break;
			case 4:    //正向打印二叉树
				system("cls");
				cout << endl;
				cout << "\n\t\t\t\t\t\t正向打印二叉树结果如下:\n";
				tree->display();
				Quit(tree, user);
				break;
			}
		}
};