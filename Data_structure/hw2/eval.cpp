#include <iostream>
#include <stack>
#include "post.h"

using namespace std;

int GetVal(Token& opnd)
{
	if (opnd.type == NUM) return opnd.ival;
	return 0; // ID인 경우는 0을 return하자
}
Token UnaryOp(int op, Token& x)
{ // UMINUS와 ‘!’의 두가지 경우만 처리함
	if (!x.IsOperand()) throw "Operand Only for Unary Operator";
	Token tmp; tmp.type = NUM;
	if (op == UMINUS) tmp.ival = -GetVal(x);
	else if (op == '!') tmp.ival = !GetVal(x);
	else throw "Invalid unary operator";
	return tmp;
}
Token BinaryOp(int op, Token& left, Token& right)
{
	if (!left.IsOperand() || !right.IsOperand())
		throw "Two Operands required for Binary Operation";
	Token tmp; tmp.type = NUM;
	int val1 = GetVal(left), val2 = GetVal(right);
	if (op == '+') tmp.ival = val1 + val2;
	else if (op == '-') tmp.ival = val1 - val2;
	else if (op == '*') tmp.ival = val1 * val2;
	else if (op == '/') {
		if (val2 == 0) {
			throw "Integer division by zero";
		}
		tmp.ival = val1 / val2;
	}
	else if (op == '%') tmp.ival = val1 % val2;
	else if (op == '<') tmp.ival = val1 < val2;
	else if (op == '>') tmp.ival = val1 > val2;
	else if (op == GE) tmp.ival = val1 >= val2;
	else if (op == LE) tmp.ival = val1 <= val2;
	else if (op == EQ) tmp.ival = val1 == val2;
	else if (op == NE) tmp.ival = val1 != val2;
	else if (op == AND) tmp.ival = val1 && val2;
	else if (op == OR) tmp.ival = val1 || val2;
	else if (op == '=') throw "Assignment Not Yet Implemented";
	else throw "No such binary operator";
	return tmp;
}
Token DeleteFromStack(stack<Token>& stack)
{ // 스택의 top에 있는 것을 꺼내어 return한다.
	if (stack.empty()) throw "Trying to pop from an empty stack";
	Token tmp = stack.top();
	stack.pop();
	return tmp;
}
void Eval(Expression e)
{ // postfix표현식을 입력으로 받아 그 값을 계산한다.
	stack<Token> stack;
	Token opnd1, opnd2;
	for (Token x = NextToken(e, false); x != '#'; x = NextToken(e, false))
		if (x.IsOperand()) stack.push(x);
		else { // x is an operator
			if (x.type == UMINUS || x.type == '!') { // unary operator
				opnd1 = DeleteFromStack(stack);
				stack.push(UnaryOp(x.type, opnd1));
			}
			else { // binary operator
		 //... 코드 추가 할 것
				opnd1 = DeleteFromStack(stack);
				opnd2 = DeleteFromStack(stack);
				stack.push(BinaryOp(x.type, opnd1, opnd2));
			}
		}
	cout << DeleteFromStack(stack) << endl;// 최종 계산 결과를 출력하자
}