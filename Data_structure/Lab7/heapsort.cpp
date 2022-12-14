// B911139, ������
#include <iostream>
using namespace std;
template <class T>
void PrintArray(T* a, const int n)
{
	// �迭 a[]�� 1���� n���� n�� �׸� ����ϱ�
	for (int i = 1; i < n + 1; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
template <class T>
void Adjust(T* a, const int root, const int n)
{ // ��Ʈ root�� ���� ����Ʈ���� ���� ������ �����ϵ��� �����Ѵ�. 
  // root�� ���ʰ� ������ ���� Ʈ���� ���� ������ �̹� �����Ѵ�. 
  // � ��嵵 n���� ū �ε����� ���� �ʴ´�. 
	T e = a[root];
	//e�� ���� ������ ��ġ�� Ž��
	int j; // ���� ���� �� j�� for���� �ۿ��� �����ؾ� ��
	for (j = 2 * root; j <= n; j *= 2) {
		if (j < n && a[j] < a[j + 1]) j++; // j�� �θ��� �ִ� �ڽ�
		if (e >= a[j]) break; // e�� j�� �θ�� ����
		a[j / 2] = a[j]; // j��° ���ڵ带 Ʈ�� ���� �̵�
	}
	a[j / 2] = e;
}
template <class T>
void HeapSort(T* a, const int n)
{// a[1:n]�� �񰨼Ҽ����� �����Ѵ�. 
	for (int i = n / 2; i >= 1; i--) // ������ ����
		Adjust(a, i, n);
	for (int i = n - 1; i >= 1; i--) // ���� // �������(int����)
	{
		swap(a[1], a[i + 1]); // �� ������ ó���� �������� ��ȯ
		Adjust(a, 1, i); // ������ ����
	}
}
int main()
{
	int a[] = { 0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19 }; //0��°�� ���ȵ�
	int n = sizeof(a) / sizeof(int) - 1; // 0��° ���� ����
	cout << "Before Sorting : "; PrintArray(a, n);
	HeapSort(a, n);
	cout << "After Sorting : "; PrintArray(a, n);
}