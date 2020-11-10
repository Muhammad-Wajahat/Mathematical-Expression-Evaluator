#include<iostream>
#include<math.h>
#include<string>
#include<fstream>
#include"Stack.h"
#include"Calculator.h"
using namespace std;

//constructor initializes an empty string
Calculator::Calculator() {
	expression = "";
}

//parameterised consructor initializes the string with a value
Calculator::Calculator(string exp) {
	expression = exp;
}

//setter function to set the value of the expression from the user
void Calculator::setExpression(string expre) {
	expression = expre;
}

//checking to see if the equation is correctly balanced
//returns true if the equation is correctly balanced
//returns false if the equation is not correctly balanced
bool Calculator::isExpressionBalanced() {
	Stack<char> stk;
	//using for loop to go through the expression
	for (int i = 0; i < expression.length(); i++)
	{
		//if '(' is encountered
		//it is pushed on to the stack
		if (expression[i] == '(')
		{
			stk.push(expression[i]);
		}
		//if at any point there is "Stack Underflow"
		//return false
		else if (expression[i] == ')')
		{
			if (stk.pop() == NULL)
			{
				return false;
			}
		}
	}
	//when for loop terminates if stack is empty return true;
	//else return false;
	if (stk.isEmpty()) {
		return true;
	}
	else {
		return false;
	}
}


//utility function to check the precedence of two
bool Calculator::checkPrec(char opt1, char opt2) {

	//if '(' is encountered then we return false
	//since in this case we only want push operator on to the stack
	if (opt1 == '(') {
		return false;
	}
	//using an enum to set level of precidence
	//the higher the level the higher the value assossiated with it
	enum operatorPrec
	{
		lvl1 = 1,
		lvl2 = 2,
		lvl3 = 3
	};
	operatorPrec oper1;
	operatorPrec oper2;
	//depending on the operator the level is assigned using switch
	//for first operator (TOS)
	switch (opt1)
	{
	case '+':
	case '-':
	{
		oper1 = lvl1;
		break;
	}
	case '*':
	case '/':
	case '%':
	{
		oper1 = lvl2;
		break;
	}
	case '^':
	{
		oper1 = lvl3;
		break;
	}
	}

	//checking level for 2nd operator
	//new operator to be added to stack
	switch (opt2)
	{
	case '+':
	case '-':
	{
		oper2 = lvl1;
		break;
	}
	case '*':
	case '/':
	case '%':
	{
		oper2 = lvl2;
		break;
	}
	case '^':
	{
		oper2 = lvl3;
		break;
	}
	}
	//if operator at TOS is greater return true
	if (oper1 >= oper2) {
		return true;
	}
	//else return false
	else
	{
		return false;
	}
}

//function to convert a infix Expression to Postfix
//function will return a postfix expression string
string Calculator::infixToPostfix() {
	string postFix;
	Stack<char> stk;
	int i = 0;
	//going through the expression
	while (i < expression.length())
	{
		//storing the expression for ease of use
		char symbol = expression[i];
		//if to ignore spaces in the expression
		if (symbol == ' ') {
			i++;
			continue;
		}
		//if the character is a operand it is inserted to postfix string
		if (symbol >= '0' && symbol <= '9') {
			postFix += symbol;
		}
		//if the character is '(' then it is pushed on to the stack
		else if (symbol == '(') {
			stk.push(symbol);
		}
		//if the character is ')'
		//all values in the stack are popped
		//inserted into postfix string
		//until ')' is occured
		else if (symbol == ')') {
			while (stk.getTop() != '(')
			{
				char topSymbol = stk.pop();
				postFix += topSymbol;
			}
			stk.pop();
		}
		//if character is an operator
		//then if the precedence of the operator at TOS is greater
		//all the values in the stack are popped and inserted into postfix string
		//then the character is pushed on to the stack
		else {
			while (!stk.isEmpty() && checkPrec(stk.getTop(), symbol))
			{
				char topSym = stk.pop();
				postFix += topSym;
			}
			stk.push(symbol);
		}
		i++;
	}
	//when while loop terminates all the items in the stack
	//are popped and inserted to the postfix string
	while (!stk.isEmpty()) {
		postFix += stk.pop();
	}
	return postFix;
}

//function evaluates the postfix expression string
//return the result of the solution of the expression
//operands are pushed on to the stack
//until an operator is occured then top two operators are popped
//then their result is pushed back on the stack
//at the end the value at TOS is the result and it is returned
int Calculator::evaluatePostfix(string postFix)
{
	Stack<int> s;
	int x, y, temp;
	for (int i = 0; i < postFix.length(); i++)
	{
		if (postFix[i] >= '0' && postFix[i] <= '9')
			s.push((int)postFix[i] - '0');
		else {
			x = s.pop(); y = s.pop();
			switch (postFix[i])
			{
			case'+':
				temp = y + x;
				break;
			case'-':
				temp = y - x;
				break;
			case'*':
				temp = y * x;
				break;
			case'/':
				if (x == 0) {
					cout << "Divide by Zero is not possible" << endl;
					return 0;
				}
				temp = y / x;
				break;
			case'%':
				temp = y % x;
				break;
			case'^':
				temp = pow(y, x);
				break;
			}
			s.push(temp);
		}
	}
	return s.pop();
}

void Calculator::writePostfixToFile() {
	fstream file;
	file.open("postfix Expression.txt", ios::out);
	cout << "Postfix Expression: " << infixToPostfix() << " Written to File" << endl;
	file << infixToPostfix() << endl;
	file.close();
}
void Calculator::writeInfixToFile() {
	fstream file;
	file.open("infix Expression.txt", ios::out);
	cout << "Infix Expression: " << expression << " Written to File" << endl;
	file << expression << endl;
	file.close();
}
bool Calculator::checkBalancedFromFile() {
	fstream file;
	file.open("infix Expression.txt", ios::in);
	getline(file, expression);
	file.close();
	cout << "Expression is: " << expression << endl;
	return isExpressionBalanced();
}

//checks infix expression from file
//if expression is valid
//converts the expression to postfix and writes it to file
//otherwise deletes the file postfix file
void Calculator::convertAndWriteToFile() {
	fstream infixFile, postfixFile;
	infixFile.open("infix Expression.txt");
	getline(infixFile, expression);
	infixFile.close();
	if (checkBalancedFromFile()) {
		writePostfixToFile();
	}
	else {
		cout << "The expression was not balanced. Did not Write to File" << endl;
		cout << "Please write a new Expression." << endl;
		remove("postfix Expression.txt");
	}
}

//functions gets expression from postfix file
//then evaluates it
//if the there is no postfix expression file then tells user
void Calculator::evaluatePostfixFromFile() {
	fstream infixFile, postfixFile;
	infixFile.open("infix Expression.txt");
	getline(infixFile, expression);
	cout << "The Infix Expression is:" << expression << endl;
	postfixFile.open("postfix Expression.txt", ios::in);
	if (postfixFile.good()) {
		getline(postfixFile, expression);
		cout << "The postfix Expression is: " << expression << endl;
		cout << "The Result is: " << evaluatePostfix(expression) << endl;
	}
	else {
		cout << "No Postfix Expression written.\n Please write a valid Infix notation and convert it into postfix first" << endl;
	}
}
