// B911139, ������

#include <iostream>
#include "post.h"

using namespace std;

void Postfix(Expression);

int main()
{
	char line[MAXLEN];
	while (cin.getline(line, MAXLEN)) {
		Expression e(line); // line Expression ���۸� �̿��Ͽ� �� ����
		try {
			Postfix(e);
		}
		catch (char const* msg) {
			cerr << "Exception: " << msg << endl;
		}
	}
}