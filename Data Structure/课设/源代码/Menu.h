#pragma once
#include "Draw.h"
#include"AVLTree.h"
#include<conio.h>
//界面类 包含关于界面的指令函数
class Menu:protected Draw {
    public:
        virtual int MenuSelect(void)=0;//用于打印主菜单以及做出选择

        virtual void Switch_Menu(AVLTree* tree, TNode* user) = 0;//用于根据选择做出对应指令

		//实现回退到主菜单或者退出程序
		void Quit(AVLTree* tree, TNode* user) {
			char ch;
			printf("\n\n\t\t\t\t要返回登录界面按任意键\t\t退出程序请按Esc键\n");
			ch = _getch();
			if (ch == 0x1b)	//esc键按下
			{
				cout << "\n\t\t\t\t\t\t感谢使用";
				Sleep(500);
			}
			//重新进入主菜单
			else {
				Switch_Menu(tree, user);
			}
		}
};