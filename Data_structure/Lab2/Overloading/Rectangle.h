// B911139, ������
#ifndef RECTANGLE_H
#define RECTANGLE_H

using namespace std;

class Rectangle {
public:
	Rectangle(int, int, int, int); // constructor
	Rectangle(); // default constructor
	~Rectangle(); // destructor
	void Print();
	int Area();
	bool LessThan(Rectangle&); // true ������ ������
	bool EqualSize(Rectangle&); // true ������ �����ϸ�
	bool Equal(Rectangle&); // Equal ( true) ������ ��� ����� �����ϸ�
	int GetHeight();
	int GetWidth();
	bool operator<(Rectangle&); // true ������ ������
	bool operator==(Rectangle&); // true ������ ������
	friend ostream& operator<<(ostream&, Rectangle&);
private:
	int xLow, yLow, height, width;
};
#endif