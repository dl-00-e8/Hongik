// B911139, ������

#include <iostream>
#include "poly.h"

using namespace std;

int main() {
	Polynomial p1, p2;
	
	cin >> p1 >> p2; // 2 . ���� ���׽��� �о� ���δ�
	Polynomial p3 = p1 + p2;
	cout << p1 << p2 << p3;

}
