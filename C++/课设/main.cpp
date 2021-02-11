#include <iostream>
#include "Menu.hpp" 
#include "Init.hpp"
using namespace std;
int main() {
	Init init;//登录或注册
	if (init.getlogin_success()) {  //登录成功则进入菜单
		Menu menu;
	}
}