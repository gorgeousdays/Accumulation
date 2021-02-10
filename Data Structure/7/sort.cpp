#include<iostream>
#include<ctime>
#include<queue>
#include<vector>
#include "d_random.h"

using namespace std;
#define MAX 100000
//存储随机序列、递增序列、递减序列
int Number_Ran_[MAX]= {0}, Number_Asc_[MAX]= {0}, Number_Des_[MAX]= {0};
//生成数字序列
void Generate_Number() {
	randomNumber R;
	for (int i=0; i<MAX; i++) {
		Number_Ran_[i] = R.random();
		Number_Asc_[i] = i;
		Number_Des_[i] = MAX - i;
	}
}

//选择排序
void Selection_Sort(const int array[],int n,string s) {
	int pass,j,temp;
	int a[MAX];
	int smallIndex;
	memcpy(a, array, sizeof(a));
    /*用sizeof(array)或者MAX计算结果会出错,
	因为MAX=100,sizeof(array)=100,可以用sizeof(array)*MAX代替array(a)
	也可以通过for循环赋值 
	*/ 
	time_t begin = clock();
	for (pass = 0; pass < n-1; pass++){
		int smallIndex = pass;
		for (j = pass+1; j < n; j++)
			if (a[j] < a[smallIndex])
				smallIndex = j;
		if (smallIndex != pass) {
			temp = a[pass];
			a[pass] = a[smallIndex];
			a[smallIndex] = temp;
		}
	}
	time_t end = clock();
	cout<<s<<" cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
}

//插入排序
void Insertion_Sort(int array[], int n,string s) {
	int i, j, temp;
	int a[MAX];
	memcpy(a, array, sizeof(a));
	time_t begin = clock();
	for (i = 1; i < n; i++) {
		j = i;
		temp = a[i];
		while (j > 0 && temp < a[j-1]) {
			a[j] = a[j-1];
			j--;
		}
		a[j] = temp;
	}
	time_t end = clock();
	cout<<s<<" cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
}

//冒泡排序
void Bubble_Sort(int array[], int n,string s) {
	int temp,i,j;
	//bool exchange;//增加哨兵 排序完成则不继续冒泡 
	int a[MAX];
	memcpy(a, array, sizeof(a));
	time_t begin = clock();
	for(i=0; i<n; i++) {
		//exchange=false; 
		for(j=0; j<n-i; j++) {
			if(a[j]>a[j+1]) {
				temp=a[j+1];
				a[j+1]=a[j];
				a[j]=temp;
				//exchange=true; 
			}
		}
		//if(!exchange) return; 
	}
	time_t end = clock();
	cout<<s<<" cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
}

//交换排序
void Exchange_Sort(int array[], int n,string s) {
	int i, j, temp;
	int a[MAX];
	memcpy(a, array, sizeof(a));
	time_t begin = clock();
	for (i = 0; i < n-1; i++)
		for (j = i; j < n-1; j++)
			if (a[i] > a[j+1]) {
				temp = a[i];
				a[i] = a[j+1];
				a[j+1] = temp;
			}
	time_t end = clock();
	cout<<s<<" cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
}

//快速排序
int pivotIndex(int *v, int first, int last){
	int mid, scanUp, scanDown;
	int pivot, temp;
	if (first == last)	
		return last;
	else if (first == last-1)	
		return first;
	else{
		mid = (last + first)/2;
		pivot = v[mid];
		v[mid] = v[first];
		v[first] = pivot;
		scanUp = first + 1;
		scanDown = last - 1;
		while(scanUp<scanDown)
		{
			while (scanUp <= scanDown && v[scanUp] <= pivot)
				scanUp++;
			while (scanUp <= scanDown && pivot <= v[scanDown])
				scanDown--;
			if (scanUp < scanDown){
				temp = v[scanUp];
				v[scanUp] = v[scanDown];
				v[scanDown] = temp;
			}
		}
		v[first] = v[scanDown];
		v[scanDown] = pivot;
		return scanDown;
	}
}
void quicksort(int *v, int first, int last){	
	int pivotLoc;
	int temp;
	if (last - first <= 1)
		return;
	else if (last - first == 2){
		if (v[last-1] < v[first]){
			temp = v[last-1];
			v[last-1] = v[first];
			v[first] = temp;
		}
		return;	
	}
	else{
		pivotLoc = pivotIndex(v, first, last);
		quicksort(v, first, pivotLoc);
		quicksort(v, pivotLoc +1, last);
	}
}
void Quick_Sort(int array[], int n,string s) {
	int first = 0, last = MAX-1;
	int a[MAX];
	memcpy(a, array, sizeof(a));
	time_t begin = clock();
	quicksort(a, first, last);
	time_t end = clock();
	cout<<s<<" cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
}

//归并排序
void merge(vector<int>& v, int first, int mid, int last){
	vector<int> tempVector;
	int indexA, indexB, indexV;
	indexA = first;
	indexB = mid;
	while (indexA < mid && indexB < last)
		if (v[indexA] < v[indexB]){	
			tempVector.push_back(v[indexA]);
			indexA++;
		}
		else{	
			tempVector.push_back(v[indexB]);
			indexB++;		
		}
	while (indexA < mid){
		tempVector.push_back(v[indexA]);
		indexA++;
	}
	while (indexB < last){
		tempVector.push_back(v[indexB]);
		indexB++;
	}
	indexA = first;
	for (indexV = 0; indexV < tempVector.size(); indexV++){
		v[indexA] = tempVector [indexV];
		indexA++;
	}
}
void mergesort(vector<int>& v, int first, int last){
	if (first + 1 < last){
		int midpt = (last + first) / 2;

		mergesort(v, first, midpt);
		mergesort(v, midpt, last);
		merge(v, first, midpt, last);
  	}
}
void Merge_Sort(int array[], int n,string s) {
	vector<int> v;
	v.clear();
	for (int i=0; i<MAX; i++)
		v.push_back(array[i]);
	time_t begin = clock();
	mergesort(v, 0, MAX-1);
	time_t end = clock();
	cout<<s<<" cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
}

//堆排序
void HeapAdjust(int *a,int i,int size){
    int lchild=2*i; 
    int rchild=2*i+1;
    int max=i;
    if(i<=size/2){
        if(lchild<=size&&a[lchild]>a[max])
            max=lchild;
        if(rchild<=size&&a[rchild]>a[max])
            max=rchild;
        if(max!=i){
            swap(a[i],a[max]);
            HeapAdjust(a,max,size);     
        }
    }        
}
void BuildHeap(int *a,int size)  {
    int i;
    for(i=size/2;i>=1;i--) 
        HeapAdjust(a,i,size);     
} 
void heapsort(int *a,int size)  {
    int i;
    BuildHeap(a,size);
    for(i=size;i>=1;i--){
        swap(a[1],a[i]);        
        HeapAdjust(a,1,i-1);  
    }
} 
void Heap_Sort(int array[], int n,string s) {
	int a[MAX];
	memcpy(a, array,sizeof(a));
	time_t begin = clock();
	heapsort(a,MAX);
	time_t end = clock();
	cout<<s<<" cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
}

//基数排序
void distribute(const vector<int>& v, queue<int> digitQueue[], int power){
	int i;
	for (i = 0; i < v.size(); i++)
		digitQueue[(v[i] / power) % 10].push(v[i]);
}
void collect(queue<int> digitQueue[], vector<int>& v){
	int i = 0, digit;
	for (digit = 0; digit < 10; digit++)
		while (!digitQueue[digit].empty())
		{
			v[i] = digitQueue[digit].front();
			digitQueue[digit].pop();
			i++;
		}
}
void radixSort(vector<int>& v, int d){
	int i;
	int power = 1;
	queue<int> digitQueue[10];

	for (i=0;i < d;i++){
		distribute(v, digitQueue, power);
		collect(digitQueue, v);
		power *= 10;
	}
}
void Radix_Sort(int array[], int n,string s) {
	time_t begin = clock();
	vector<int> v;
	v.clear();
	for (int i=0; i<MAX; i++)
		v.push_back(array[i]);
	radixSort(v, 10);
	time_t end = clock();
	cout<<s<<" cost time: "<<1000*(double)(end - begin)/CLOCKS_PER_SEC<<endl;
}
int main() {
	Generate_Number();
	cout<<"Selection Sort:"<<endl;
	Selection_Sort(Number_Asc_,MAX,"Ascending order");
	Selection_Sort(Number_Ran_,MAX,"Random order");
	Selection_Sort(Number_Des_,MAX,"Descending order");

	cout<<endl<<"Insertion Sort:"<<endl;
	
	Insertion_Sort(Number_Asc_,MAX,"Ascending order");
	Insertion_Sort(Number_Ran_,MAX,"Random order");
	Insertion_Sort(Number_Des_,MAX,"Descending order");

	cout<<endl<<"Bubble Sort:"<<endl;
	Bubble_Sort(Number_Asc_,MAX,"Ascending order");
	Bubble_Sort(Number_Ran_,MAX,"Random order");
	Bubble_Sort(Number_Des_,MAX,"Descending order");

	cout<<endl<<"Exchange Sort"<<endl;
	Exchange_Sort(Number_Asc_,MAX,"Ascending order");
	Exchange_Sort(Number_Ran_,MAX,"Random order");
	Exchange_Sort(Number_Des_,MAX,"Descending order");

	cout<<endl<<"Quick Sort"<<endl;
	Quick_Sort(Number_Asc_,MAX,"Ascending order");
	Quick_Sort(Number_Ran_,MAX,"Random order");
	Quick_Sort(Number_Des_,MAX,"Descending order");

	cout<<endl<<"Merge Sort"<<endl;
	Merge_Sort(Number_Asc_,MAX,"Ascending order");
	Merge_Sort(Number_Ran_,MAX,"Random order");
	Merge_Sort(Number_Des_,MAX,"Descending order");
	
    cout<<endl<<"Heap Sort"<<endl;
	Heap_Sort(Number_Asc_,MAX,"Ascending order");
	Heap_Sort(Number_Ran_,MAX,"Random order");
	Heap_Sort(Number_Des_,MAX,"Descending order");

	cout<<endl<<"Radix Sort"<<endl;
	Radix_Sort(Number_Asc_,MAX,"Ascending order");
	Radix_Sort(Number_Ran_,MAX,"Random order");
	Radix_Sort(Number_Des_,MAX,"Descending order");
}
