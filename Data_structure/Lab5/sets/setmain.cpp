// B911139, ÀÌÁ¤Áø

#include <iostream>
#include "sets.h"

using namespace std;

int main() {
	Sets a(8), b(8);
	cout << "SimpleUnion example of set a " << endl;
	cout << a << endl;
	a.SimpleUnion(0, 1);
	a.SimpleUnion(1, 2);
	a.SimpleUnion(2, 3);
	a.SimpleUnion(3, 4);
	a.SimpleUnion(4, 5);
	a.SimpleUnion(5, 6);
	a.SimpleUnion(6, 7);
	cout << a << endl;
	cout << "WeightedUnion Example of set b " << endl;
	cout << b << endl;
	b.WeightedUnion(0, 1);
	b.WeightedUnion(2, 3);
	b.WeightedUnion(4, 5);
	b.WeightedUnion(6, 7);
	cout << b << endl;
	b.WeightedUnion(0, 2);
	b.WeightedUnion(4, 6);
	cout << b << endl;
	b.WeightedUnion(0, 4);
	cout << b << endl << endl;

	b.CollapsingFind(7);
	cout << b << endl << endl;
}