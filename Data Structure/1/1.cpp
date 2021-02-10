/*对比数组和向量的使用方法
设计两个函数实现冒泡排序算法，待排序数据分别以数组和向量作为参数传递到排序算法子函数，
要求通过该子函数对数据进行排序，排序结果返回到主函数，不得修改破坏原始待排数据；*/

#include<iostream>
#include<vector>
#include<algorithm>
#include <iterator> //ostream_iterator在<iterator>实现vector的直接输出
using namespace std;
 
template<class T>
int length(T& arr){
	return sizeof(arr) / sizeof(arr[0]); //length方法实现返回数组长度 
}

void bubble_sort(int a[], int n){	
	for (int i=1; i<n; i++)
		for (int j=1; j<n-i+1; j++)
			if (a[j-1] > a[j]){
				a[j]=a[j]+a[j-1];
				a[j-1]=a[j]-a[j-1];
				a[j]=a[j]-a[j-1];	
			}	
}
void bubble_sort_vec(vector<int> &v){
	for (int i = 1; i<v.size(); i++) 
		for(int j=1; j<v.size()-i+1; j++)
			if (v[j-1] > v[j]){
				v[j]=v[j]+v[j-1];
				v[j-1]=v[j]-v[j-1];
				v[j]=v[j]-v[j-1];
			} 
}

//重载print函数实现数组和向量的输出
void print(int a[], int n){
	for (int i=0; i<n; i++)
		cout<<a[i]<<' ';
	cout<<endl;
} 
void print(vector<int> &v){
	copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
} 

int main(){
    int a[] = {3,1,4,1,5,9,2,6,5,3,5};
    int a_length=length(a);
    //数组排序
    int b[length(a)];
    memcpy(b,a,sizeof(a));
    bubble_sort(b,a_length);

    cout<<"原数组：";
    print(a,a_length); 
    cout<<"排序结果：";
    print(b,a_length);
    cout<<"原数组：";
    print(a,a_length);
    //向量排序 
    vector<int>ve,ve2;
    for(int i=0;i<a_length; i++)
        ve.push_back(a[i]);
    ve2=ve;
    bubble_sort_vec(ve2);

    cout<<"原向量：";
	print(ve);
	cout<<"排序结果：";
	print(ve2);
    cout<<"原向量：";
	print(ve);  
	return 0;
}
