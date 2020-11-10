#pragma once
using namespace std;
class Calculator
{
private:
	string expression;
public:
	Calculator();
	Calculator(string);
	void setExpression(string);
	bool isExpressionBalanced();
	bool checkPrec(char opt1, char opt2);
	string infixToPostfix();
	int evaluatePostfix(string);
	void writePostfixToFile();
	void writeInfixToFile();
	bool checkBalancedFromFile();
	void convertAndWriteToFile();
	void evaluatePostfixFromFile();
};