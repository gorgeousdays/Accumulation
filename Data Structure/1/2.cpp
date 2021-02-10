//设计函数，实现删除向量中所有重复元素的功能。要求：尽可能避免数据大量移动，同时保持原始数据顺序，并分析算法的时间复杂度。
/*参考https://www.techiedelight.com/remove-duplicates-vector-cpp/
https://stackoverflow.com/questions/12200486/how-to-remove-duplicates-from-unsorted-stdvector-while-keeping-the-original-or
set与unordered_set区别 https://www.cnblogs.com/Jawen/p/10821702.html 
*/ 
#include<iostream>
#include<vector>
#include <algorithm>
#include<set> 
#include<tr1/unordered_set>
using namespace std;
using namespace std::tr1;

template<class T>
int length(T& arr){
	return sizeof(arr) / sizeof(arr[0]); //length方法实现返回数组长度 
}

//方法一 比较元素 重复则删除 时间复杂度O(n^3) 空间复杂度O(1)
/*
template<class T>
void delete_repeat(vector<T> &v){
	for (int i=0; i<v.size(); i++)
		for (int j=i+1; j<v.size(); j++)
				if(v[i]==v[j]){
				    v.erase(v.begin()+j);
				    j--;//删除一个元素后 会导致下一个元素前移 即无法判断到 所以需要j--
				}
}*/

//方法二 创建新的vector 与原先元素不重复则push_back 时间复杂度O(n^2) 空间复杂度O(n)
/*
template<class T>
void delete_repeat(vector<T> &v){
	vector<T> v1;
	v1.push_back(v[0]);
	for (int i=1; i<v.size(); i++){
		bool repeat = false;
		for (int j=0;j<v1.size(); j++){
			if (v[i]==v1[j])
				repeat = true;
		}
		if(!repeat)
			v1.push_back(v[i]);
	}
	v = v1;	
}*/

//方法三  若重复则向前覆盖 时间复杂度O(n^2)
/*
template<class T>
void delete_repeat(vector<T> &v){	
    for(int i=0;i<v.size();i++){
    	for (int j=v.size()-1; j>=i+1; j--){
    		if(v[i]==v[j]){
    			if(j==v.size()-1) 
    			    v.pop_back();
    			else
				   v[j]=v[j+1];
			}
		}
	} 
}*/

//！！！不可行 方法四 使用unordered_set 失败 因为其基于哈希表
//最后输出顺序按哈希函数的顺序
/*template<class T>
void delete_repeat(vector<T> &v){
  unordered_set <T>s(v.begin(), v.end());
  v.assign(s.begin(), s.end());
}*/

//方法五 使用set的find方法 时间复杂度O(logN) 
template<class T>
void delete_repeat(vector<T> &v){
	vector<T> v1;
	set<T> s; 
	v1.push_back(v[0]);
	s.insert(v1[0]); 
	for (int i=1; i<v.size(); i++){
		if(s.find(v[i])== s.end()){ //set的find函数时间复杂度O(logN
		    s.insert(v[i]); 
			v1.push_back(v[i]);
		} 
	}
	v = v1;	
}

int main(){
	vector<int> v, v1;
	int a[] = {3,1,4,1,5,9,2,6,5,3,5};
	int a_length=length(a);
	for (int i=0; i<a_length; i++)
		v.push_back(a[i]);
	cout<<"原向量："; 
	for (int i=0; i<v.size(); i++)
		cout<<v[i]<<' ';
	cout<<endl;
	delete_repeat(v);
	cout<<"删除重复元素后结果："; 
	for (int i=0; i<v.size(); i++)
		cout<<v[i]<<' ';
	cout<<endl;
	return 0;
}
