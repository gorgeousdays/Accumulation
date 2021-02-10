#include<iostream>
#include<queue>
using namespace std;
char a[10][25]= {' '};//定义画板大小，用于打印三叉树 
int maxlevel=0;
int maxcolumn=1;
struct tnode {
	int value;
	tnode *left,*right,*mid;
	int level = 1;
	int column = 15;
	tnode(int x,tnode *tleft=NULL,tnode *tmid=NULL,tnode *tright=NULL):value(x), left(tleft),mid(tmid), right(tright) {
	}
};
void PreOrder(tnode* node) { //前序遍历
	cout << node->value << " ";
	if (node->left != NULL) PreOrder(node->left);
	if (node->mid != NULL) PreOrder(node->mid);
	if (node->right != NULL) PreOrder(node->right);
	return;

}
void MidOrder(tnode* node) { //中序遍历
	if (node->left != NULL) MidOrder(node->left);
	cout << node->value << " ";
	if (node->mid != NULL) MidOrder(node->mid);
	if (node->right != NULL) MidOrder(node->right);
	return;
}
void PostOrder(tnode* node) { //后序遍历
	if (node->left != NULL) PostOrder(node->left);
	if (node->mid != NULL) PostOrder(node->mid);
	if (node->right != NULL) PostOrder(node->right);
	cout << node->value << " ";
	return;
}
void LevelOrder(tnode* node){  //层次遍历 
	queue <tnode*> q;
    q.push(node);
    while(!q.empty()){
        if(q.front()->left!=NULL)   q.push(q.front()->left);
        if(q.front()->mid!=NULL)   q.push(q.front()->mid);
        if(q.front()->right!=NULL)   q.push(q.front()->right);
        cout<<q.front()->value<<" ";
        q.pop();
    }
    cout<<endl;
}
void deeping(tnode* node) {//通过递归确定各个点的位置信息 
	if(node->left!=NULL) {
		node->left->level=node->level+1;
		if(node->left->level>maxlevel) maxlevel=node->left->level; 
		node->left->column=node->column-(5-node->left->level);
		deeping(node->left);
	}
	if(node->mid!=NULL) {
		node->mid->level=node->level+1;
		if(node->mid->level>maxlevel) maxlevel=node->mid->level; 
		node->mid->column=node->column;
		deeping(node->mid);
	}
	if(node->right!=NULL) {
		node->right->level=node->level+1;
		if(node->right->level>maxlevel) maxlevel=node->right->level; 
		node->right->column=node->column+(5-node->right->level); 
		deeping(node->right);
	}
}
void print_before(tnode* node) { //打印三叉树之前将各个点的位置信息置与画板上 
	a[node->level][node->column]=char(node->value+48);
	if(node->left!=NULL) print_before(node->left);
	if(node->mid!=NULL) print_before(node->mid);
	if(node->right!=NULL) print_before(node->right);
}
void print_tree(tnode *node) {
	deeping(node); 
	print_before(node);
	for(int i=0; i<=maxlevel; i++) {
		for(int j=0; j<=25; j++)
			cout<<a[i][j];
		cout<<endl;
	}
}
int main() {
	tnode *t6=new tnode(6);
	tnode *t7=new tnode(7,t6);
	tnode *t8=new tnode(8);
	tnode *t3=new tnode(3,t7,t8);
	tnode *t4=new tnode(4);
	tnode *t9=new tnode(9);
	tnode *t5=new tnode(5,NULL,NULL,t9);
	tnode *root=new tnode(1,t3,t4,t5);
	cout<<"前序遍历:";
	PreOrder(root);
	cout<<endl;
	cout<<"中序遍历:";
	MidOrder(root);
	cout<<endl;
	cout<<"后序遍历:";
	PostOrder(root);
	cout<<endl;
	cout<<"层次遍历:";
	LevelOrder(root); 
    print_tree(root);
	delete t3,t4,t5,t6,t7,t8,t9,root;
}
