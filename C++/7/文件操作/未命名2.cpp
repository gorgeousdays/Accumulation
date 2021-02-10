#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Person {
	public:
		Person(int m=0, string n="", int a=0, int w=0): num(m), name(n), age(a), wage(w) {}
		void show() {
			cout<<num<<" "<<name<<" "<<age<<" "<<wage;
		}
		void change(int m=0, string n="", int a=0, int w=0) {
			num=m;
			name=n;
			age=a;
			wage=w;
		}
		int  getnum() {
			return num;
		}
		string getname() {
			return name;
		}
		int  getage() {
			return age;
		}
		int getwage() {
			return wage;
		}
		Person& operator=(Person& p) {
			this->change(p.getnum(),p.getname(),p.getage(),p.getwage());
			return *this;
		}
	private:
		int num,age,wage;
		string name;
};
int main() {
	//输入数据
	Person p[5];
	string t_name[5];
	int t_num[5],t_age[5],t_wage[5];
	for(int i=0; i<=4; i++) {
		cin>>t_num[i]>>t_name[i]>>t_age[i]>>t_wage[i];
		p[i].change(t_num[i],t_name[i],t_age[i],t_wage[i]);
	}
	//排序
	Person temp;
	for(int i = 0; i < 5; i++) {
		for(int j = i + 1; j < 5; j++) {
			if(p[i].getnum()>p[j].getnum()) {
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	//输出到文件 
	ofstream outfile1("f.dat", ios :: out);
    if(!outfile1)
    {
        cerr << "f.dat 打开错误" << endl;
        exit(1);
    }
    for(int i = 0; i < 5; i++)
    {
        outfile1 << p[i].getnum() << " "
                 << p[i].getname() << " "
                 << p[i].getage()<< " "
                 << p[i].getwage()<< endl;
    }
    outfile1.close();
}
