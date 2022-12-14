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
	//parent[i] 값을 출력하기
	for (int i = 0; i < s.n; i++) {
		os << i << ":" << s.parent[i] << "  ";
	}
	os << endl;

	return os;
}

void Sets::SimpleUnion(int i, int j)
{
	// 교재 참조 작성
	parent[i] = j;
}

int Sets::SimpleFind(int i)
{
	// 교재 참조 작성
	int r;
	for (r = 0; parent[r] >= 0; r = parent[r]);

	return r;
}

void Sets::WeightedUnion(int i, int j)
{
	// 교재 참조 작성
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) { // i의 노드 수가 적으면
		parent[i] = j; // j를 새 루트로 만든다
		parent[j] = temp;
	}
	else { // j의 노드 수가 적거나 같으면
		parent[j] = i; // i를 새 루트로 만든다
		parent[i] = temp;
	}
}

int Sets::CollapsingFind(int i) { // Depth 함수를 추가해서 가 짧아지는 것 확인하기	
	int r; // 교재에러 수정
	for (r = i; parent[r] >= 0; r = parent[r]); // 루트를 찾음
	while (i != r) { //붕괴
		int s = parent[i];
		parent[i] = r;
		i = s;
	}
	return r;
}