#include<bits/stdc++.h>
using namespace std;
//实现中缀转后缀
string infix_to_suffix(string infix_expression) {
	char element, topelement;
	stack<int> opStack;
	string suffix_expression;
	for (int i=0; i<infix_expression.length(); i++) {
		element = infix_expression[i];
		switch(element) {
			case ' ' :
				break;
			case '(' :
				opStack.push(element);
				break;
			case ')' :
				//对于为右括号的情况，则将栈中左括号前运算符出栈 
				while(true) {
					topelement = opStack.top();
					opStack.pop();
					if (topelement == '(')
						break;
					suffix_expression.append(1,topelement);
				}
				break;
			case '+' :
			case '-' :
			case '*' :
			case '/' :
			case '%' :
				//在遇到运算符 依据优先级则入栈出栈 
				while(true) {
					if (opStack.empty() ||opStack.top() == '(' ||(element=='*' || element=='/' || element=='&') &&(opStack.top()=='+' || opStack.top()=='-')) {
						opStack.push(element);
						break;
					} else {
						topelement = opStack.top();
						opStack.pop();
						suffix_expression.append(1,topelement);
					}
				}
				break;
			default :
				//在遇到数字 则直接连上，.则考虑了小数点的情况 
				suffix_expression.append(1,element);
				while(true) {
					if (infix_expression[i+1]!='.' && !isalnum(infix_expression[i+1]))
						break;
					i++;
					element = infix_expression[i];
					suffix_expression.append(1, element);
				}
		}
	}
	//最后将符栈中剩余的符号入栈 
	while(true) {
		if (opStack.empty())
			break;
		topelement = opStack.top();
		opStack.pop();
		if (topelement != '(')
			suffix_expression.append(1,topelement);
		else {
			return "Error!Wrong Input!";
		}
	}
	return suffix_expression;
}

struct tnode {
	int value;
	tnode *left,*right;
	int level = 0;
	int column = 10;
	tnode(int x,tnode *tleft=NULL,tnode *tright=NULL):value(x), left(tleft), right(tright) {}
};

class tree {
	private:
		stack<tnode*> numStack;
		tnode *root=NULL;
		//draw为画图区域  开始置为空区域 
		char draw[100][100]={" "}; 
		int max_level=0;
		int max_column=0;
		int min_column=1e9;
	public:
		bool IsOperator(char s){
			return s == '+' || s == '-' || s == '*' || s == '/' || s=='%'||s == '(' || s == ')';
		}
		void creat(string infix_expression);
		void position(tnode* root);
		tnode *theroot() {
			return root;
		}
		void define_position(tnode* root);
		void print_the_tree() {
			for (int j = 0; j <= max_level; j++) {
				for (int i =min_column; i <= max_column; i++) {
					cout << draw[j][i];
				}
				cout << endl;
			}
		}
		void  display(tnode *root); 
};

//创建表达式二叉树 
void tree::creat(string infix_expression) {
	string suffix_expression = infix_to_suffix(infix_expression);//先将中缀表达式转后缀表达式 
	for (int i = 0; i < suffix_expression.length(); i++) {
		tnode* father = NULL;
		tnode *left = NULL;
		tnode *right = NULL;
		if (IsOperator(suffix_expression[i])){//如果遇到运算符，则以栈中第一个元素为右子树 第二个元素为左子树 
			right = numStack.top();
			numStack.pop();
			left = numStack.top();
			numStack.pop();
		}
		father = new tnode(suffix_expression[i], left, right);
		numStack.push(father);
	}
	root = numStack.top();
}
//确定每个点的level和column 
void tree::define_position(tnode* root) {
	if (root != NULL) {
		if (root->left){
			root->left->level = root->level + 1;
			if (2*root->left->level >max_level)max_level = 2*root->left->level;
			root->left->column = root->column - (5 - root->left->level);
			if (min_column> 2*root->left->column) min_column = 2*root->left->column;
		}
		define_position(root->left);
		if (root->right) {
			if (2*root->right->level >max_level)max_level = 2*root->right->level;
			root->right->level = root->level + 1;
			root->right->column = root->column + (5 - root->right->level);
			if (max_column < 2*root->right->column) max_column = 2*root->right->column;
		}
		define_position(root->right);
	}
}
//确定各点对应的value 
void tree::position(tnode* root) {
	if (root != NULL) {
		position(root->left);
		draw[root->level][2*root->column] = root->value;
	    position(root->right);
	}
}

void tree::display(tnode *root){
	define_position(root);
	position(root);
	print_the_tree();
}

int main() { 
	string postfix(string);
	string infix_expression;
	cout<<"\nPlease enter the infix expression"<<endl;
	getline(cin, infix_expression);
	cout<<"The suffix expression is\n"<<infix_to_suffix(infix_expression)<<endl;
	tree expression_tree;
	//根据后缀表达式创建表达式二叉树 
	expression_tree.creat(infix_expression);
    //输出对应的表达式二叉树 
	expression_tree.display(expression_tree.theroot());
}

