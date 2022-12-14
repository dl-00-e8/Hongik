// B911139, ������
#include <iostream>
#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(int x = 0, int y = 0, int h = 0, int w = 0)
	: xLow(x), yLow(y), height(h), width(w) { }

Rectangle::Rectangle()
	: xLow(0), yLow(0), height(0), width(0) {}

Rectangle::~Rectangle() { }

void Rectangle::Print()
{ // ���� ���õ� ���â�� ���˿� �°� ����� �� �ֵ��� ����
	cout << "xLow: " << xLow << ", yLow: " << yLow << ", height: " << height << ", width: " << width << endl;
}

int Rectangle::Area()
{ // �������� �����Ͽ� ��ȯ�ϱ�

	return width * height; //GetWidth() * GetHeight()�� ����
}

bool Rectangle::LessThan(Rectangle& s)
{ // (Area()) �簢���� ���� �� ���� ��� ���� �簢������ ����
	return this->Area() < s.Area();
}

bool Rectangle::Equal(Rectangle& s)
{ // , , ��ġ ���� ���� ��� ���ƾ� ������ �簢������ ����
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
	//Rectangle s�� ��� ���� �� ���˿� ���߾� ����ϱ�
	os << "xLow: " << s.xLow << ", yLow: " << s.yLow << ", height: " << s.height << ", width: " << s.width << endl;

	return os;
}

bool Rectangle::operator<(Rectangle& s)
{
	//�ڵ� �߰�
	return this->Area() < s.Area();
}

bool Rectangle::operator==(Rectangle& s)
{
	//�ڵ� �߰�
	return Area() == s.Area();
}