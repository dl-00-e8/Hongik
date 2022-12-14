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
	void InsertBack(int); // ����Ʈ �ڿ� ����
	void InsertFront(int); // ����Ʈ �տ� ����
	void Insert(int); // ���ĵǾ� �ִٴ� ���� �Ͽ� �� ��ġ�� ����
	void Delete(int);
	friend ostream& operator<<(ostream&, IntList&);
private:
	Node* first; // ù ��带 ����Ŵ
	Node* last; // ������ ��带 ����Ŵ
};