#include "RandomNumber.h"
#include<iostream>
using namespace std;
const int INF = 9999;

// 交换a, b的值
template<class Type> 
void Swap(Type &a, Type &b){
    Type temp;
    temp = a;
    a = b;
    b = temp;
}

template<class Type> 
Type select(Type a[], int lt, int rt, int k){
    // 计算a[lt:rt]中第k小元素
    static RandomNumber rnd;
    while(true)
    {
        if(lt > rt)
            return a[lt];
        int i = lt, j = lt+rnd.Random(rt-lt+1);   // 随机选择的划分基准
        Swap(a[i], a[j]);
        j = rt+1;
        Type pivot = a[lt];
        //以划分基准为轴作元素交换
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
        // 对子数组重复划分过程
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
    // 计算a[0: n-1]中第k小元素
    // 假设a[n]是一个键值无穷大的元素
    if(k < 1 || k > n)
        cerr << "Wrong!" << endl;
    return select(a, 0, n-1, k);
}

int main(){
    int arr[7] = {3, 2, 5, 7, 10, INF};
    cout << Select(arr, 6, 4) << endl;
}
