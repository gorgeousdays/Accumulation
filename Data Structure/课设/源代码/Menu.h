#pragma once
#include "Draw.h"
#include"AVLTree.h"
#include<conio.h>
//������ �������ڽ����ָ���
class Menu:protected Draw {
    public:
        virtual int MenuSelect(void)=0;//���ڴ�ӡ���˵��Լ�����ѡ��

        virtual void Switch_Menu(AVLTree* tree, TNode* user) = 0;//���ڸ���ѡ��������Ӧָ��

		//ʵ�ֻ��˵����˵������˳�����
		void Quit(AVLTree* tree, TNode* user) {
			char ch;
			printf("\n\n\t\t\t\tҪ���ص�¼���水�����\t\t�˳������밴Esc��\n");
			ch = _getch();
			if (ch == 0x1b)	//esc������
			{
				cout << "\n\t\t\t\t\t\t��лʹ��";
				Sleep(500);
			}
			//���½������˵�
			else {
				Switch_Menu(tree, user);
			}
		}
};