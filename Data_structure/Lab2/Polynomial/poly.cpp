// B911139, 이정진

#include <iostream>
#include "poly.h"

using namespace std;

istream& operator>> (istream& is, Polynomial& p) {
	// #terms and (coefficoent, exponent) pair . 의 들을 읽어들인다
	// . 높은 차수의 항부터 입력되어 저장된다고 가정한다
	int noofterms; float coef; int exp;
	is >> noofterms;
	for (int i = 0; i < noofterms; i++) {
		is >> coef >> exp; // pair . 계수와 지수 를 읽어들인다
		p.NewTerm(coef, exp);
	}
	return is;
}

ostream& operator<< (ostream& os, Polynomial& p) {
	// 포맷에 맞게 출력하는 코드 입력
	for (int i = 0; i < p.terms; i++) {
		// 차수 구분
		if (p.termArray[i].exp > 1) {
			if(p.termArray[i].coef == 1) {
				os << "x^" << p.termArray[i].exp;
			}
			else if (p.termArray[i].coef == -1) {
				os << "-x^" << p.termArray[i].exp;
			}
			else {
				os << p.termArray[i].coef << "x^" << p.termArray[i].exp;
			}
		}
		else if (p.termArray[i].exp == 1) {
			if (p.termArray[i].coef == 1) {
				os << "x^";
			}
			else if (p.termArray[i].coef == -1) {
				os << "-x";
			}
			else {
				os << p.termArray[i].coef << "x";
			}
		}
		else {
			os << p.termArray[i].coef;
		}

		if (i < p.terms - 1) {
			if (p.termArray[i + 1].coef > 0) {
				os << " +";
			}
			else if (p.termArray[i + 1].coef < 0) {
				os << " ";
			}
		}
	}
	
	os << endl;

	return os;
}

Polynomial::Polynomial() :capacity(1), terms(0)
{
	termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	// 다항식 뒤에 새로운 항을 추가하는 함수로 교재에 있음
	if (terms == capacity)
	{//termArray의 크기를 두 배로 확장
		capacity *= 2;
		Term* temp = new Term[capacity]; // 새로운 배열
		copy(termArray, termArray + terms, temp);
		delete[] termArray; // 그전 메모리를 반환
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}

Polynomial Polynomial::operator+(Polynomial& b)
{
	// Add 교재의 와 동일한 함수로 이름만 바꾸면 됨
	Polynomial c; // 합을 저장
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms))
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	// add in remaining terms of *this
	for (; aPos < terms; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	// add in remaining terms of b(x)
	for (; bPos < b.terms; bPos++) // 교재에는 b++로 잘못 적혀있음
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}