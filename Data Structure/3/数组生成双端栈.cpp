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
		cout<<"ջ���!\n";
		return true;
	}
	return false;
}
//����temp���� 1Ϊͷ��ջ����
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
			cout<<"ɾ���ɹ�!\n";
		} else
			cout<<"��Ԫ�ؿ�ɾ��\n";
	} else {
		if (backTop<MAX_SIZE) {
			backTop++;
			cout<<"ɾ���ɹ�!\n";
		} else
			cout<<"��Ԫ�ؿ�ɾ!\n";
	}
}

void DoubleStack::display() {
	cout<<"ͷ��ջΪ";
	int i=0;
	while (i <= frontTop) {
		cout<<StackArray[i]<<" ";
		i++;
	}
	cout<<endl;

	cout<<"β��ջΪ";
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
	cout<<"����:0.�˳����� 1.ͷ��ջ���� 2.β��ջ���� 3.ͷ��ջɾ�� 4.β��ջɾ�� 5.��ӡջ\n";
	while(1) {
		cout<<"����";
		cin>>c;
		switch(c) {
			case 1:
				cout<<"������Ҫ�����Ԫ��";
				cin>>temp;
				s.push(temp,1);
				break;
			case 2:
				cout<<"������Ҫ�����Ԫ��";
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
				cout<<"����������������룡"<<endl;
		}
	}
}

int main() {
	DoubleStack S;
	choose(S);
	return 0;
}

