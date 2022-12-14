#include "list.h"

ostream& operator<<(ostream& os, IntList& il)
{
	Node* ptr = il.first;
	while (ptr != 0) {
		os << ptr->data << " "; ptr = ptr->link;
	}
	os << endl;
	return os;
}

void IntList::InsertBack(int e)
{
	if (!first)
		first = last = new Node(e);
	else {
		last->link = new Node(e);
		last = last->link;
	}
}

void IntList::InsertFront(int e)
{ 
	if (!first) {
		first = last = new Node(e);
	}
	else {
		first = new Node(e, first);
	}
} 

void IntList::Insert(int e)
{ // �������� ���ĵ� ���� ����Ʈ���� e��ġ �˻��Ͽ� �߰��ϱ�
	if (!first) //�� ����Ʈ�� ���
	{
		first = last = new Node(e);
	}
	else if (e < first->data) // �� �տ� �߰�
	{
		first = new Node(e, first);
	}
	else if (e > last->data) // �� �ڿ� �߰�
	{
		last->link = new Node(e);
		last = last->link;
	}
	else // e �߰��� ��ġ first���� �˻��Ͽ� �߰� (prev�� cur ���� ����)
	{
		Node* cur = first;
		Node* prev = first;

		while (cur) {
			if (cur->data < e) {
				prev = cur;
				cur = cur->link;
			}
			// prev�� cur ���� ����
			else if (cur->data > e) {
				prev->link = new Node(e, prev->link);
				break;
			}
			// �ߺ� ���� �Ұ�
			else {
				break;
			}
		}
	}
} 

void IntList::Delete(int e)
{ 
	// �������� ���ĵ� ���� ����Ʈ���� e�� �˻��Ͽ� �����ϱ�
	Node* cur = first; //first���� e �˻��ϱ�
	Node* prev = first;
	Node* x;
	
	while (cur) {
		if (cur->data > e) // no item to delete
		{
			break;
		}
		else if (cur->data < e) // go to next node
		{			
			prev = cur;
			cur = cur->link;
		}
		else if(cur->data == e) // delete
		{
			x = cur;
			prev->link = x->link;

			if (x == first) {
				first = first->link;
			}
			else if (x == last) {
				prev->link = NULL;
				last = prev;
			}
			else {
				prev->link = x->link;
			}

			delete x;
			break;
		}
	}// while
}