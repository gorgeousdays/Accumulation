#include<iostream>
using namespace std;

template <typename T>
class node {
	public:
		T data;
		node<T> *next;
		node(const T& temp, node<T> *nextnode = NULL) : data(temp), next(nextnode) {}
		node():next(NULL) {}
};


int main() {
	int num, temp,place;
	node<int> *first = NULL, *a[2];
	cout<<"Please enter the data: ";
	cin>>temp;
	first = new node<int>(temp, NULL);
	a[0] = first;
	int i=1;
	num=1;
	//�ֱ���a[0],a[1]�洢���������
	while(cin>>temp) {
		a[i] = new node<int>(temp, NULL);
		a[1-i]->next = a[i];
		i=1-i;
		num++;
	}
	//ctrl+zֹͣ����� ���뻺�����ͻ�ֱ�ӹر�
	cin.clear();// ����cin��״̬��ʾ����
	cin.sync();//���������������� 
	cout<<"Please enter the place of node you want to insert: ";
	cin>>place;
	if(place > num)
		cout<<"error��The place is bigger than size of your list"<<endl;
	else {
		node<int> *insert,t;
		cout<<"Please enter the data: ";
		cin>>temp;
		node<int>* f=first;
		if(place == num) {
			while(f->next!=NULL)
				f=f->next;
			insert = new node<int>(temp, NULL);
			f->next = insert;
		} else {
			for(int i=1; i<=place-1; i++) {
				f=f->next;
			}
			insert = new node<int>(temp, f->next);
			f->next=insert;
		}
		cout<<"data list: ";
		f = first;
		while(f!=NULL) {
			cout<<f->data<<' ';
			f=f->next;
		}
		cout<<endl;
	}
}
