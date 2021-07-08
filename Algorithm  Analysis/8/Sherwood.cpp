#include "RandomNumber.h"
#include<iostream>
using namespace std;
const int INF = 9999;

// ����a, b��ֵ
template<class Type> 
void Swap(Type &a, Type &b){
    Type temp;
    temp = a;
    a = b;
    b = temp;
}

template<class Type> 
Type select(Type a[], int lt, int rt, int k){
    // ����a[lt:rt]�е�kСԪ��
    static RandomNumber rnd;
    while(true)
    {
        if(lt > rt)
            return a[lt];
        int i = lt, j = lt+rnd.Random(rt-lt+1);   // ���ѡ��Ļ��ֻ�׼
        Swap(a[i], a[j]);
        j = rt+1;
        Type pivot = a[lt];
        //�Ի��ֻ�׼Ϊ����Ԫ�ؽ���
        while(true)
        {
            while(a[++i] < pivot);
            while(a[--j] > pivot);
            if(i >= j)
                break;
            Swap(a[i], a[j]);
        }
        if(j - lt + 1 == k)
            return pivot;
        a[lt] = a[j];
        a[j] = pivot;
        // ���������ظ����ֹ���
        if(j - lt + 1 < k)
            {
                k = k - j + lt - 1;
                lt = j + 1;
            }
        else
            rt = j - 1;
    }
}

template<class Type>  
Type Select(Type a[], int n, int k){
    // ����a[0: n-1]�е�kСԪ��
    // ����a[n]��һ����ֵ������Ԫ��
    if(k < 1 || k > n)
        cerr << "Wrong!" << endl;
    return select(a, 0, n-1, k);
}

int main(){
    int arr[7] = {3, 2, 5, 7, 10, INF};
    cout << Select(arr, 6, 4) << endl;
}
