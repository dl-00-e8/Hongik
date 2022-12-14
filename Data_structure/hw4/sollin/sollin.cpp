#include "mstree.h"

priority_queue< Edge, vector<Edge>, Compare >* PQ;

// 필요함수를 정의 및 구현하시오
void MoveIntoPQ(int v1root, int v2root) {
	while (!PQ[v2root].empty()) {
		Edge e = PQ[v2root].top();
		PQ[v2root].pop();
		PQ[v1root].push(e);
	}
}

void ReadEdges4sollin(istream& is) {
	// 각 점(tree) 마다 연결된 간선들의 minheap이 필요함
	// NNODES개의 minheap을 갖고 있는 PQ배열을 생성하시오
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
	// 각 노드가 트리(포리스트)이므로
	// 각 트리에 속한 최소 edge를 구한다
	// 단 트리가 WeightedUnion되므로 루트 v를 Find하고 최소 edge를 검색한다
	// vertex번호가 작은 PQ로 edge를 모은다
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

				// 함수 구현
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
	// kruskal 파일 입력 부분은 경우와 동일하게
	//추가
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