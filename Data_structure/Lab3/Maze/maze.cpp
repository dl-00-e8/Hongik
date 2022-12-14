#include <iostream>
#include <stack>

using namespace std;

const int MAXSIZE = 100; // up to 100 by 100 maze allowed
bool maze[MAXSIZE + 2][MAXSIZE + 2];
bool mark[MAXSIZE + 1][MAXSIZE + 1] = { 0 };

enum directions { N, NE, E, SE, S, SW, W, NW };
struct offsets
{
	int a, b;
} movea[8] = { -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1, -1,-1 };
struct Items {
	Items(int xx = 0, int yy = 0, int dd = 0) : x(xx), y(yy), dir(dd) {}
	int x, y, dir;
};
template <class T>
ostream& operator<< (ostream& os, stack<T>& s) {
	//�ڵ� �Է�:
	// ������ ������ �������� ���
	// ���� ��� : ������ �ϳ��� ���� �ٸ� �ӽ� ���ÿ� �־� ������
	// ��, ���������� �� �ӽ� ���ÿ��� �ϳ��� ���� ����ϸ� ��
	// os << "top = " << s.top << endl;
	// for (int i = 0; i <= s.top; i++) os << i << ":" << s.stack[i] << endl;
	stack<T> s2; // ������ ����ϱ� ���� �ӽ� ���� s2 �̿�
	while (!s.empty()) { s2.push(s.top()); s.pop(); }
	while (!s2.empty()) { os << " -> " << s2.top(); s.push(s2.top()); s2.pop(); }

	return os;
}
ostream& operator<<(ostream& os, Items& item)
{
	static int count = 0; // 5���� Items�� ��µ� ������ �� �ٲٱ� ����
	os << "(" << item.x << "," << item.y << ")";
	count++; if ((count % 5) == 0) cout << endl;
	return os;
}
void Path(const int m, const int p)
{
	mark[1][1] = 1;
	stack<Items> stack; // C++ STD stack�� �̿��ϱ�
	Items temp(1, 1, E);
	stack.push(temp);
	//�ڵ� �Է�
	while (!stack.empty())
	{
		temp = stack.top(); stack.pop(); // unstack
		int i = temp.x; int j = temp.y; int d = temp.dir;
		while (d < 8) // move forward
		{ // (i,j)���� (g,h)�� �̵��Ѵٰ� ����. 
			int g = i + movea[d].a; int h = j + movea[d].b;
			if ((g == m) && (h == p)) { // reached exit
				/*
				cout << stack; // print reverse order of stack pops.
				// Now let��s print the last two squares on the path
				temp.x = i; temp.y = j; cout << "->" << temp;
				temp.x = m; temp.y = p; cout << "->" << temp << endl;
				*/
				/* ������ å�� �����ϴ�. �� �������� ����� ����� ������ ���� �Ѵ�. */
				cout << stack;
				temp.x = i; temp.y = j; cout << " -> " << temp;
				temp.x = m; temp.y = p; cout << " -> " << temp << endl;
				
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h])) { // new position
				mark[g][h] = 1; // �湮�� ������ ǥ��
				temp.x = i; temp.y = j; temp.dir = d + 1; //�� ��ġ�� ���� �� ������ �õ��� ���� ����
				stack.push(temp); // stack it
				i = g; j = h; d = N; // N������� (�ð��������) �õ�����
			}
			else d++; // try next direction
		} // end of while (d < 8)
	} // end of while (!stack.empty())
	cout << "No path in maze." << endl;
}
void getdata(istream& is, int& m, int& p)
{ // �ڷ�ȭ���� �о�鿩 maze�� �����Ѵ�.
	is >> m >> p;
	for (int i = 0; i < m + 2; i++) { maze[i][0] = 1; maze[i][p + 1] = 1; }
	for (int j = 1; j <= p; j++) { maze[0][j] = 1; maze[m + 1][j] = 1; }
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= p; j++)
			is >> maze[i][j];
}