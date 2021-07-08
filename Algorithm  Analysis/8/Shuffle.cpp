#include "RandomNumber.h"
#include<iostream>
using namespace std;

// 交换a, b的值
using namespace std;

// 交换a, b的值
template<class Type> 
void Swap(Type &a, Type &b){
    Type temp;
    temp = a;
    a = b;
    b = temp;
}

template<class Type> 
void Shuffle (Type a[], int len){
    // 随机洗牌算法
    static RandomNumber rnd;
    for (int i = 0; i < len; ++i) 
    {
        int j = rnd.Random(len-i) + i;      
        Swap (a[i], a[j]) ;    
    }
}

int main(){
    int arr[7] = {3, 2, 5, 7, 10};
    Shuffle(arr, 5);
    for(int i=0;i<5;i++){
    	cout<<arr[i]<<" ";
	}
}
