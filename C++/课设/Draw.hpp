#pragma once
#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;
class Draw {
protected:
	/****************��ͼ*****************/
	//��ͼ��
	void Draw1() {
		printf("\n\t\t\t\t\t�q �] �r                        �q ```�r\n");
		printf("\t\t\t\t\t(@^o^@) �׶�԰�༶��Ϣ����ϵͳ(��:��)\n");
		printf("\t\t\t\t\t(~):(~)                       (~)v(~) \n\n\n\n");
	}
	//����
	void Draw2() {
		char star[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
		for (int i = 0; i< strlen(star); i++) {
			printf("%c", star[i]);
			Sleep(10);
		}
	}
	//��ͼ�ӻ���
	void Draw3() {
		Draw1();
		Draw2();
	}
};