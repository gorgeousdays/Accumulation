#include<iostream>
using namespace std;
const int MAX_SIZE=100;

class DoubleStack {
	public:
		DoubleStack()  {
			frontTop=-1;
			backTop=MAX_SIZE;
		}
		bool full();
		void push(int item,int temp);
		void pop(int temp);
		void display();
	private:
		int StackArray[MAX_SIZE];
		int frontTop;
		int backTop;
};

bool DoubleStack::full() {
	if (frontTop >= backTop-1) {
		cout<<"栈溢出!\n";
		return true;
	}
	return false;
}
//传入temp参数 1为头部栈插入
void DoubleStack::push(int item,int temp) {
	if(temp==1) {
		if (!full()) {
			frontTop++;
			StackArray[frontTop] = item;
		}
	} else {
		if (!full()) {
			backTop--;
			StackArray[backTop] = item;
		}
	}
}

void DoubleStack::pop(int temp) {
	if(temp==1) {
		if (frontTop>-1) {
			frontTop--;
			cout<<"删除成功!\n";
		} else
			cout<<"无元素可删！\n";
	} else {
		if (backTop<MAX_SIZE) {
			backTop++;
			cout<<"删除成功!\n";
		} else
			cout<<"无元素可删!\n";
	}
}

void DoubleStack::display() {
	cout<<"头部栈为";
	int i=0;
	while (i <= frontTop) {
		cout<<StackArray[i]<<" ";
		i++;
	}
	cout<<endl;

	cout<<"尾部栈为";
	i = MAX_SIZE-1;
	while (i >= backTop) {
		cout<<StackArray[i]<<" ";
		i--;
	}
	cout<<endl;
}

int choose(DoubleStack s) {
	int temp;
	int c;
	cout<<"输入:0.退出程序 1.头部栈插入 2.尾部栈插入 3.头部栈删除 4.尾部栈删除 5.打印栈\n";
	while(1) {
		cout<<"输入";
		cin>>c;
		switch(c) {
			case 1:
				cout<<"请输入要插入的元素";
				cin>>temp;
				s.push(temp,1);
				break;
			case 2:
				cout<<"请输入要插入的元素";
				cin>>temp;
				s.push(temp,2);
				break;
			case 3:
				s.pop(1);
				break;
			case 4:
				s.pop(2);
				break;
			case 5:
				s.display();
				break;
			case 0 :
				return 0;
			default:
				cout<<"输入错误，请重新输入！"<<endl;
		}
	}
}

int main() {
	DoubleStack S;
	choose(S);
	return 0;
}

