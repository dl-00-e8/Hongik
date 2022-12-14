// B911139, 이정진
#ifndef MSTREE_H
#define MSTREE_H
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class Sets {
public:
	Sets(int);
	void WeightedUnion(int i, int j);
	int Find(int i) { while (parent[i] >= 0) i = parent[i]; return i; }

private:
	int* parent;
	int n;
}; //5 program 5.23, 5.24 장의

Sets::Sets(int numberOfElements) {
	if (numberOfElements < 2) throw "Must have at least 2 elements.";
	n = numberOfElements;
	parent = new int[n];
	fill(parent, parent + n, -1);
}

void Sets::WeightedUnion(int i, int j)
{
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) { // i has fewer nodes
		parent[i] = j;
		parent[j] = temp;
	}
	else {// j has fewer nodes or the same number of nodes
		parent[j] = i;
		parent[i] = temp;
	}
}

int NNODES; // #nodes(vertices) in the graph

struct Edge {
	int v1, v2;
	double weight;
	bool operator==(Edge& e2) { return (v1 == e2.v1 && v2 == e2.v2); }
	bool operator!=(Edge& e2) { return (v1 != e2.v1 || v2 != e2.v2); }
};

ostream& operator<<(ostream& os, Edge& e) {
	os << "(" << e.v1 << "," << e.v2 << ") : " << e.weight << endl;
	return os;
}

bool GetEdge(istream& is, Edge& e) {
	// make sure that node number is 0 to NNODES-1
	is >> e.v1 >> e.v2 >> e.weight; if (!is.good()) return false;
	if (e.v1 < 0 || e.v1 >= NNODES || e.v2 < 0 || e.v2 >= NNODES || e.v1 == e.v2)
		throw "Incorrect Edge";
	if (e.v2 < e.v1) swap(e.v1, e.v2); // low-numbered vertex first
	return true;
}

class Compare {
public:
	bool operator() (Edge e1, Edge e2) { return e1.weight > e2.weight; }
};
#endif