// B911139, ÀÌÁ¤Áø

#include <iostream>
#include "list.h"

int main()
{
	IntList il;

	il.InsertBack(5); il.InsertBack(7); il.InsertBack(9);
	cout << il;

	il.InsertFront(4); il.InsertFront(3);
	cout << il;

	il.Insert(6); il.Insert(10); il.Insert(2);
	il.Insert(5); il.Insert(2); il.Insert(10); // already existing ones
	cout << il;

	il.Delete(2); // delete the first
	il.Delete(6); // delete an integer in the middle
	il.Delete(10); // delete the last
	cout << il;
}
