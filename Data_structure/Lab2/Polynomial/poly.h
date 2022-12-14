// B911139, 이정진

#ifndef POLY_H
#define POLY_H

using namespace std;

class Polynomial; // 전방참조

class Term {
	friend class Polynomial;
	friend ostream& operator<<(ostream&, Polynomial&);
	friend istream& operator>>(istream&, Polynomial&);
private:
	float coef; // coefficient
	int exp; // exponent
};

class Polynomial {
public:
	Polynomial(); // construct a polynomial p(x) = 0.
	Polynomial operator+(Polynomial&); // 다항식의 합을 반환
	void NewTerm(const float, const int);
	friend ostream& operator<<(ostream&, Polynomial&);
	friend istream& operator>>(istream&, Polynomial&);
private:
	Term* termArray;
	int capacity; // 1로 초기화
	int terms; // 0 저장된 항의 수로 으로 초기화
};
#endif