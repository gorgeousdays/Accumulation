/*��һ�����ϣ��ʲ�Peter�е��ǳ����ģ�Ϊ�˴���ҹ��ĵ�����
��ʹ���ʾ��е�һ��������������µ�ʵ�顣
��Щ���䱻��1��150�����˱�ţ�
Ȼ�������2��ʼ�����������б��Ϊż����������ţ�����������������Ź��š�
���Ŵ�����3��ʼ��ÿ��3�����䣬��������������ǹ��ŵ����ʹ����������ţ���������ǿ��ŵ����͹����š�
Ȼ����ÿ��4�������ظ�������̣���ÿ��5�������ظ�������̣������ȥ��
������ʱ���������ŵ�����ķֲ��������ˡ���дһ���������ж���Щ�����ǹ��ŵġ�*/
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

