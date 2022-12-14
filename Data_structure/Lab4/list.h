#include <iostream>

using namespace std;

class Node
{
public:
	friend class IntList;
	Node(int d = 0, Node* l = 0) : data(d), link(l) { }
	friend ostream& operator<<(ostream&, IntList&);
private:
	int data;
	Node* link;
};

class IntList
{
public:
	IntList() { last = first = 0; }
	void InsertBack(int); // 리스트 뒤에 삽입
	void InsertFront(int); // 리스트 앞에 삽입
	void Insert(int); // 정렬되어 있다는 가정 하에 제 위치에 삽입
	void Delete(int);
	friend ostream& operator<<(ostream&, IntList&);
private:
	Node* first; // 첫 노드를 가리킴
	Node* last; // 마지막 노드를 가리킴
};