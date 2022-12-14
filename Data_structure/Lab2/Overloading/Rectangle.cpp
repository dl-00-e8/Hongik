// B911139, 이정진
#include <iostream>
#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(int x = 0, int y = 0, int h = 0, int w = 0)
	: xLow(x), yLow(y), height(h), width(w) { }

Rectangle::Rectangle()
	: xLow(0), yLow(0), height(0), width(0) {}

Rectangle::~Rectangle() { }

void Rectangle::Print()
{ // 위에 제시된 출력창의 포맷에 맞게 출력할 수 있도록 구성
	cout << "xLow: " << xLow << ", yLow: " << yLow << ", height: " << height << ", width: " << width << endl;
}

int Rectangle::Area()
{ // 면적값을 산출하여 반환하기

	return width * height; //GetWidth() * GetHeight()도 가능
}

bool Rectangle::LessThan(Rectangle& s)
{ // (Area()) 사각형의 면적 이 작은 경우 작은 사각형으로 결정
	return this->Area() < s.Area();
}

bool Rectangle::Equal(Rectangle& s)
{ // , , 위치 넓이 높이 모두 같아야 동일한 사각형으로 결정
	if (this == &s) return true;
	if ((xLow == s.xLow) && (yLow == s.yLow) && (height == s.height) && (width == s.width)) return true;
	else return false;
}

bool Rectangle::EqualSize(Rectangle& s) {
	return Area() == s.Area();
}

int Rectangle::GetHeight() { 
	return height; 
}

int Rectangle::GetWidth() { 
	return width;
}

ostream& operator<<(ostream& os, Rectangle& s) {
	//Rectangle s의 멤버 변수 값 포맷에 맞추어 출력하기
	os << "xLow: " << s.xLow << ", yLow: " << s.yLow << ", height: " << s.height << ", width: " << s.width << endl;

	return os;
}

bool Rectangle::operator<(Rectangle& s)
{
	//코드 추가
	return this->Area() < s.Area();
}

bool Rectangle::operator==(Rectangle& s)
{
	//코드 추가
	return Area() == s.Area();
}