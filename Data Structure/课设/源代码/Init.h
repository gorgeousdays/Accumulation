#pragma once
#include "Draw.h"
#include"AVLTree.h"
using namespace std;
class Init :protected Draw {
    public:
        Init();// ��ʼ�� ��¼ ע��
		~Init();//�˳�����
		
	    void Getusermessage(AVLTree *tree);//���ļ��ж�ȡusers����Ϣ
		void Saveusermessage(AVLTree* tree);
		TNode* Login(AVLTree *tree);
		void isLogin(AVLTree* tree,string username,string password);
		TNode* Register(AVLTree* tree);
		//�޸ĵ�¼״̬
		void setlogin_success(int n) {
			login_success = n;
		};
	    //��ȡ��¼״̬
		int getlogin_success() {
			return login_success;
		};
		string input_username;
		char input_password[20] = "";//������˺����� ����char�Ϳ���ʵ���˸���*��ӡ
    private:
		int login_success=0;//�Ƿ��¼�ɹ� 0Ϊ���ɹ�  1Ϊ�û� 2Ϊ����Ա
};