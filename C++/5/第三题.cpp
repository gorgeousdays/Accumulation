#include<iostream>
using namespace std;
class teacher {
	public:
		teacher(string a,int b,char c,string d,string e,string f) {
			name=a;age=b;sex=c;title=d;address=e;tel=f;
		}
		void display();
	protected:
		string name,address,tel,title;
		char sex;
		int age;
};
void teacher::display(){
	cout<<"name: "<<name<<endl;
			cout<<"age: "<<age<<endl;
			cout<<"sex: "<<sex<<endl;
			cout<<"title: "<<title<<endl;
			cout<<"address: "<<address<<endl;
			cout<<"tel: "<<tel<<endl;
}
class cadre {
	public:		
		cadre(string a,int b,char c,string d,string e,string f) {
			name=a;
			age=b;
			sex=c;
			post=d;
			address=e;
			tel=f;
		}
	protected:
		string name,address,tel,post;
		char sex;
		int age;
};
class teacher_cadre:public teacher,public cadre {
	public:
		teacher_cadre(string a,int b,char c,string d,string e,string f,string g,double h)
			:cadre(a,b,c,g,e,f),teacher(a,b,c,d,e,f) {
			wage=h;
		}
		void show();
	private:
		double wage;
};
void teacher_cadre::show(){
	display();
			cout<<"post: "<<post<<endl;
			cout<<"wage: "<<wage<<endl;
}
int main() {
	string a,d,e,f,g;
	int b;
	char c;
	double h;
	cin>>a>>b>>c>>e>>f>>d>>g>>h;
	teacher_cadre t(a,b,c,d,e,f,g,h);
	t.show();
}
