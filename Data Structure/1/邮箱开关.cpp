/*有一天晚上，邮差Peter感到非常无聊，为了打破夜班的单调，
他使用邮局中的一行邮箱进行了以下的实验。
这些邮箱被从1～150进行了编号，
然后从邮箱2开始，他打开了所有编号为偶数的邮箱的门，而保持其他邮箱的门关着。
接着从邮箱3开始，每隔3个邮箱，如果这个邮箱的门是关着的他就打开这个邮箱的门，而如果门是开着的他就关上门。
然后他每隔4个邮箱重复这个过程，再每隔5个邮箱重复这个过程，如此下去。
当结束时，他被关着的邮箱的分布所惊讶了。编写一个程序来判断哪些邮箱是关着的。*/
#include<iostream>
#include<vector>
using namespace std;
class Solution{
    public:
        vector<int> select_postbox(int n){
            vector<bool>s(n,false);
            int t=1;
            while(t<=n){
                for(int i=t;i<n;i=i+(t+1)){
                    s[i]=!s[i];
                }
                t++;
            }
            vector<int> nums;
            for(int i=0;i<n;i++){
                if(!s[i])  
				    nums.push_back(i+1);
            }
        return nums;
    }
};
int main(){
	Solution Peter;
    vector<int> p=Peter.select_postbox(150);
    for(int i=0; i<p.size(); i++){
        cout<<p[i]<<endl;
    }
}

