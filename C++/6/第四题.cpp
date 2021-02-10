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
	cout<<"请输入圆的半径：";
	cin>>r;
	Circle circle(r);
	cout<<"圆面积为"<<circle.area()<<endl; 
	cout<<"请输入正方形的边长：";
	cin>>a;
	Square square(a);
	cout<<"正方形面积为"<<square.area()<<endl;
	cout<<"请输入长方形的两边长：";
	cin>>a>>b;
	Rectangle rectangle(a,b);
	cout<<"长方形面积为"<<rectangle.area()<<endl;
	cout<<"请输入梯形的上底下底和高：";
	cin>>w1>>w2>>h;
	Trapezoid trapezoid(w1,w1,h);
	cout<<"梯形面积为"<<trapezoid.area()<<endl;
	cout<<"请输入三角形的三边长：";
	cin>>r1>>r2>>r3;
	Triangle triangle(r1,r2,r3);
	cout<<"三角形面积为"<<triangle.area()<<endl;
	Shape *pt[5]= {&circle,&square,&rectangle,&trapezoid,&triangle};
	double areas=0.0;
	for(int i=0; i<5; i++)
		areas=areas+pt[i]->area();
	cout<<"总面积为"<<areas<<endl;
	return 0;
}
