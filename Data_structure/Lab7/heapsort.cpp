// B911139, 이정진
#include <iostream>
using namespace std;
template <class T>
void PrintArray(T* a, const int n)
{
	// 배열 a[]의 1부터 n까지 n개 항목 출력하기
	for (int i = 1; i < n + 1; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
template <class T>
void Adjust(T* a, const int root, const int n)
{ // 루트 root를 가진 이진트리를 히프 성질을 만족하도록 조정한다. 
  // root의 왼쪽과 오른쪽 서브 트리는 히프 성질을 이미 만족한다. 
  // 어떤 노드도 n보다 큰 인덱스를 갖지 않는다. 
	T e = a[root];
	//e에 대한 적절한 위치를 탐색
	int j; // 교재 수정 즉 j를 for문장 밖에서 선언해야 함
	for (j = 2 * root; j <= n; j *= 2) {
		if (j < n && a[j] < a[j + 1]) j++; // j는 부모의 최대 자식
		if (e >= a[j]) break; // e는 j의 부모로 삽입
		a[j / 2] = a[j]; // j번째 레코드를 트리 위로 이동
	}
	a[j / 2] = e;
}
template <class T>
void HeapSort(T* a, const int n)
{// a[1:n]을 비감소순으로 정렬한다. 
	for (int i = n / 2; i >= 1; i--) // 히프로 조정
		Adjust(a, i, n);
	for (int i = n - 1; i >= 1; i--) // 정렬 // 교재수정(int삽입)
	{
		swap(a[1], a[i + 1]); // 현 히프의 처음과 마지막을 교환
		Adjust(a, 1, i); // 히프로 조정
	}
}
int main()
{
	int a[] = { 0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19 }; //0번째는 사용안됨
	int n = sizeof(a) / sizeof(int) - 1; // 0번째 성분 제외
	cout << "Before Sorting : "; PrintArray(a, n);
	HeapSort(a, n);
	cout << "After Sorting : "; PrintArray(a, n);
}