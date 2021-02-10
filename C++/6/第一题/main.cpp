#include <iostream>
#include "point.h"
#include "circle.h"
#include "cylinder.h" 
using namespace std;
int main() {
	Point p(3.5,6.4);
	cout<<"x="<<p.getX()<<"y="<<p.getY()<<endl;
	p.setPoint(8.5,6.8);
	cout<<"Point(new)"<<p<<endl;
	Circle c(1,2,3);
	cout<<"radius="<<c.getRadius()<<endl;
	c.setRadius(4);
	cout<<"Circle(new)"<<c<<endl;
	Cylinder c2(1,2,3,4);
	cout<<"heighrt="<<c2.getHeight()<<endl;
	c2.setHeight(5);
	cout<<"cylinder(new)"<<c2<<endl; 
}
