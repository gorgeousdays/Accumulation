#include<iostream>
using namespace std;
class Point{
	public:
		Point(double a,double b):x(a),y(b){
		}
		virtual ~Point(){
			cout<<"executing Point destructor"<<endl;
		}
	private:
		double x,y;
};
class Circle:public Point{
	public:
	Circle(double a,double b,double c):Point(a,b),radus(c){
	} 
	virtual ~Circle(){
		cout<<"executing Circle destructor"<<endl;
	}
	private:
		int radus;
};
int main(){
	Point *p=new Circle(1.1,1.2,1.3);
	delete p;
	return 0;
} 
