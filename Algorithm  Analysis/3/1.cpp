#include<iostream>
#define N 1000
using namespace std;
int sum[N]={0};
int a[N]={0};
int dp[N][N];
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	//����ǰ׺��  ͨ��ǰ׺�ͼ�������������� 
	for(int i=1;i<=n;i++)
	    sum[i]=sum[i-1]+a[i-1];
	for(int len=2;len<=n;len++){ //���䳤�� 
		for(int L=0;L+len-1<n;L++){ //��˵� 
		    int R=L+len-1;
			dp[L][R]=1e6;
			for(int k=L;k<R;k++){
				dp[L][R]=min(dp[L][R], dp[L][k] + dp[k+1][R] + sum[R+1] - sum[L]);
			} 
		} 
	}
	cout<<dp[0][n-1];
} 
