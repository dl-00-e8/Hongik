// B911139, 이정진
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
	bool LessThan(Rectangle&); // true 면적이 작으면
	bool EqualSize(Rectangle&); // true 면적이 동일하면
	bool Equal(Rectangle&); // Equal ( true) 교재의 모든 멤버가 동일하면
	int GetHeight();
	int GetWidth();
	bool operator<(Rectangle&); // true 면적이 작으면
	bool operator==(Rectangle&); // true 면적이 같으면
	friend ostream& operator<<(ostream&, Rectangle&);
private:
	int xLow, yLow, height, width;
};
#endif