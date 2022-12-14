#include "mstree.h"

priority_queue< Edge, vector<Edge>, Compare > PQ;

queue< Edge >* Q; // each vertex has a queue

void MoveIntoPQ_EdgesOfNodes(int v) {
	// Move all edges of vertex 'v' in the queue Q into PQ
	while (!Q[v].empty()) {
		PQ.push(Q[v].front());
		Q[v].pop();
	}
}

void prim() {
	Sets sets(NNODES);
	int nedges = 0; // #edges found up to now.
	while (nedges < NNODES - 1) {
		if (PQ.empty()) throw "No Spanning Tree Exists.";
		Edge e = PQ.top(); PQ.pop();
		// 현재 선택된 edge ed의 두 점(노드)들의 루트를 구한다
		int v1root = sets.Find(e.v1);
		int v2root = sets.Find(e.v2);
		// PQ 꺼낸 e가 자격이 있으면, 두 집합 WeightedUnion, nedges  갯수추가, e출력
		if (v1root != v2root) {
			sets.WeightedUnion(v1root, v2root);
			nedges++;

			cout << e;

			// 트리에 연결 처리된 e의 두 점에 연결된 edge들을 PQ로 옮긴다
			MoveIntoPQ_EdgesOfNodes(e.v1);
			MoveIntoPQ_EdgesOfNodes(e.v2);
		}
	}
}

void ReadEdges4prim(istream& is) {
	Edge e;
	// NNODES개 각 점 (vertex)를 위한 queue들을 배열로 생성한다
	// 각 점에 연결된 간선 (edges)를 나타내기 위함
	Q = new queue<Edge>[NNODES];
	while (GetEdge(is, e))
	{
		// 두 점 (vertex 또는 노드)의 큐에 각각 e를 넣는다.
		// edge (e.v1, e.v2) 한 에 연결된 점은 두 개
		Q[e.v1].push(e);
		Q[e.v2].push(e);
	}
	MoveIntoPQ_EdgesOfNodes(0); // 0 edge PQ . 시작 점 의 들을 로 이동한다
}

int main(int argc, char* argv[]) {
	// kruskal 입력부분은 경우와 동일하게
	// 추가 할 것
	ifstream is;
	if (argc == 1) is.open("kin.txt");
	else is.open(argv[1]);
	if (!is) { cerr << "No such input file\n"; exit(1); }
	is >> NNODES;
	if (NNODES < 2) { cerr << "#nodes must be 2.." << endl; exit(1); }
	try {
		ReadEdges4prim(is);
		prim();
	}
	catch (char const* str)
	{
		cerr << "Exception: " << str << endl; exit(1);
	}
}