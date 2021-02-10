/*�Ա������������ʹ�÷���
�����������ʵ��ð�������㷨�����������ݷֱ��������������Ϊ�������ݵ������㷨�Ӻ�����
Ҫ��ͨ�����Ӻ��������ݽ����������������ص��������������޸��ƻ�ԭʼ�������ݣ�*/

#include<iostream>
#include<vector>
#include<algorithm>
#include <iterator> //ostream_iterator��<iterator>ʵ��vector��ֱ�����
using namespace std;
 
template<class T>
int length(T& arr){
	return sizeof(arr) / sizeof(arr[0]); //length����ʵ�ַ������鳤�� 
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

//����print����ʵ����������������
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
    //��������
    int b[length(a)];
    memcpy(b,a,sizeof(a));
    bubble_sort(b,a_length);

    cout<<"ԭ���飺";
    print(a,a_length); 
    cout<<"��������";
    print(b,a_length);
    cout<<"ԭ���飺";
    print(a,a_length);
    //�������� 
    vector<int>ve,ve2;
    for(int i=0;i<a_length; i++)
        ve.push_back(a[i]);
    ve2=ve;
    bubble_sort_vec(ve2);

    cout<<"ԭ������";
	print(ve);
	cout<<"��������";
	print(ve2);
    cout<<"ԭ������";
	print(ve);  
	return 0;
}
