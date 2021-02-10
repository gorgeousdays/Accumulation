#include<iostream>
using namespace std;
template <typename T>
class node {
	public:
		T value;
		node<T> *next;
		node() : next(NULL) {}
		node(const T& item, node<T> *nextNode = NULL) :  value(item), next(nextNode)  {}
};

template <typename T>
class priority_queue {
	public:
		priority_queue():front(NULL), back(NULL), count(0) {};
		void push(const T& item);
		void popmax();
		void showmax();
        
		//ʵ���п� ����Ԫ�ظ����Լ���ӡ����  
		bool empty() const {
			return count==0;
		}
		int size() const {
			return count;
		}
		void display() {
			node<T>  *temp=front;
			while(temp!=NULL) {
				cout<<temp->value<<' ';
				temp = temp->next;
			}
			cout<<endl;
		}
        T The_max;
	private:
		node<T> *front,*back;
		int count;
};
//Ԫ�ز������ 
template <typename T>
void priority_queue<T>::push(const T& item) {
	node<T> *newNode=new node<T>(item, NULL);
	if(front==NULL) {
		front=newNode;
		back=newNode;
	} else {
		back->next=newNode;
		back=newNode; 
	}
	count++; 
}
//������Ԫ��ֵ����The_max 
template <typename T>
void priority_queue<T>::showmax() {
    node<T>*temp=front;
    T max=front->value;
	if(front==NULL) return;
	while(temp!=NULL){
		if(temp->value>max){
			max=temp->value;
			
		}
		temp = temp->next;
    } 
    The_max=max;
}
//ɾ�����Ԫ�� 
template <typename T>
void priority_queue<T>::popmax(){
	node<T>*temp=front;
	if(front==NULL) return; 
	showmax();
	if(The_max==front->value){
		front=front->next;
	}
	else{
		while(The_max!=temp->next->value){
			temp=temp->next;
		}
	    temp->next=temp->next->next;	
	}
    count--;
} 
int main() {
	priority_queue<int> Q;
	char option;
	Q.push(123);
	Q.push(2);
	Q.push(2345);
	Q.showmax();
	cout<<"The max number is"<<Q.The_max<<endl;
	cout<<"The size is"<<Q.size()<<endl;
	cout<<"The queue is"<<endl; 
	Q.display(); 
	cout<<"after pop"<<endl;
	Q.popmax();
	cout<<"The queue is"<<endl; 
	Q.display(); 
	
}
