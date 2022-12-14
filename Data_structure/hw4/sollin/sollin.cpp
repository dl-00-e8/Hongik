#include "mstree.h"

priority_queue< Edge, vector<Edge>, Compare >* PQ;

// �ʿ��Լ��� ���� �� �����Ͻÿ�
void MoveIntoPQ(int v1root, int v2root) {
	while (!PQ[v2root].empty()) {
		Edge e = PQ[v2root].top();
		PQ[v2root].pop();
		PQ[v1root].push(e);
	}
}

void ReadEdges4sollin(istream& is) {
	// �� ��(tree) ���� ����� �������� minheap�� �ʿ���
	// NNODES���� minheap�� ���� �ִ� PQ�迭�� �����Ͻÿ�
	//PQ = new ....
	PQ = new priority_queue<Edge, vector<Edge>, Compare>[NNODES];
	Edge e;
	while (GetEdge(is, e)) {
		PQ[e.v1].push(e);
		PQ[e.v2].push(e);
	}
}

void sollin() {
	Sets sets(NNODES);
	// �� ��尡 Ʈ��(������Ʈ)�̹Ƿ�
	// �� Ʈ���� ���� �ּ� edge�� ���Ѵ�
	// �� Ʈ���� WeightedUnion�ǹǷ� ��Ʈ v�� Find�ϰ� �ּ� edge�� �˻��Ѵ�
	// vertex��ȣ�� ���� PQ�� edge�� ������
	int nedges = 0;
	while (nedges < NNODES - 1) {
		for (int i = 0; i < NNODES - 1; i++) {
			int v = sets.Find(i);
			
			if (PQ[v].empty()) {
				continue;
			}

			Edge e = PQ[v].top();
			PQ[v].pop();

			int v1root = sets.Find(e.v1);
			int v2root = sets.Find(e.v2);

			if (v1root != v2root) {
				sets.WeightedUnion(v1root, v2root);
				nedges++;

				cout << e;

				// �Լ� ����
				if (v1root < v2root) {
					MoveIntoPQ(v1root, v2root);
				}
				else {
					MoveIntoPQ(v2root, v1root);
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
	// kruskal ���� �Է� �κ��� ���� �����ϰ�
	//�߰�
	ifstream is;
	if (argc == 1) is.open("kin.txt");
	else is.open(argv[1]);
	if (!is) { cerr << "No such input file\n"; exit(1); }
	is >> NNODES;
	if (NNODES < 2) { cerr << "#nodes must be 2.." << endl; exit(1); }
	try {
		ReadEdges4sollin(is);
		sollin();
	}
	catch (char const* str)
	{
		cerr << "Exception: " << str << endl; exit(1);
	}
}