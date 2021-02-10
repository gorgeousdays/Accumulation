#include <iostream>
#include "point.h"
#include "circle.h"
#include "cylinder.h"
using namespace std;
Cylinder::Cylinder(double a, double b, double r, double h)
	:Circle(a, b, r), height(h){}
void Cylinder::setHeight(double h) {height=h;}
double Cylinder::getHeight() const {return height;}
double Cylinder::area() const {return 2*Circle::area()+2*3.14159*radius*height;}
double Cylinder::volume() const {return Circle::area()*height;}
ostream& operator<<(ostream &output, const Cylinder &cy)
{
	output<<"Center=["<<cy.x<<", "<<cy.y<<"], r="<<cy.radius<<", h="<<cy.height
		<<"\narea="<<cy.area()<<", volume="<<cy.volume()<<endl;
	return output;
}
