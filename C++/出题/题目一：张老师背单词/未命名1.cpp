//张老师背单词
//题目描述 张老师准备出国旅游，于是他最近开始背单词背单词，为了更好的掌握每一个单词，
//对每个单词，张老师第一天需要花5分钟背，
//第二天要花4分钟复习，第三天要花3分钟复习，第四天要花2分钟复习
//第五天要花1分钟复习，也就是说张老师完整的背完一个单词需要五天
//现在 张老师每天有100分钟背单词，他会花一点时间先复习之前的单词，再在剩下的时间里背尽可能多的新单词
//求张老师第n天背的新单词个数
//输入 输入多组数据，第一行m表示数据组数，接下来的m行分别表示张老师背单词天数n
//输出 输出有多行，分别表示张老师第n天背的新单词的个数
//样例输入
//样例输出
#include<iostream>
using namespace std;
int new_word(int n) {
	if(n==1) return 20;
	if(n==2) return 4;
	if(n==3) return 4;
	if(n==4) return 6;
	if(n>=8)
	    if(n%2==0) return 6;
	    else return 7;
	int t=5;
	int k=100;
	for(int i=n-1; i>=n-4; i--) {
		k-=new_word(i)*(t-1);
		t--;
	}
	return k/5;
}
int main() {
	int m,n;
	cin>>m;
	for(int i=1; i<=m; i++) {
		cin>>n;
		cout<<new_word(n)<<endl;
	}
}

