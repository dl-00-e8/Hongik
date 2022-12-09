// B911139, 이정진

#include <iostream>
#include "post.h"

using namespace std;

void Postfix(Expression);

int main()
{
	char line[MAXLEN];
	while (cin.getline(line, MAXLEN)) {
		Expression e(line); // line Expression 버퍼를 이용하여 을 만듬
		try {
			Postfix(e);
		}
		catch (char const* msg) {
			cerr << "Exception: " << msg << endl;
		}
	}
}