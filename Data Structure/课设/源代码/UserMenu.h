#pragma once
#include "Menu.h"
#include "AVLTree.h"
#include<conio.h>
//��ͨ�û�����
class UserMenu :protected Menu {
    public:
        //�������������������������͵�ǰ�û���Ӧ�Ľڵ�
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
				printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
				printf("\t\t\t\t   ��                 �û���¼����ϵͳ        ��\n");
				printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
				printf("\t\t\t\t   ����������������������������������������������������������������������������������������-��\n");
				printf("\t\t\t\t   ��                                            ��\n");
				printf("\t\t\t\t   �� 1. �޸�����                    2. ע���˻� ��\n");
				printf("\t\t\t\t   ��                                            ��\n");
				printf("\t\t\t\t   ��                                            ��\n");
				printf("\t\t\t\t   �� 0. �˳�����                                ��\n");
				printf("\t\t\t\t   ��                                            ��\n");
				printf("\t\t\t\t   ��������������������������������������������������������������������������������������������\n");
				printf("\t\t\t\t\t\t  ����ѡ��(0-7):");
				c = _getch();  //��ȡ�ַ����ɼ�
			} while (c < '0' || c > '6');
			return c - '0';
        }
        void Switch_Menu(AVLTree *tree,TNode *user) {
			string new_password;
            switch (MenuSelect()){
				case 0:
					system("cls");
					Draw3();
					Quit(tree,user);	//�˳��򷵻����˵�
					break;
				case 1:   //�޸�����
					system("cls");
					cout << "\n\n\t\t\t\t����������������:";
					cin >> new_password;
					user->setpassword(new_password);
					cout << "\n\n\t\t\t\t�޸ĳɹ�������";
					Quit(tree, user);
					break;
				case 2:   //ע���˻�
					system("cls");
					cout << "\n\n\t\t\t\t��ȷ��Ҫע���˻���(y/n)��";
					char ch;
					ch = _getch();
					if (ch == 'y'){ 
						tree->deleteUser(user->getusername()); 
						cout << "\n\n\t\t\t\tע���ɹ�������";
						cout << "\n\t\t\t\t\t\t��лʹ��";
						Sleep(500);
					}
					else
					  Quit(tree, user);
            }
        }
};