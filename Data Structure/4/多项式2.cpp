#include<bits/stdc++.h>
#include<list>
using namespace std;
struct term {
	double ratio;
	int index;
};
int main() {
	int len[2];
	list <term> l[2],list3;
	for(int i=0; i<=1; i++) {
		cout<<"请输入第"<<i+1<<"个多项式的项数"<<endl;
		cin>>len[i];
		cout<<"请输入多项式:"<<endl;
		for(int j=0; j<len[i]; j++) {
			term p;
			cin>>p.ratio>>p.index;
			l[i].push_back(p);
		}
	}
	list<term>::iterator it[2],it3;
	for(it[0]=l[0].begin(),it[1]=l[1].begin(); it[0]!=l[0].end(),it[1]!=l[1].end();) {
		if((*it[0]).index>(*it[1]).index) {
			list3.push_back(*it[0]);
			it[0]++;
		} else if((*it[0]).index<(*it[1]).index) {
			list3.push_back(*it[1]);
			it[1]++;
		} else {
			term p;
			p.ratio=(*it[0]).ratio+(*it[1]).ratio;
			p.index=(*it[0]).index;
			list3.push_back(p);
			it[0]++;
			it[1]++;
		}
	}
	for(int i=0; i<=1; i++) {
		if(it[i]!=l[i].end()){
			for(; it[i]!=l[i].end(); it[i]++) {
				list3.push_back(*it[i]);
			}
		}
	}
	for(it3=list3.begin(); it3!=list3.end(); it3++) {
		if(it3!=list3.begin())
			cout<<"+";
		cout<<"("<<(*it3).ratio<<")"<<"x^"<<(*it3).index;
	}
}
