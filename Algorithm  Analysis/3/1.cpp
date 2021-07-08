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
	//计算前缀和  通过前缀和减法来计算区间和 
	for(int i=1;i<=n;i++)
	    sum[i]=sum[i-1]+a[i-1];
	for(int len=2;len<=n;len++){ //区间长度 
		for(int L=0;L+len-1<n;L++){ //左端点 
		    int R=L+len-1;
			dp[L][R]=1e6;
			for(int k=L;k<R;k++){
				dp[L][R]=min(dp[L][R], dp[L][k] + dp[k+1][R] + sum[R+1] - sum[L]);
			} 
		} 
	}
	cout<<dp[0][n-1];
} 
