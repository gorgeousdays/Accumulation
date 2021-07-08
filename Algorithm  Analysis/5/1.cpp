#include<iostream>
#define Max 100 
using namespace std;
int dp[Max][Max];
string s1,s2;
void LCS(int i ,int j){
	if (i ==0 || j==0) return;
	if(s1[i-1]==s2[j-1]) {
		LCS(i-1,j-1);
		cout<<s1[i-1];
	} else if(dp[i-1][j]>=dp[i][j-1])
		LCS(i-1,j);
	else
		LCS(i,j-1);
}
int main() {
	cout<<"Please enter the first sequence:";
	cin>>s1;
	cout<<"Please enter the second sequence:";
	cin>>s2;
	int len1=s1.length();
	int len2=s2.length();
	for(int i=0; i<=len1; i++)
		dp[i][0]=0;
	for(int i=0; i<=len2; i++)
		dp[0][i]=0;
	for(int i=1; i<=len1; i++) {
		for(int j=1; j<=len2; j++) {
			if(s1[i-1]==s2[j-1])
				dp[i][j]=dp[i-1][j-1]+1;
			else if(dp[i-1][j]>=dp[i][j-1])
				dp[i][j]=dp[i-1][j];
			else
				dp[i][j]=dp[i][j-1];
		}
	}
	cout<<"The longest common sequence is:";
	LCS(len1,len2);
}
