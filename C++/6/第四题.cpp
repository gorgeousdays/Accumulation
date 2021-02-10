#include<iostream>
#include<cmath>
using namespace std;
class Shape {
	public:
		virtual double area()=0;
};
class Circle:public Shape {
	public:
		Circle(double r):radius(r) {}
		virtual double area() {
			return 3.14*radius*radius;
		}
	protected:
		double radius;
};


class Rectangle:public Shape {
	public:
		Rectangle(double r,double l):width(r),height(l) {}
		virtual double area() {
			return width*height;
		}
	protected:
		double width;
		double height;
};


class Triangle:public Shape {
	public:
		Triangle(float x,float y,float z):r1(x),r2(y),r3(z) {};
		virtual double area() {
			double s=0.5*(r1+r2+r3);
			return sqrt(s*(s-r1)*(s-r2)*(s-r3));
		}
	protected:
		double r1,r2,r3;
};
class Trapezoid:public Shape {
	public:
		Trapezoid(double r,double l,double k):top(r),bottom(l),height(k) {}
		virtual double area() {
			return 0.5*(top+bottom)*height;
		}
	protected:
		double top;
		double bottom;
		double height;
};
class Square:public Shape {
	public:
		Square(double r):side(r) {}
		virtual double area() {
			return side*side;
		}
	protected:
		double side;
};
int main() {
	float r,a,w1,w2,w,h,r1,r2,r3,b;
	cout<<"������Բ�İ뾶��";
	cin>>r;
	Circle circle(r);
	cout<<"Բ���Ϊ"<<circle.area()<<endl; 
	cout<<"�����������εı߳���";
	cin>>a;
	Square square(a);
	cout<<"���������Ϊ"<<square.area()<<endl;
	cout<<"�����볤���ε����߳���";
	cin>>a>>b;
	Rectangle rectangle(a,b);
	cout<<"���������Ϊ"<<rectangle.area()<<endl;
	cout<<"���������ε��ϵ��µ׺͸ߣ�";
	cin>>w1>>w2>>h;
	Trapezoid trapezoid(w1,w1,h);
	cout<<"�������Ϊ"<<trapezoid.area()<<endl;
	cout<<"�����������ε����߳���";
	cin>>r1>>r2>>r3;
	Triangle triangle(r1,r2,r3);
	cout<<"���������Ϊ"<<triangle.area()<<endl;
	Shape *pt[5]= {&circle,&square,&rectangle,&trapezoid,&triangle};
	double areas=0.0;
	for(int i=0; i<5; i++)
		areas=areas+pt[i]->area();
	cout<<"�����Ϊ"<<areas<<endl;
	return 0;
}
