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
	int temp, max;
	node<int> *first = NULL, *a[2];
	cout<<"Please enter the data: ";
	cin>>temp;
	first = new node<int>(temp, NULL);
	a[0] = first;
	int i=1;
	//分别用a[0],a[1]存储输入的数据
	while(cin>>temp) {
		a[i] = new node<int>(temp, NULL);
		a[1-i]->next = a[i];
		i=1-i;
	}

	node<int> *f,*b,*c;
	f=first;
	if (f == NULL)
		cout<<"error!nothing to output"<<endl;
	else {
		b = f->next;
		f->next = NULL;
		while(b) {
			c = b->next;
			b->next = f;
			f = b;
			b = c;
		}
		first = f;
		cout<<"list data:" ;
		while(f != NULL) {
			cout<<f->data<<' ';
			f=f->next;
		}
	}
}
