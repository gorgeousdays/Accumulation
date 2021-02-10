#include<iostream>
#include<string>
using namespace std;
 
const int SIZE = 100;
class Change_Stack{
	public:
 		Change_Stack(){count = -1;}
		bool full()	const;
		bool empty() const;
		void push(char sTemp);
		void push(string sTemp);
		string top();
		bool empty2() const;
		string top2();
		void pop();
		int size();
	private:
		string StackString[SIZE];
		int count;
};

//判满与判空的实现 
bool Change_Stack::full() const{
	if (count == SIZE-1){
		cout<<"Error!Full!"<<endl;
	 	return 1;
	}	
	return 0;
}
bool Change_Stack::empty()	const{
	if (count == -1){
		cout<<"Error!Empty!"<<endl;
		return 1;
	}
	return 0;
}

//入栈考虑位单个字符和字符串情况 
void Change_Stack::push(char s){
	if (!full()){
 		count += 1;
 		StackString[count] = s;
	}	
}
void Change_Stack::push(string s){
	if (!full()){
 		count += 1;
 		StackString[count] = s;
	}	
}

//Function: Show the top element in the stack.
string Change_Stack::top(){
	if (!empty())
		return StackString[count];
}

//以empyt2来判断栈中是否有两个数 
bool Change_Stack::empty2() const{
	if (count == 0)
		return 1;
	return 0;
}
//如果存在两个数，则返回再下一个 
string Change_Stack::top2(){
	if (!empty2()){
		return StackString[count-1];
	}
}
//栈顶指针下移，即一个元素被pop 
void Change_Stack::pop(){
	if (!empty()){
		count -= 1;
	}
}
//返回栈中元素个数 
int Change_Stack::size(){
	return count+1;
}

string suffix_to_infix(string expression){
	char element;
	Change_Stack S;
	bool flag = 1;//flag判断是否出错 flag=0为Error 
	int i = 0;
	while(flag && i<expression.length()){
		element= expression[i];
		//如果是变量则入栈 
		if ((element>='A'&&element<='Z') || (element>='a'&&element<='z'))
			S.push(element);
		else{
			switch(element){
				case ' ' : 	break;
				case '+' :
				case '-' :
				case '*' :
				case '/' :
				case '%' :	
				    if (!S.empty2()){
						string temp = '(' + S.top2() + element + S.top() + ')';
						S.pop();
						S.pop();
						S.push(temp);
					}
					else{
						flag = 0;//如果要一个操作符 但是栈中没有两个以上操作数则报错 
					}
					break;
				default  :	flag = 0;
			}
		}
		i++;
	}
	if (S.size()==1 && flag){//如果栈中只有一个元素 并且无错误信息则输出栈顶元素，即答案 
		return S.top();
	}
	else
		return "Error!Wrong Input";
}


int main(){
 	string expression;
	cout<<"You can enter '#' to exit\n";
	while(true){
		cout<<"\nPlease enter the suffix expression"<<endl; 
		getline(cin, expression);
		if (expression == "#")
			break;		
		cout<<"The infix expression is: "<<suffix_to_infix(expression)<<endl;
	}
	return 0;
}


