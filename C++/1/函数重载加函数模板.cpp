#include<iostream>
using namespace std;
int max(int a, int b, int c) {
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}
double max(double a,double b,double c) {
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}

long max(long a,long b,long c) {
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}
int main() {
	int a1,b1,c1;
	double a2,b2,c2;
	long a3,b3,c3;
	cin>>a1>>b1>>c1>>a2>>b2>>c2>>a3>>b3>>c3;
	cout<<max(a1,b1,c1)<<"  "<<max(a2,b2,c2)<<" "<<max(a3,b3,c3);
}
#include<iostream>
using namespace std;
template<typename T>
T max(T a,T b,T c){
	if (b>a) a=b;
	if(c>a) a=c;
     return a;
}
int main(){
	int a1,b1,c1;
	double a2,b2,c2;
	long a3,b3,c3;
	cin>>a1>>b1>>c1>>a2>>b2>>c2>>a3>>b3>>c3;
	cout<<max(a1,b1,c1)<<"  "<<max(a2,b2,c2)<<" "<<max(a3,b3,c3);
} 
