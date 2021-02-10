//��ƺ�����ʵ��ɾ�������������ظ�Ԫ�صĹ��ܡ�Ҫ�󣺾����ܱ������ݴ����ƶ���ͬʱ����ԭʼ����˳�򣬲������㷨��ʱ�临�Ӷȡ�
/*�ο�https://www.techiedelight.com/remove-duplicates-vector-cpp/
https://stackoverflow.com/questions/12200486/how-to-remove-duplicates-from-unsorted-stdvector-while-keeping-the-original-or
set��unordered_set���� https://www.cnblogs.com/Jawen/p/10821702.html 
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
	return sizeof(arr) / sizeof(arr[0]); //length����ʵ�ַ������鳤�� 
}

//����һ �Ƚ�Ԫ�� �ظ���ɾ�� ʱ�临�Ӷ�O(n^3) �ռ临�Ӷ�O(1)
/*
template<class T>
void delete_repeat(vector<T> &v){
	for (int i=0; i<v.size(); i++)
		for (int j=i+1; j<v.size(); j++)
				if(v[i]==v[j]){
				    v.erase(v.begin()+j);
				    j--;//ɾ��һ��Ԫ�غ� �ᵼ����һ��Ԫ��ǰ�� ���޷��жϵ� ������Ҫj--
				}
}*/

//������ �����µ�vector ��ԭ��Ԫ�ز��ظ���push_back ʱ�临�Ӷ�O(n^2) �ռ临�Ӷ�O(n)
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

//������  ���ظ�����ǰ���� ʱ�临�Ӷ�O(n^2)
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

//������������ ������ ʹ��unordered_set ʧ�� ��Ϊ����ڹ�ϣ��
//������˳�򰴹�ϣ������˳��
/*template<class T>
void delete_repeat(vector<T> &v){
  unordered_set <T>s(v.begin(), v.end());
  v.assign(s.begin(), s.end());
}*/

//������ ʹ��set��find���� ʱ�临�Ӷ�O(logN) 
template<class T>
void delete_repeat(vector<T> &v){
	vector<T> v1;
	set<T> s; 
	v1.push_back(v[0]);
	s.insert(v1[0]); 
	for (int i=1; i<v.size(); i++){
		if(s.find(v[i])== s.end()){ //set��find����ʱ�临�Ӷ�O(logN
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
	cout<<"ԭ������"; 
	for (int i=0; i<v.size(); i++)
		cout<<v[i]<<' ';
	cout<<endl;
	delete_repeat(v);
	cout<<"ɾ���ظ�Ԫ�غ�����"; 
	for (int i=0; i<v.size(); i++)
		cout<<v[i]<<' ';
	cout<<endl;
	return 0;
}
