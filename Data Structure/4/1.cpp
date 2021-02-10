#include <bits/stdc++.h>
using namespace std;
class tnode {
	private:
		int data;
		tnode *right;
		tnode *left;
	public:
		friend class BST;
		tnode(int d, tnode *l = NULL, tnode *r = NULL):data(d),left(l),right(r) {};
};

class BST {
	public:
		tnode *root;
		BST() {
			tnode *p3, *p8, *p24, *p60, *p91, *p37, *p58, *p5, *p20, *p15, *p62;
			p3 = new tnode(3);
			p8 = new tnode(8);
			p24 = new tnode(24);
			p60 = new tnode(60);
			p91 = new tnode(91);
			p37 = new tnode(37, p24, (tnode *)NULL);
			p58 = new tnode(58, (tnode *)NULL, p60);
			p5 = new tnode(5, p3, p8);
			p20 = new tnode(20, (tnode *)NULL, p37);
			p15 = new tnode(15, p5, p20);
			p62 = new tnode(62, p58, p91);
			root = new tnode(50, p15, p62);
		}		
		void displayPreOrder(tnode *troot) {
			if (troot != NULL) {
				cout << left << setw(14) << troot->data;
				if (troot->left)
					cout << left << setw(16) << troot->left->data;
				else
					cout << left << setw(16) << '-';
				if (troot->right)
					cout << troot->right->data<<'\n';
				else
					cout << "-\n";
				displayPreOrder(troot->left);
				displayPreOrder(troot->right);
			}
		}
};

int main() {
	BST b;
	cout << "\Node.data     Lchild.data     Rchild.data\n";
	cout << "=========     ===========     ===========\n";
	b.displayPreOrder(b.root);
}
