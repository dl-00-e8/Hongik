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
{ // 오름차수 정렬된 정수 리스트에서 e위치 검색하여 추가하기
	if (!first) //빈 리스트인 경우
	{
		first = last = new Node(e);
	}
	else if (e < first->data) // 맨 앞에 추가
	{
		first = new Node(e, first);
	}
	else if (e > last->data) // 맨 뒤에 추가
	{
		last->link = new Node(e);
		last = last->link;
	}
	else // e 추가할 위치 first부터 검색하여 추가 (prev와 cur 변경 주의)
	{
		Node* cur = first;
		Node* prev = first;

		while (cur) {
			if (cur->data < e) {
				prev = cur;
				cur = cur->link;
			}
			// prev와 cur 사이 삽입
			else if (cur->data > e) {
				prev->link = new Node(e, prev->link);
				break;
			}
			// 중복 삽입 불가
			else {
				break;
			}
		}
	}
} 

void IntList::Delete(int e)
{ 
	// 오름차순 정렬된 정수 리스트에서 e를 검색하여 삭제하기
	Node* cur = first; //first부터 e 검색하기
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