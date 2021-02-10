#include<iostream>
using namespace std;

template <typename T>
class node{
	public:
		T data;      
      	node<T> *next;
      	node(const T& temp, node<T> *nextnode = NULL) : data(temp), next(nextnode){}
      	node():next(NULL){}	
};

int main(){
	int temp, max;
	node<int> *first = NULL, *a[2];
	cout<<"Please enter the data: ";
	cin>>temp;
	first = new node<int>(temp, NULL);
	a[0] = first;
	int i=1;
	//�ֱ���a[0],a[1]�洢��������� 
	while(cin>>temp){
		a[i] = new node<int>(temp, NULL);
		a[1-i]->next = a[i];
		i=1-i; 
	}
	//��maxֵ�뵱ǰֵ�Աȵó��Ƿ����� 
	bool judge = true;
	node<int> *f = first;
	max = first->data;
	while(f!=NULL){
		if(f->data < max){
			judge = 0;
			break; 
		}
		else
			max = f->data;
		f=f->next;
	}  
	cout<<"This List is"<<(judge ? "" : " not")<<" sorted by ascending order."<<endl; 
	return 0;
}
