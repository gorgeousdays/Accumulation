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

//随机值创建链表与输入值创建链表
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
	cout<<"请输入本组数据总量的值"; 
	cin>>num;
	if (num!=0) {
		cout<<"请输入数据";
		cin>>temp;
		first = new node<int>(temp, NULL); 
		p[0] = first;
		for (int i = 1; i<num; i++) {
			cin>>temp;
			p[i%2] = new node<int>(temp, NULL);
			p[(i-1)%2]->next = p[i%2];
		}
	}
	else cout<<"输入值有误！"; 
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
//插入排序实现从小到大排序
node<int>* sort(node<int> *first){
	node<int> *ser,*head,*tail,*temp;
	//考虑为空或只有一个节点的情况 
	if(first==NULL||first->next==NULL)
	     return first; 
	//先插入第一个节点 
	head=new node<int>(first->nodeValue,NULL);
	first=first->next;
	tail=head;
	
    while(first){
    	//分小于头结点大于尾结点和位于中间考虑 
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

//实现两个有序单链表的合并
node<int>* merge(node<int> *first1, node<int> *first2)  {
	if (first1 == NULL) {
		return first2;
	} else if(first2 == NULL) {
		return first1;
	}

	node<int> *first = NULL,*ser,*ser1 = first1, *ser2 = first2;
    //比较两个链表的第一个节点确定复合链表的第一个节点 
	if (ser1->nodeValue <= ser2->nodeValue) {
		first = ser1;
		ser1 = ser1->next;
	} else {
		first = ser2;
		ser2 = ser2->next;
	}
    //依次插值 
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
    //最后若还有一个链表不为空，则继续插值 
	if (ser2!=NULL) {
		while(ser2->next!=NULL) {
			ser->next = ser2;
			ser2 = ser2->next;
			ser = ser->next;
		}
		ser->next =ser2;//需要考虑还有最后一个数据 
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

	srand(time(NULL));//随机数发生器 
	first[0] = random_create();
	first[1] = create();

	for (int i=0; i<2; i++) {
		cout<<"第"<<i+1<<"组原始数据";
		print(first[i]);
		first[i] = sort(first[i]);
		cout<<"第"<<i+1<<"组排序数据 ";
		print(first[i]);
	}
	
	node<int> *merge_list;
	merge_list = merge(first[0], first[1]);
	cout<<"合并后链表";
	print(merge_list);
	return 0;
}


