// B911139, ¿Ã¡§¡¯
#include <iostream>
#include "Rectangle.h"

using namespace std;

int main() {
	Rectangle r(2, 3, 4, 6), s(1, 2, 6, 6);
	Rectangle* t = &s;
	Rectangle u;

	/*
	if (r.Equal(s)) {
		cout << "Same Rectangle" << endl;
	}
	else {
		cout << "Different Rectangle" << endl;
	}
	*/

	cout << "<rectangle r> "; r.Print();
	cout << "<rectangle s> "; s.Print();
	if (r.LessThan(s))
		cout << "s is bigger";
	else if (r.EqualSize(s))
		cout << "Same Size";
	else cout << "r is bigger";
	cout << endl << endl;

	// Operator Overloading
	cout << "<rectangle r> " << r;
	cout << "<rectangle s> " << s;
	if (r < s) {
		cout << "s is bigger";
	}
	else if (r == s) {
		cout << "Same Size";
	}
	else {
		cout << "r is bigger";
	}
	cout << endl;

	return 0;
}