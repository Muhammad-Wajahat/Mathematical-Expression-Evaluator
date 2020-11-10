#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#include"Calculator.h"

void menu();
int main()
{
	menu();
	return 0;
}

void menu() {
	char choice;
	Calculator calc;
	string postfix;
	string expression;
	cout << "WELCOME" << endl;
	cout << "This program is to evaluate Arithematic Expressions" << endl;
	cout << "The following Operators are supported: +,-,*,/,%,^" << endl;
	cout << "Only numbers 0 to 9 are supported." << endl;
	cout << "\"9+2\" is valid and will generate correct result" << endl;
	cout << "\"11+2\" is not valid and will not generate correct result" << endl;
	system("pause");
	system("cls");
	while (1)
	{
		cout << "Enter 1 to Write a Infix Expression to a File" << endl;
		cout << "Enter 2 to Read an Infix Expression from a file and check its validity" << endl;
		cout << "Enter 3 to read an Infix Expression from a file and convert it to an Postfix Notation" << endl;
		cout << "Enter 4 to read an Postfix Expression from a file and evaluate it" << endl;
		cout << "Enter q or Q to exit the program" << endl;
		cout << ">>";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case '1':
		{
			cout << "Enter your Infix expression: ";
			getline(cin, expression);
			calc.setExpression(expression);
			cout << "The expression is: " << expression << endl;
			calc.writeInfixToFile();
			break;
		}
		case'2':
		{
			if (calc.checkBalancedFromFile()) {
				cout << "The expression is Balanced" << endl;
			}
			else {
				cout << "the expression is not balanced." << endl;
			}
			break;
		}
		case'3':
		{
			calc.convertAndWriteToFile();
			break;
		}
		case'4':
		{
			calc.evaluatePostfixFromFile();
			break;
		}
		case'q':
		case'Q':
			cout << "You have exited" << endl;
			exit(0);
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}
