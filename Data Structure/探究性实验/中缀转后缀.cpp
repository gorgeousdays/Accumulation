//Infix expression converse to postfix expression. 
//Created by Yule, Nov_10_2015
//==============================================================================
#include<iostream>
#include<string>
#include<cassert>
#include<cctype>
#include<stack>
using namespace std;

// Function to operate the original infix expression to postfix expression.
// Parameter: infix expression. Output: postfix expression. 
string postfix(string exp)
{
	char token, topToken;
	stack<int> opStack;			// Create a stack to store the sign.
	string postfixExp;
	const string BLANK = " ";
	
	// deal every character by order
	for (int i=0; i<exp.length(); i++){
		token = exp[i];
		// Switch the sign, decide wether go to the stack.
		switch(token)
		{
			// token is blank, ignore this.
			case ' ' : 	break;
			
			// token is '('
			// Push it into the stack unconditionally. 
			case '(' : 	opStack.push(token);
						break;
			
			// token is ')'
			// Judge wether there exist any sign in the stack initially,
			// If the stack include some signs, pop out the signs continuously
			// until meet a '('. Pop out this '(' without displaying it.
			// If topToken didn't meet a '(' until the stack was empty, 
			// there must be a error.It will be discussed at the back. 
			case ')' :  for (;;){
							assert(!opStack.empty());
							topToken = opStack.top();
							opStack.pop();
							if (topToken == '(')
								break;
							postfixExp.append(BLANK + topToken);
						}
						break;
						
			// token is '*', '/', '+' or '-'
		 	// If the stack is empty, or the token has a higher priority than
		 	// the top sign in the stack, push this token to the stack.
		 	// If not, display the sign in the stack until fit the assumption.
			case '+' :
			case '-' :
			case '*' :
			case '/' :
			case '%' :  for (;;){
							if (opStack.empty() ||
								opStack.top() == '(' ||
								// '*' and '/' have higher priority than '+' and '-'.
								(token=='*' || token=='/' || token=='&') &&
								(opStack.top()=='+' || opStack.top()=='-')){
									opStack.push(token);
									break;
								}
							else{
								topToken = opStack.top();
								opStack.pop();
								postfixExp.append(BLANK + topToken);
							}	
						}
						break;
			
			// If token is not fit to conditions ahead, it must be a number.
	  		// Append the number to the output string.  
			default  :  postfixExp.append(BLANK + token);
						for (;;){
							//**********************************************************************************
							// In the task require, this number may be a floating point number,
							// so except the digit, character'.' should also include in the judgement sentence.
							// It prevents the blank appear in front of the '.'.
							//**********************************************************************************
							if (exp[i+1]!='.' && !isalnum(exp[i+1]))
								break;
							i++;
							token = exp[i];
							postfixExp.append(1, token);
						}
		}
	}
	// Judge wether there exists any sign in the stack.
	for (;;){
		if (opStack.empty())	// If there is no sign in the stack, get out.
			break;

		topToken = opStack.top();
		opStack.pop();
		// If the left sign is '(', the original expression must have some mistakes,
		// for '(' and ')' must appear in pairs.
		if (topToken != '(')	
			postfixExp.append(BLANK + topToken);
		else{
			cout<<"*** Error in the infix expression. ***\n";
			return "ERROR! CHECK THE INPUT EXPREESION AGAIN!";
		}
	}	
	return postfixExp;
}


int main()
{
	string postfix(string);
	string infixExp;
	cout<<"NOTE: Enter # for infix expression to stop.\n";
	for (;;){
		cout<<"\nInfix expression? "<<endl;
		getline(cin, infixExp);
		if (infixExp == "#")		// Use '#' as the mark of exit.
			break;	
		cout<<"Postfix expression is "<<postfix(infixExp)<<endl;
	}	
	return 0;
}

