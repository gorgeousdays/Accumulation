#include<iostream>
#include<cmath>
using namespace std;
class Shape
{
	public:
	    virtual void printArea()=0;	
};
class Circle:public Shape
{
	public:
	 Circle(float r):radius(r){};
	 void printArea() {cout<<"圆面积为"<<3.14159*radius*radius<<endl;}	
	protected:
		float radius;
};
class Rectangle:public Shape
{
	public:
		Rectangle(float w,float h):width(w),height(h){
};
	 void printArea();
	protected:
		float height;
		float width;
};
void Rectangle::printArea()
{
	cout<<"矩形面积为"<<width*height<<endl;
}
class Triangle:public Shape
{
	public:
		Triangle(float x,float y,float z):r1(x),r2(y),r3(z){}; 
     	 void printArea();
	private:
		float r1,r2,r3;
};
void Triangle::printArea()
{
	double s=0.5*(r1+r2+r3);
   cout<<"三角形面积为"<<sqrt(s*(s-r1)*(s-r2)*(s-r3))<<endl; 
}
int main()
{    
	Circle c(1.1);
	c.printArea();
	Rectangle r(1.1,1.2);
	r.printArea();
	Triangle t(1.1,1.2,1.3);
	t.printArea();
}
