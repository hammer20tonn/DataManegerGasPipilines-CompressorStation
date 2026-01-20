#include "gtn.h"
#include "Mainthread.h"

#include <iostream>
#include <stack>
#include <algorithm>

#include <vector>
#include <queue>

#include "utils.h"
using namespace std;

int gtn::MaxID = 0;


gtn::gtn(set<Pipeline>& pl, set<Compressedstation>& cs) : Pipelines(pl), Compressedstations(cs) {
	id = MaxID++;
}









vector<int> gtn::topologicalSortKahn(int V, vector<vector<int>>& adj) {
	vector<int> inDegree(V, 0);

	for (int u = 0; u < V; u++) {
		for (int v : adj[u]) {
			inDegree[v]++;
		}
	}

	queue<int> q;
	for (int i = 0; i < V; i++) {
		if (inDegree[i] == 0) q.push(i);
	}

	vector<int> result;

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		result.push_back(u);

		for (int v : adj[u]) {
			inDegree[v]--;
			if (inDegree[v] == 0) {
				q.push(v);
			}
		}
	}

	return result;
}







void gtn::getTopologicalSort() {
	if (Connections.empty()) {
		cout << "Connection list is empty." << endl;
		return;
	}

	set<int> s;
	for (Connection& i : Connections) {
		s.insert(i.cs1.id);
		s.insert(i.cs2.id);
	}
	size_t V = s.size();
	vector<vector<int>> adj(V);
	for (Connection& i : Connections) {
		adj[i.cs1.id].push_back(i.cs2.id);
	}
	vector<int> sortedOrder = topologicalSortKahn(V, adj);
	if (sortedOrder.size() != V) {
		cout << "The graph contains a cycle. Topological sorting is not possible." << endl;
		return;
	}
	cout << "=== Kahn algorithm ===" << endl;
	for (int node : sortedOrder) {
		cout << node << " ";
	}
	cout << endl;
	for (int node : sortedOrder) {
		for (int node1 : adj[node]) {
			cout << node << " -> " << node1 << endl;
		}
		cout << endl;
	}
	cout << endl;
}










ostream& operator << (ostream& out, const gtn& s)
{
	PRINT_PARAM(cout, s.id);
	int counter = 1;
	for (Connection cn : s.Connections) {
		cout << "=== Connection " << counter << " ===" << endl;
		cout << "Compression station 1: " << endl;
		cout << cn.cs1;
		cout << "Pipeline:" << endl;
		cout << cn.pl;
		cout << "Compression station 2:" << endl;
		cout << cn.cs2;
		counter++;
	}
	return out;
}

istream& operator >> (istream& in, gtn& s)
{
	s.Connections.clear();
	int num;
	vector<int> diameters = { 500, 700, 1000, 1400 };
	vector<Pipeline*> PipelineMask;
	for (const Pipeline& pl : s.Pipelines) {
		pl.resetGTN();
	}
	while (1) {
		PipelineMask.clear();
		try {
			uint64_t max;
			max = GetMax<Compressedstation, std::set>(s.Compressedstations);
			cout << "Type id of compression station ";
			Compressedstation& cs1 = Select<Compressedstation, std::set>(s.Compressedstations, max + 1);
			max = GetMax<Compressedstation, std::set>(s.Compressedstations);
			cout << "Type id of compression station ";
			Compressedstation& cs2 = Select<Compressedstation, std::set>(s.Compressedstations, max + 1);


			cout << "Type diameter [500, 700, 1000, 1400]: ";
			num = GetCorrectNumberAllowed(diameters);
			for (auto it = s.Pipelines.begin(); it != s.Pipelines.end(); ++it) {
				if (CheckByDiametr<Pipeline>(*it, num)) {
					Pipeline& pl_ = const_cast<Pipeline&>(*it);
					if (pl_.InGTN == false) {
						cout << *it;
						PipelineMask.push_back(&pl_);
					}
				}
			}
			if (!PipelineMask.empty()) {
				try {
					max = GetMax<Pipeline*, std::vector>(PipelineMask);
					Pipeline* pl_ = Select<Pipeline*, std::vector>(PipelineMask, max + 1);
					Pipeline& pl = *pl_;
					pl.cs1 = cs1.id;
					pl.cs2 = cs2.id;
					pl.InGTN = true;
					Connection cn(cs1, pl, cs2);
					s.Connections.push_back(cn);
				}
				catch (const runtime_error& e) {
					cerr << e.what() << endl;
					break;
				}
			}
			else {
				cerr << "Not found" << endl;
				cout << "=== Create new ===" << endl;
				Pipeline pl;
				cin >> pl;
				s.Pipelines.insert(pl);
				cout << "Restart creating of this connection." << endl;
				continue;
			}
			cout << "Next? (yes - 1, no - 0): ";
			int num = GetCorrectNumber(0, 1);
			if (num == 0) {
				break;
			}
		}
		catch (const std::runtime_error& e) {
			cout << e.what() << endl;
			break;
		}
	}
	return in;
}