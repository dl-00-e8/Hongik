// B911139, ������
#include <iostream>
#include <stack>
#include "post.h"

using namespace std;

bool Token::operator==(char b) { return len == 1 && str[0] == b; }

bool Token::operator!=(char b) { return len != 1 || str[0] != b; }

Token::Token() {}

Token::Token(char c) : len(1), type(c)
{
	str = new char[1]; str[0] = c;
}// default type = c itself

Token::Token(char c, char c2, int ty) : len(2), type(ty)
{
	str = new char[2]; str[0] = c; str[1] = c2;
}

Token::Token(char* arr, int l, int ty = ID) : len(l), type(ty) {
	str = new char[len + 1];
	for (int i = 0; i < len; i++) str[i] = arr[i];
	str[len] = '\0';
	if (type == NUM) {
		ival = arr[0] - '0';
		for (int i = 1; i < len; i++) ival = ival * 10 + arr[i] - '0';
	}
	else if (type == ID) ival = 0;
	else throw "must be ID or NUM";
}

bool Token::IsOperand() { return type == ID || type == NUM; }

ostream& operator<<(ostream& os, Token t) {
	if (t.type == UMINUS) os << "-u";
	else if (t.type == NUM) os << t.ival;
	else for (int i = 0; i < t.len; i++) os << t.str[i];
	os << " ";
	return os;
}

bool GetID(Expression& e, Token& tok)
{
	char arr[MAXLEN]; int idlen = 0;
	char c = e.str[e.pos];
	if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')) return false;
	arr[idlen++] = c;
	e.pos++;
	while ((c = e.str[e.pos]) >= 'a' && c <= 'z'
		|| c >= 'A' && c <= 'Z'
		|| c >= '0' && c <= '9')
	{
		arr[idlen++] = c; e.pos++;
	}
	arr[idlen] = '\0';
	tok = Token(arr, idlen, ID); // return an ID
	return true;
}

bool GetInt(Expression& e, Token& tok)
{
	//�ڵ� �Է�
	char arr[MAXLEN];
	int intLen = 0;
	char c = e.str[e.pos];

	if (!(c >= '0' && c <= '9')) {
		return false;
	}

	arr[intLen++] = c;
	e.pos++;

	while ((c = e.str[e.pos]) >= '0' && c <= '9') {
		arr[intLen++] = c;
		e.pos++;
	}

	arr[intLen] = '\0';
	tok = Token(arr, intLen, NUM);
	return true;
}

void SkipBlanks(Expression& e)
{
	char c;
	while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t'))
		e.pos++;
}

bool TwoCharOp(Expression& e, Token& tok)
{ //7 // <= >= == != && || -u ���� �α��� ��ū�� �� ó��
	char c = e.str[e.pos]; char c2 = e.str[e.pos + 1];
	int op; // LE GE EQ NE AND OR UMINUS
	if (c == '<' && c2 == '=') {
		op = LE;
	}
	else if(c == '>' && c2 == '=') {
		op = GE;
	}// : type op �ڵ��Է� �� �� ���� ��ū�� ���� �˸��� �� �� ����
	else if (c == '=' && c2 == '=') {
		op = EQ;
	}
	else if (c == '!' && c2 == '=') {
		op = NE;
	}
	else if (c == '&' && c2 == '&') {
		op = AND;
	}
	else if (c == '|' && c2 == '|') {
		op = OR;
	}
	else if(c == '-' && c2 == 'u') {
		op = UMINUS;
	}
	else {
		return false; // false return . �´� �� ���� ��ū�� �ƴϸ� �� �Ѵ�
	}

	tok = Token(c, c2, op); e.pos += 2;
	return true;
}

bool OneCharOp(Expression& e, Token& tok)
{
	char c = e.str[e.pos];
	if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' ||
		c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=')
	{
		tok = Token(c); e.pos++; return true;
	}
	return false;
}

Token NextToken(Expression& e, bool INFIX = true)
{
	static bool oprrFound = true; // . ������ ������ �߰ߵǾ��ٰ� ����
	Token tok;
	SkipBlanks(e); // skip blanks if any
	if (e.pos == e.len) // No more token left in this expression
	{
		if (INFIX) oprrFound = true; return Token('#');
	}
	if (GetID(e, tok) || GetInt(e, tok))
	{
		if (INFIX) oprrFound = false; return tok;
	}
	if (TwoCharOp(e, tok) || OneCharOp(e, tok)) {
		if (tok.type == '-' && INFIX && oprrFound) // operator - �� �߰�
			tok = Token('-', 'u', UMINUS); // unary minus(-u)�� �ٲٽÿ�
		if (INFIX) oprrFound = true; return tok;
	}
	throw "Illegal Character Found";
}

int icp(Token& t) { // in-coming priority
	int ty = t.type;
	/* ty '(' 0, UMINUS '!' 1, �� �� �� ��
	 '*' '/' '%' 2, ��+�� '-' 3,'<' '>' LE GE 4, �� �� �� �� �� �� �� �� ��
	 EQ NE 5, AND 6, OR 7,'=' 8, '#' 9 return .*/

	if (ty == '(') {
		return 0;
	}
	else if (ty == '!' || ty == UMINUS) {
		return 1;
	}
	else if (ty == '*' || ty == '/' || ty == '%') {
		return 2;
	}
	else if (ty == '+' || ty == '-') {
		return 3;
	}
	else if (ty == '<' || ty == LE || ty == GE || ty == '>') {
		return 4;
	}
	else if (ty == EQ || ty == NE) {
		return 5;
	}
	else if (ty == AND) {
		return 6;
	}
	else if (ty == OR) {
		return 7;
	}
	else if (ty == '=') {
		return 8;
	}
	else if (ty == '#') {
		return 9;
	}

	return 0;
}

int isp(Token& t) { //in-stack priority
	//�ڵ� �Է�
	int ty = t.type;

	if (ty == '(') {
		return 9;
	}
	else if (ty == '!' || ty == UMINUS) {
		return 1;
	}
	else if (ty == '*' || ty == '/' || ty == '%') {
		return 2;
	}
	else if (ty == '+' || ty == '-') {
		return 3;
	}
	else if (ty == '<' || ty == LE || ty == GE || ty == '>') {
		return 4;
	}
	else if (ty == EQ || ty == NE) {
		return 5;
	}
	else if (ty == AND) {
		return 6;
	}
	else if (ty == OR) {
		return 7;
	}
	else if (ty == '=') {
		return 8;
	}
	else if (ty == '#') {
		return 10;
	}

	return 0;
}

void Postfix(Expression e) {
	// STL stack , for */ �̿��ϰ� ������ ������ ���� ���� ���� �ٲ۴�
	// while (stack.top()!='#') { cout << stack.top(); stack.pop(); }
	// stack.pop();
	// 
	// infix expression e�� postfix form���� �ٲپ� ���
	// ����: e�� ������ ��ū�� ��#����. // ������ �ٴ� (bottom)���� ��#���� �ִ´�.
	stack<Token> stack; // ������ �ʱ�ȭ
	stack.push(Token('#'));
	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
		if (x.IsOperand()) cout << x;
		else if (x == ')') {// unstack until ��(��
			for (; stack.top() != '('; stack.pop())
				cout << stack.top();
				stack.pop(); // unstack ��(��
			}
		else { // x is an operator
			for (; isp(stack.top()) <= icp(x); stack.pop()) {
				if (x == '=' && stack.top() == '=') break;
					cout << stack.top();
			}
			stack.push(x);
		}
	// end of expression; empty the stack
	while (stack.top() != '#') {
		cout << stack.top(); stack.pop();
	}
	cout << endl;
	
}