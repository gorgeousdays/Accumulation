#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
class Calculator {
	private:
		int n1,n2;
		double answer;
		string c;
	public:
		void myinput();
		void input1();
		void input2();
		void input3();
		void  change();
		double get_answer(double p);
		void show_answer();
};
Calculator cal;
double Calculator::get_answer(double p) {
	answer=p;
}
void Calculator::change() {
	n1=answer;
}
void Calculator::show_answer() {
	cout<<answer;
}
void Calculator::myinput() {
	cout<<"�������һ����:";
	cin>>n1;
}
void Calculator::input1() {
	cout<<"�������������:";
	cin>>c;
	if(c=="+"||c=="-"||c=="*"||c=="/"||c=="pow")
		cal.input2();
	else if (c=="sin"||c=="cos"||c=="sqrt"||c=="ln"||c=="log10")
		cal.input3();
	else
		cout<<"��֧�ָ�����";
}
void Calculator::input2() {
	cout<<endl<<"������ڶ�����:";
	cin>>n2;
	if(c=="+") get_answer(n1+n2);
	else if(c=="-") get_answer(n1-n2);
	else if(c=="*") get_answer(n1*n2);
	else if(c=="/") get_answer(n1/n2);
	else if(c=="pow") get_answer(pow(n1,n2));
	show_answer();
	cout<<endl;
}
void Calculator::input3() {
	if(c=="sin")
		get_answer(sin(n1));
	else if(c=="cos")
		get_answer(cos(n1));
	else if(c=="sqrt")
		get_answer(sqrt(n1));
	else if(c=="ln")
		get_answer(log(n1));
	else if(c=="log10")
		get_answer(log10(n1));
	show_answer();
	cout<<endl;
}
int main() {
	int flag2=1;
	int a;
	while(flag2) {
		cal.myinput();
		cal.input1();
		int flag1=1;
		while(flag1==1) {
			cout<<"������� ��Ҫ�ø����ٽ��м���������1:";
			cin>>a;
			cout<<endl;
			if(a!=1) flag1=0;
			else {
				cal.change();
				cal.input1();
			}
		}
		cout<<"�˳�������������1 ��������Ĭ�Ͻ������µ�����:";
		cin>>a;
		cout<<endl;
		if(a==1) break;
	}
	cout<<"�������";
}
