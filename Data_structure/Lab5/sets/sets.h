#ifndef SETS_H
#define SETS_H
#include <iostream>

using namespace std;

class Sets {
public:
	Sets(int numberOfElements);
	void SimpleUnion(int i, int j);
	int SimpleFind(int i);
	void WeightedUnion(int i, int j);
	int CollapsingFind(int i);
	friend ostream& operator<<(ostream&, Sets&);
private:
	int* parent;
	int n; // number of set elements
};
#endif