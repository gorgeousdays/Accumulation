//������·ͨ����
//��Ŀ������С��Ҫȥ�����������꣨x1��y1�� С�����꣨x2��y2��ÿ�غϿ�����1��,x1,x2,x3,x4��Ϊ����
//x��y�������һ���һ��Ҫ��С����ÿһ���������������������С���������м��ַ���
//����x1��y1��x2��y2����-10��10,��С����������������������1 
//��� �м��ַ�����0�Ե�����0
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


