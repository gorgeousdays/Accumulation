#pragma once
#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;
class Draw {
protected:
	/****************画图*****************/
	//画图标
	void Draw1() {
		printf("\n\t\t\t\t\t╭ ⺌ ╮                        ╭ ```╮\n");
		printf("\t\t\t\t\t(@^o^@) 幼儿园班级信息管理系统(⌒:⌒)\n");
		printf("\t\t\t\t\t(~):(~)                       (~)v(~) \n\n\n\n");
	}
	//画线
	void Draw2() {
		char star[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
		for (int i = 0; i< strlen(star); i++) {
			printf("%c", star[i]);
			Sleep(10);
		}
	}
	//画图加画线
	void Draw3() {
		Draw1();
		Draw2();
	}
};