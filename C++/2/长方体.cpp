#include<iostream>
using namespace std;
class cuboids {
	private: 
		double lengh[3],width[3],height[3];
	public:
		void myinput();
		void myoutput();
		double calculate(double lengeh,double width,double height);
};
void cuboids::myinput() {
	cout<<"��������������������ĳ����"<<endl;
	for(int i=0; i<=2; i++)
		cin>>lengh[i]>>width[i]>>height[i];
}
double cuboids::calculate(double lengh,double width,double height) {
	return lengh*width*height;
}
void cuboids::myoutput() {
	for(int i=0; i<=2; i++)
		cout<<"��"<<i+1<<"�����������Ϊ"<<calculate(lengh[i],width[i],height[i])<<endl; 
	}
int main() {
	cuboids mycuboids;
	mycuboids.myinput();
	mycuboids.myoutput();
}
