#include <iostream>

using namespace std;

class Bag
{
public:
	Bag(int bagCapacity = 10);
	virtual ~Bag();
	virtual int Size() const;
	virtual bool IsEmpty() const;
	virtual int Element() const;
	virtual void Push(const int);
	virtual void Pop();
	friend ostream& operator<<(ostream&, Bag&);
protected:
	int* array;
	int capacity;
	int top;
};
class Stack : public Bag
{
public:
	Stack(int stackCapacity = 10);
	~Stack();
	int Top() const;
	void Pop();
};
void ChangeSize1D(int*& a, const int oldsize, const int newSize);