#include<stdlib.h>
#include<iostream>
#include<time.h>
#define LIST_SIZE 10
using namespace std;

template <typename T>
class node {
	public:
		T nodeValue;
		node<T> *next;
		node() : next(NULL) {}
		node(const T& item, node<T> *nextNode = NULL) :  nodeValue(item), next(nextNode)  {}
};

//���ֵ��������������ֵ��������
node<int>* random_create() {
	node<int> *first = NULL;
	for (int i = 0; i<LIST_SIZE; i++) {
		first=new node<int>(rand(),first);
	}
	return first; 
}

node<int>* create() {
	int num, temp;
	node<int> *first = NULL, *p[2];
	cout<<"�����뱾������������ֵ"; 
	cin>>num;
	if (num!=0) {
		cout<<"����������";
		cin>>temp;
		first = new node<int>(temp, NULL); 
		p[0] = first;
		for (int i = 1; i<num; i++) {
			cin>>temp;
			p[i%2] = new node<int>(temp, NULL);
			p[(i-1)%2]->next = p[i%2];
		}
	}
	else cout<<"����ֵ����"; 
	return first;
}

void print(node<int> *first){
	node<int> *ser;
	ser = first;
	while(ser!=NULL){
		cout<<ser->nodeValue<<' ';
		ser=ser->next;
	}
	cout<<endl;
}
//��������ʵ�ִ�С��������
node<int>* sort(node<int> *first){
	node<int> *ser,*head,*tail,*temp;
	//����Ϊ�ջ�ֻ��һ���ڵ����� 
	if(first==NULL||first->next==NULL)
	     return first; 
	//�Ȳ����һ���ڵ� 
	head=new node<int>(first->nodeValue,NULL);
	first=first->next;
	tail=head;
	
    while(first){
    	//��С��ͷ������β����λ���м俼�� 
    	if(first->nodeValue<=head->nodeValue){
    		head=new node<int>(first->nodeValue,head);
		}
		else if(first->nodeValue>=tail->nodeValue){
			temp=new node<int>(first->nodeValue,NULL);
			tail->next=temp;
			tail=tail->next; 
		}
		else{    	
		    ser=head;
			while(ser->next!=NULL){
			    if(ser->nodeValue<first->nodeValue&&ser->next->nodeValue>first->nodeValue){
			        temp= new node<int>(first->nodeValue,ser->next);
				    ser->next=temp;
					break;
				}
				ser=ser->next;
				
			}
		}
    	first=first->next;
	}
	return head;	
}

//ʵ��������������ĺϲ�
node<int>* merge(node<int> *first1, node<int> *first2)  {
	if (first1 == NULL) {
		return first2;
	} else if(first2 == NULL) {
		return first1;
	}

	node<int> *first = NULL,*ser,*ser1 = first1, *ser2 = first2;
    //�Ƚ���������ĵ�һ���ڵ�ȷ����������ĵ�һ���ڵ� 
	if (ser1->nodeValue <= ser2->nodeValue) {
		first = ser1;
		ser1 = ser1->next;
	} else {
		first = ser2;
		ser2 = ser2->next;
	}
    //���β�ֵ 
	ser = first;
	while(ser1 && ser2) {
		if (ser1->nodeValue < ser2->nodeValue) {
			ser->next = ser1;
			ser1 = ser1->next;
		} else {
			ser->next = ser2;
			ser2 = ser2->next;
		}
		ser = ser->next;
	}
    //���������һ������Ϊ�գ��������ֵ 
	if (ser2!=NULL) {
		while(ser2->next!=NULL) {
			ser->next = ser2;
			ser2 = ser2->next;
			ser = ser->next;
		}
		ser->next =ser2;//��Ҫ���ǻ������һ������ 
	}
	if (ser1!=NULL) {
		while(ser1->next!=NULL) {
			ser->next = ser1;
			ser1 = ser1->next;
			ser = ser->next;
		}
		ser->next =ser1;
	}
	return first;
}

int main() {
	node<int> *first[2];
	first[0] = first[1] = NULL;

	srand(time(NULL));//����������� 
	first[0] = random_create();
	first[1] = create();

	for (int i=0; i<2; i++) {
		cout<<"��"<<i+1<<"��ԭʼ����";
		print(first[i]);
		first[i] = sort(first[i]);
		cout<<"��"<<i+1<<"���������� ";
		print(first[i]);
	}
	
	node<int> *merge_list;
	merge_list = merge(first[0], first[1]);
	cout<<"�ϲ�������";
	print(merge_list);
	return 0;
}


