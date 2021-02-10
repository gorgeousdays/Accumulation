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

//�������пյ�ʵ�� 
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

//��ջ����λ�����ַ����ַ������ 
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

//��empyt2���ж�ջ���Ƿ��������� 
bool Change_Stack::empty2() const{
	if (count == 0)
		return 1;
	return 0;
}
//����������������򷵻�����һ�� 
string Change_Stack::top2(){
	if (!empty2()){
		return StackString[count-1];
	}
}
//ջ��ָ�����ƣ���һ��Ԫ�ر�pop 
void Change_Stack::pop(){
	if (!empty()){
		count -= 1;
	}
}
//����ջ��Ԫ�ظ��� 
int Change_Stack::size(){
	return count+1;
}

string suffix_to_infix(string expression){
	char element;
	Change_Stack S;
	bool flag = 1;//flag�ж��Ƿ���� flag=0ΪError 
	int i = 0;
	while(flag && i<expression.length()){
		element= expression[i];
		//����Ǳ�������ջ 
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
						flag = 0;//���Ҫһ�������� ����ջ��û���������ϲ������򱨴� 
					}
					break;
				default  :	flag = 0;
			}
		}
		i++;
	}
	if (S.size()==1 && flag){//���ջ��ֻ��һ��Ԫ�� �����޴�����Ϣ�����ջ��Ԫ�أ����� 
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


