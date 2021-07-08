#include<iostream>
using namespace std;
int res=0;
void search(int flower,int shop,int wine,int flag){//flag=1Óö»¨£¬flag=0±íÊ¾Óö¾Æ 
	if(flower==0&&shop==0){
	    if(wine==0&&flag==1){
	    	res++;
		}
		return;  
	} 
	if(shop>0)
	    search(flower,shop-1,wine*2,0);
	if(flower>0){
		search(flower-1,shop,wine-1,1);
	}
}
int main(){
	search(10,5,2,-1);
	cout<<res;
} 
