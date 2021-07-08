#include<iostream>
using namespace std;
#define N 6 
int* binarySearch(int a[], int left, int right,int x) {
	int b[2];
	int middle;
	while ( left <= right ) {
		middle = (left + right)/2;
		if (x == a[middle]) {
			b[0]=middle;
			b[1]=middle;
			return b;
		}
		if (x > a[middle]) left = middle + 1;
		else right = middle -1;
	}
	if(left==0) b[0]=-1;
	else b[0] = left;
	b[1]=right;
	return b;
}
int search(int a[]){
	for(int i=0;i<N;i++){
		int *p=binarySearch(a,0,N,i);
		if(p[0]==i)
		    return i;
	}
	return -1;
}
int main() {
	int a[]= {1,1,2,78,90,100};
	cout<<search(a);
}
