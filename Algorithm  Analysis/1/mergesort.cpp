#include<iostream> 
#include<ctime>
#include<cstdlib>
#include<vector>

#define MAX 20
#define CutOff 7
using namespace std;

template<typename T>
void Insert_Sort(T a[], int left, int right) {
    for (int i = left; i < right; i++) {
        int j = i-1;
        T v = a[i];
        while (j>=0&&a[j]>v) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = v;
    }
}

template<typename T>
void Merge(T a[], T aux[], int left, int mid, int right) {
	int i = left, j = mid+1;
	for (int k = left; k <= right; k++) {
		if (i > mid) aux[k] = a[j++];
		else if (j > right) aux[k] = a[i++];
		else if (a[j] < a[i]) aux[k] = a[j++];
		else aux[k] = a[i++];
	}
}

template<typename T>
void Merge_Sort(T a[], T aux[], int left, int right){
	if (right - left <= CutOff) {
		Insert_Sort(a, left, right+1);
		return;
	}
	int mid = left + (right - left) / 2;
	Merge_Sort(a, aux, left, mid);
	Merge_Sort(a, aux, mid+1, right);
	if (!(a[mid + 1] < a[mid])) return;
	Merge(a, aux, left, mid, right);
}

//存储随机序列、递增序列、递减序列
int Number_Ran_[MAX]= {0}, Number_Asc_[MAX]= {0}, Number_Des_[MAX]= {0};
//生成数字序列
void Generate_Number() {
	srand((int)time(NULL));
	for (int i=0; i<=MAX; i++) {
		Number_Ran_[i] = rand();
		Number_Asc_[i] = i;
		Number_Des_[i] = MAX - i;
	}
}

int main(){
	Generate_Number();
	int *aux=new int(MAX);
	
	time_t begin = clock();
	Merge_Sort(Number_Ran_, aux, 0, 20);
	time_t end = clock();
	cout<<"Merge sort cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
	
	for (int i = 0; i <= 20; i++){
		cout <<Number_Ran_[i] << endl;
	}
	delete []aux;
}
