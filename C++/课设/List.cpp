#include "List.hpp"
#include<iostream>
using namespace std;

void  boyname_node::print() {
	boyname_node* boy_node = boy__head;
	while (boy_node != NULL) {
		cout << "\n\n\t\t\t\t\t\t" << boy_node->boyname;
		boy__head = boy_node;
		boy_node = boy_node->next;
		free(boy__head);
	}
}

void  girlname_node::print() {
	girlname_node* girl_node = girl__head;
	while (girl_node != NULL) {
		cout << "\n\n\t\t\t\t\t\t" << girl_node->girlname;
		girl__head = girl_node;
		girl_node = girl_node->next;
		free(girl__head);
	}
}