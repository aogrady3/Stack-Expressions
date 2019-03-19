/**
 * @file Stack_Expressions.cpp
 * \mainpage
 *
 * Recognizing Infix Arithmetic Expressions
 *
 * A C++ program that uses stack, to read an expression from standard input,
 * computes the value of that expression and prints the value.
 *
 * @author Andrew O'Grady
 * @date   4/3/18
 */

/*
 * includes
 */
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/**
 * Using integer arithemtic.
 * To generalize use <code>typedef</code>
 */
using ValueType = int;


/** @class IllegalExprException
 *  Exception class thrown by illegal postfix expression
 */
class IllegalExprException : public exception { };

/**
 * Determine the value of an infix expression
 *
 * @param expr a string, supposedly representing an infix expression
 * @return the value of <code>expr</code>
 * @throw IllegalExprException if <code>expr</code> is not a legal infix
 * expression
 */
ValueType processExpression(const string& expr) throw (IllegalExprException);

/**
 * Determine the precedence of an operator
 *
 * @param op the operator
 * @pre <code>op</code> is +,-, *, /
 * @return precedence of operation
 *
 */
int precedence(char op);

/**
*
* Gives user help if needed.
*
**/
void provideHelpIfNecessary(void);

/**
*
* Do binary operation using a vector of postfix
* @param postfix expression from infix
* @param post stack to use while executing the postfix
* @post all binary operations applied
*/
void execute(stack<ValueType>& valstack, stack<char>& opStack)
    throw (IllegalExprException);


/**
*
* @param left to the left operand
* @param operation to be preformed
* @param the right operand
* @throw IllegalExprExpxception when illegal post expression
* @return the result of the operation
**/

ValueType doOperation(ValueType operandL, char operation, ValueType operandR)
    throw (IllegalExprException);

/**
 * The usual main function
 */
int main(void)
{
    provideHelpIfNecessary();

    while (true) {
	cout << "Expression? " ;
	string expr;                    // holds the supposed expression
	getline(cin, expr);
	if (expr.length() == 0)
	    break;
	try {
	    ValueType result = processExpression(expr);
	    cout << result << endl;
	} catch (exception& ex) {
	    cerr << ex.what() << endl;
	}
    } // end while
    cout << endl;
} // end main

void provideHelpIfNecessary(void)
{

    cout << "Do you need help (Y/N)? ";
    string help;
    cin >> help;
    if (help == "Y" || help == "y") {
	cout << "Please enter an infix expression. " << endl
	     << "This program will then tell you the new value. " << endl
	     << "To stop the program, just hit \"return\" "
	     << "after the prompt." << endl;
        cin.ignore();
    }
    else if (help == "N" || help == "n") {
        cin.ignore();
	return;
    }
    else {
	cout << "Response must be either either \"Y\" or \"N\"." << endl;
	provideHelpIfNecessary();
    }
} // end provideHelpIfNecessary

ValueType processExpression(const string& expr) throw (IllegalExprException)
{
    stack<ValueType> ValStack;
    stack<char> OpStack;
for (unsigned int i = 0; i < expr.length(); i++) {
    if (isdigit(expr[i])){
        ValueType num = expr[i] - '0';
        ValStack.push(num);
}
    else if (expr[i] == '(')
        OpStack.push(expr[i]);
    else if (expr[i] == '*'|| expr[i] == '+'|| expr[i] == '-'|| expr[i] == '/')
{
    if(OpStack.empty())
        OpStack.push(expr[i]);
    else if (precedence(expr[i]) > precedence(OpStack.top()))
        OpStack.push(expr[i]);
    else
{
    while (!OpStack.empty() && precedence(expr[i]) <= precedence(OpStack.top()) && OpStack.top() != '(') //condition for checking '(' added
        execute(ValStack,OpStack);
        OpStack.push(expr[i]);
}
}
    else if (expr[i] == ')') {
    while (OpStack.top() != '(')
        execute(ValStack,OpStack);
        OpStack.pop();
}
}
    while (!OpStack.empty())
        execute(ValStack,OpStack);
        ValueType result = ValStack.top();
        return result;
}  // end processExpression

int precedence(char op)
{
switch(op)
{
    case '+':
        return 1;
	case '-':
	    return 1;
	case '*':
	    return 2;
	case '/':
	    return 2;
	default:
	    return 0;
}
} // end precedence

void execute(stack<ValueType>& valStack, stack<char>& opStack)
    throw (IllegalExprException)
{
    ValueType right = valStack.top();
    valStack.pop();
    ValueType left = valStack.top();
    valStack.pop();
    valStack.push(doOperation(left, opStack.top(), right));
    opStack.pop();
} // end execute

ValueType doOperation(ValueType operandL, char operation, ValueType operandR)
    throw (IllegalExprException)
{
    switch (operation){
    case '+':
        return operandL + operandR;
    case '-':
        return operandL - operandR;
    case '*':
        return operandL * operandR;
    case '/':
        return operandL / operandR;
    }
    return 0;
} // end doOperation
