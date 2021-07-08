#include<iostream>
#include<vector>
using namespace std;
int FindMax(vector<int>& nums) {
	vector<int>dp(nums.size(),nums[0]);
	int MaxSum=nums[0];
	for(int i=1; i<nums.size(); i++) {
		dp[i]=max(dp[i-1]+nums[i],nums[i]);//求解局部最优解
		MaxSum=max(dp[i],MaxSum);//求解全局的最优解
	}
	return MaxSum;
}
int main() {
	int a[9] = {-2,1,-3,4,-1,2,1,-5,4};
	vector<int> nums;
	nums.insert(nums.begin(), a, a+9);
	cout<<FindMax(nums);
}
