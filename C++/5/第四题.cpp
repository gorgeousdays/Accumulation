#include <iostream>
#include <cstring>
using namespace std;
class Teacher {
	public:
		Teacher(int a,string b,char c) {
			num=a;
			name=b;
			sex=c;
		}
		void display();
	private:
		int num;
		string name;
		char sex;
};
void Teacher::display() {
	cout<<"num:"<<num<<endl;
	cout<<"name:"<<name<<endl;
	cout<<"sex:"<<sex<<endl;
}
class BirthDate {
	public:
		BirthDate(int y,int m,int d) {
			year=y;
			month=m;
			day=d;
		}
		void display();
		void change(int y,int m,int d);
	private:
		int year;
		int month;
		int day;
};
void BirthDate::display() {
	cout<<"birthday:"<<month<<"/"<<day<<"/"<<year<<endl;
}
void BirthDate::change(int y,int m,int d) {
	year=y;
	month=m;
	day=d;
}
class Professor:public Teacher {
	public:
		Professor(int a,string b,char c,int y,int m,int d):Teacher(a,b,c),birthday(y,m,d) {};
		void display();
		void change(int y,int m,int d) {
			birthday.change(y,m,d);
		}
	private:
		BirthDate birthday;
};
void Professor::display() {
	Teacher::display();
	birthday.display();
}
int main() {
	Professor prof1(123,"jack",'m',1999,9,9);
	cout<<endl<<"初值:"<<endl;
	prof1.display();
	cout<<endl<<"新数据:"<<endl;
	prof1.change(2000,1,1);
	prof1.display();
	return 0;
}
