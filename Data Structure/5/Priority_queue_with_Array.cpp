#include<iostream>
using namespace std;
#define MAXSIZE 5

template <typename T>
class priority_queue {
	public:
		priority_queue():front(0), back(0), count(0) {};
		void push(const T& item);
		void popmax();
		void popmin();
		void showmax();
		void showmin();
        
        //实现判满、判空 返回元素个数以及打印操作 
		bool empty() const {return count==0;}
		bool full() const {return count == MAXSIZE;}
		int size() const {return count;}
		void display() {
			for (int i=front; i<(back+(front>=back? MAXSIZE:0)); i++) {
				cout<<Element[i%MAXSIZE]<<' ';
			}
			cout<<endl;
		}
	private:
		T Element[MAXSIZE];
		int front, back;//记录首尾位置 便于数据存入循环队列 
		int count;
};
 
template <typename T>
void priority_queue<T>::push(const T& item) {
	Element[back] = item;
	back = (back+1) % MAXSIZE;
	count++;
}
//pop掉最大或最小元素 
template <typename T>
void priority_queue<T>::popmax() {
	if (empty()) {
		cout<<"Error!No element to pop!"<<endl;
		return;
	}
	T max = Element[front];
	int maxindex = front, k = count;

	//找到最大值及其索引 
	while(k--) {
		int i = front+(count-k)-1;
		if (max<Element[i%MAXSIZE]) {
			max = Element[i%MAXSIZE];
			maxindex = i % MAXSIZE;
		}
	}
    //位置后移 
	for (int i=maxindex+(front>maxindex? MAXSIZE:0); i>front; i--) {
		Element[i%MAXSIZE] = Element[(i-1)%MAXSIZE];
	}
	front = (front+1) % MAXSIZE;
	count--;
	cout<<"Pop successfully"<<endl;
}

template <typename T>
void priority_queue<T>::popmin() {

	if (empty()) {
		cout<<"Error!No element to pop!"<<endl;
		return;
	}
	T min = Element[front];
	int minindex = front, k = count;
	while(k--) {
		int i = front+(count-k)-1;
		if (min>Element[i%MAXSIZE]) {
			min = Element[i];
			minindex = i % MAXSIZE;
		}
	}

	for (int i=minindex+(front>minindex? MAXSIZE:0); i>front; i--) {
		Element[i%MAXSIZE] = Element[(i-1)%MAXSIZE];
	}

	front = (front+1) % MAXSIZE;
	count--;
	cout<<"Pop successfully!"<<endl;
}
//print出最大和最小元素 
template <typename T>
void priority_queue<T>::showmax() {
	T max = Element[front];
	int k = count-1;
	while(k--) {
		int i = front+(count-k)-1;
		if (max < Element[i%MAXSIZE]) {
			max = Element[i];
		}
	}
	cout<<max<<endl;
}
template <typename T>
void priority_queue<T>::showmin() {
	T min = Element[front];
	int k  = count-1;
	while(k --) {
		int i = front+(count-k)-1;
		if (min > Element[i%MAXSIZE]) {
			min = Element[i];
		}
	}
	cout<<min<<endl;
}
//choose1和choose2对应不同优先级下的输出 
void choose1() {
	priority_queue<int> Q;
	char option;
	int temp;
	cout<<"Please enter your option! 1.push 2.show 3.pop 4.display 5.size E.exit\n";
	while(cin>>option&&option!='e'&&option!='E') {
		switch(option) {
			case '1':
				if (!Q.full()) {
					cout<<"Please enter the eletement:";
					cin>>temp;
					Q.push(temp);
				} else
					cout<<"Error!Full!"<<endl;
				break;
			case '2':
				Q.showmax();
				break;
			case '3':
				Q.popmax();
				break;
			case '4':
				Q.display();
				break;
			case '5':
				cout<<"The size is:"<<Q.size()<<endl;
				break;
			default:
				cout<<"Error input! Please try again."<<endl;
		}
	}
}
void choose2() {	
	priority_queue<int> Q;
	char option;
	int temp;
	cout<<"Please enter your option! 1.push 2.show 3.pop 4.display 5.size E.exit\n";
	while(cin>>option&&option!='e'&&option!='E') {
		switch(option) {
			case '1':
				if (!Q.full()) {
					cout<<"Please enter the eletement:";
					cin>>temp;
					Q.push(temp);
				} else
					cout<<"Error!Full!"<<endl;
				break;
			case '2':
				Q.showmin();
				break;
			case '3':
				Q.popmin();
				break;
			case '4':
				Q.display();
				break;
			case '5':
				cout<<"The size is:"<<Q.size()<<endl;
				break;
			default:
				cout<<"Error input! Please try again."<<endl;
		}
	}
}
//关于choose部分 感觉可以用函数指针优化 根据输入选择对应的pop和show函数 不过还没实现 
int main () {
	int choose;
	cout<<"Please set your priorities\n1.Big priority   2.Small priority\n";
	cin>>choose;
	char option;
	int temp;
	if(choose==1) {
		choose1();
	} else if(choose==2) {
        choose2();
	} else {
		cout<<"Error!";
		return 0;
	}
	return 0;
}

