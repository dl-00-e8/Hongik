// B911139, 이정진

#include <iostream>
#include "poly.h"

using namespace std;

int main() {
	Polynomial p1, p2;
	
	cin >> p1 >> p2; // 2 . 개의 다항식을 읽어 들인다
	Polynomial p3 = p1 + p2;
	cout << p1 << p2 << p3;

}
