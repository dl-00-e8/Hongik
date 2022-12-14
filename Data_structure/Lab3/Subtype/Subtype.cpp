// B911139, ������

#include <iostream>
#include "bagstack.h"

using namespace std;

int main() {
	Bag b(3);
	Stack s(3);
	b.Push(1); b.Push(2); b.Push(3);
	b.Push(4); b.Push(5);
	cout << "Bag: " << b;
	s.Push(1); s.Push(2); s.Push(3);
	s.Push(4); s.Push(5);
	cout << "Stack: " << s << endl;
	b.Pop(); s.Pop();
	cout << "Bag: " << b;
	cout << "Stack: " << s << endl << endl;
	int j = s.Size(); //Stack Bag Size() �� �θ�Ŭ���� �� �� �ҷ�����
	cout << "Stack ũ��: " << j << endl;
	j = s.Top(); //Stack Top() . �� �� �ҷ�����
	cout << "Stack Top() ���: " << j << endl;
	j = s.Element(); //Stack Bag Element() . �� �θ�Ŭ���� �� �� �ҷ�����
	cout << "Stack Element() ���: " << j << endl << endl;
}