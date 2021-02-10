#include<fstream>
#include<iostream>
using namespace std;
struct student {
	string name;
	string sex;
	double score;
};
int main() {
	ifstream infile;
	ofstream outfile;
	outfile.open("aa.txt");
	student a[6],s;
	for(int i=1; i<=5; i++) {
		cin>>a[i].name>>a[i].sex>>a[i].score;
		outfile<<a[i].name<<endl<<a[i].sex<<endl<<a[i].score<<endl;
	}
	outfile.close();
	infile.open("aa.txt");
	while(!infile.eof()) {
		infile>>s.name>>s.sex>>s.score;
		if(s.score>60) {
			cout<<s.name<<" "<<s.sex<<" "<<s.score<<endl;
		}
	}
	infile.close();
}
