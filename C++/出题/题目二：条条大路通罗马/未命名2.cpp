//条条大路通罗马
//题目描述：小明要去罗马，罗马坐标（x1，y1） 小明坐标（x2，y2）每回合可以走1步,x1,x2,x3,x4均为整数
//x或y的坐标加一或减一）要求小明的每一步都必须离罗马更近，问小明到罗马有几种方法
//输入x1，y1，x2，y2属于-10到10,若小明坐标等于罗马坐标则输出1 
//输出 有几种方法可0以到罗马0
#include<iostream>
#include<cmath> 
using namespace std;
int main(){
	int x1,x2,y1,y2,m,n;
	cin>>x1>>y1>>x2>>y2; 
	m=abs(x1-x2);
	n=abs(y1-y2);
	long long path[21][21]={0};
	for(int y=0; y<=n; y++)
		path[0][y]=1;
	for(int x=1; x<=m; x++) {
		path[x][0]=path[x-1][0];
		for(int y=1; y<=n; y++)
			path[x][y]=path[x-1][y]+path[x][y-1];
	}
	cout<<path[m][n];
}


