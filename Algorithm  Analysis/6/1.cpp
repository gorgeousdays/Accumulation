#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;
typedef char ElemType;
class node {
	public:
		int w;
		int flag;
		ElemType c;
		node *plink,*llink,*rlink;
		vector<char> code;
		node() {
			plink=NULL;
			llink=NULL;
			rlink=NULL;
			flag=0;
		}
};

struct op {
	bool operator()(node* a,node* b) {
		return a->w>b->w;
	}
};

int n;
node *nums[100], *root;
map<char,string> m;
void SetTree() {
	cout<<"�������ַ�����С:";
	cin>>n;
	for(int i=0; i<n; i++) {
		nums[i]=new node;
	}
	cout<<"�������ַ��Լ���Ӧ��Ȩֵ:";
	for(int i=0; i<n; i++) {
		cin>>nums[i]->c>>nums[i]->w;
		nums[i]->flag=1;
		m[nums[i]->c]="";
	}
	priority_queue<node*,vector<node*>,op>pq;
	for(int i=0; i<n; i++) {
		pq.push(nums[i]);
	}
	while(!pq.empty()) {
		node* a=pq.top();
		pq.pop();
		if(pq.empty()) {
			root=a;
			return;
		}
		node* b=pq.top();
		pq.pop();
		node* newnode=new node;
		a->plink=newnode;
		b->plink=newnode;
		newnode->llink=a;
		newnode->rlink=b;
		newnode->w=a->w+b->w;
		pq.push(newnode);
	}
}

void coding(node *root) {
	node *temp=root;
	if(temp==NULL) {
		return;
	}
	if(temp->llink) {
		temp->llink->code=temp->code;
		temp->llink->code.push_back('0');
		coding(temp->llink);
	}
	if(temp->rlink) {
		temp->rlink->code=temp->code;
		temp->rlink->code.push_back('1');
		coding(temp->rlink);
	}
}
void printcode(node *root) {
	for(int i=0; i<n; i++) {
		cout<<nums[i]->c<<":";
		for(int j=0; j<nums[i]->code.size(); j++) {
			cout<<nums[i]->code[j];
			m[nums[i]->c]=m[nums[i]->c]+nums[i]->code[j];
		}
		cout<<endl;
	}
}
string EnCode(string s) {
	string ans;
	for(int i=0; i<s.length(); i++)
		ans+=m[s[i]];
	return ans;
}
string DeCode(string s) {
	string temp,ans;
	for(int i=0; i<s.length(); i++) {
		temp=temp+s[i];
		for(int j=0; j<n; j++) {
			if(m[nums[j]->c]==temp) {
				ans+=nums[j]->c;
				temp="";
			}
		}
	}
	return ans;
}
int main() {
	SetTree();
	cout<<"Coding...\n";
	coding(root);
	printcode(root);
	string test;
	bool F=1;
	int choose;
	while(F) {
	    cout<<"1:���� 2������ 0:�˳�\n";
		cin>>choose;
		switch(choose) {
			case 1:
				cout<<"������Ҫ���ܵ��ַ�����";
				cin>>test;
				cout<<"Encoding..."<<EnCode(test)<<"\n";
				break;
			case 2:
				cout<<"������Ҫ���ܵ��ַ�����";
				cin>>test;
				cout<<"Decoding..."<<DeCode(test)<<"\n";
				break;
			case 0:
				F=0;
				break;
		}
	}
}
