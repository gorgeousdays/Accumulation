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
				printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
				printf("\t\t\t\t   ��             �û���¼����ϵͳ(����Ա)        ��\n");
				printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
				printf("\t\t\t\t   ����������������������������������������������������������������������������������������-��\n");
				printf("\t\t\t\t   ��                                            ��\n");
				printf("\t\t\t\t   �� 1. �޸�����                    2. ɾ���û� ��\n");
				printf("\t\t\t\t   ��                                            ��\n");
				printf("\t\t\t\t   �� 3. ����û�                    4. ��ӡAVL����\n");
				printf("\t\t\t\t   ��                                            ��\n");
				printf("\t\t\t\t   �� 0. �˳�����                                ��\n");
				printf("\t\t\t\t   ��                                            ��\n");
				printf("\t\t\t\t   ��������������������������������������������������������������������������������������������\n");
				printf("\t\t\t\t\t\t  ����ѡ��(0-7):");
				c = _getch();  //��ȡ�ַ����ɼ�
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
				Quit(tree, user);	//�˳��򷵻����˵�
				break;
			case 1:   //�޸�����
				system("cls");
				cout << "\n\n\t\t\t\t����������������:";
				cin >> new_password;
				user->setpassword(new_password);
				cout << "\n\n\t\t\t\t�޸ĳɹ�������";
				Quit(tree, user);
				break;
			case 2:   //ɾ��ָ���û�
				system("cls");
				cout << "\n\t\t\t\t\t\t������Ҫɾ�����˺��û�����";
				cin >> new_username;
				if (tree->SearchTNode(tree->root, new_username) != NULL) {
					tree->deleteUser((tree->SearchTNode(tree->root,new_username))->getusername());
					cout << "\n\t\t\t\t\t\tɾ���ɹ�������";
				}
				else cout << "\n\t\t\t\t\t\t�����ڸ��û���";
				Quit(tree, user);
				break;
			case 3:    //����û�
				system("cls");
				cout << "\n\n\t\t\t\t����������˻����û�����";
				cin >> new_username;
				cout << "\n\n\t\t\t\t����������˻������룺";
				cin >> new_password;
				tree->addUser(new_username, new_password);
				cout << "\n\n\t\t\t\t��ӳɹ�������";
				Quit(tree, user);
				break;
			case 4:    //�����ӡ������
				system("cls");
				cout << endl;
				cout << "\n\t\t\t\t\t\t�����ӡ�������������:\n";
				tree->display();
				Quit(tree, user);
				break;
			}
		}
};