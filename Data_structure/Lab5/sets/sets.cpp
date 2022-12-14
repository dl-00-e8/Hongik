#include "sets.h"
#include <algorithm>

using namespace std;

Sets::Sets(int numberOfElements) // constructor
{
	if (numberOfElements < 2) throw "Must have at least 2 elements";
	n = numberOfElements;
	parent = new int[n];
	fill(parent, parent + n, -1);
}

ostream& operator<<(ostream& os, Sets& s)
{
	//parent[i] ���� ����ϱ�
	for (int i = 0; i < s.n; i++) {
		os << i << ":" << s.parent[i] << "  ";
	}
	os << endl;

	return os;
}

void Sets::SimpleUnion(int i, int j)
{
	// ���� ���� �ۼ�
	parent[i] = j;
}

int Sets::SimpleFind(int i)
{
	// ���� ���� �ۼ�
	int r;
	for (r = 0; parent[r] >= 0; r = parent[r]);

	return r;
}

void Sets::WeightedUnion(int i, int j)
{
	// ���� ���� �ۼ�
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) { // i�� ��� ���� ������
		parent[i] = j; // j�� �� ��Ʈ�� �����
		parent[j] = temp;
	}
	else { // j�� ��� ���� ���ų� ������
		parent[j] = i; // i�� �� ��Ʈ�� �����
		parent[i] = temp;
	}
}

int Sets::CollapsingFind(int i) { // Depth �Լ��� �߰��ؼ� �� ª������ �� Ȯ���ϱ�	
	int r; // ���翡�� ����
	for (r = i; parent[r] >= 0; r = parent[r]); // ��Ʈ�� ã��
	while (i != r) { //�ر�
		int s = parent[i];
		parent[i] = r;
		i = s;
	}
	return r;
}