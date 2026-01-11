#include "gtn.h"
#include "Mainthread.h"

#include <iostream>
#include <stack>
#include <algorithm>

#include <vector>

#include "utils.h"
using namespace std;

int gtn::MaxID = 0;


gtn::gtn(set<Pipeline>& pl, set<Compressedstation>& cs) : Pipelines(pl), Compressedstations(cs) {
	id = MaxID++;
}









void gtn::topologicalSortDFS(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
	visited[u] = true;

	for (int v : adj[u]) {
		if (!visited[v]) {
			topologicalSortDFS(v, adj, visited, st);
		}
	}

	st.push(u);
}

vector<int> gtn::topologicalSort(int V, vector<vector<int>>& adj) {
	stack<int> st;
	vector<bool> visited(V, false);

	for (int i = 0; i < V; ++i) {
		if (!visited[i]) {
			topologicalSortDFS(i, adj, visited, st);
		}
	}

	vector<int> result;
	while (!st.empty()) {
		result.push_back(st.top());
		st.pop();
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
		s.insert(i.cs1.getId());
		s.insert(i.cs2.getId());
	}
	int V = s.size();
	vector<vector<int>> adj(V);
	for (Connection& i : Connections) {
		adj[i.cs1.getId()].push_back(i.cs2.getId());
	}

	vector<int> sortedOrder = topologicalSort(V, adj);

	cout << "=== DFS ===" << endl;
	for (int node : sortedOrder) {
		cout << node << " ";
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
					pl.cs1 = cs1.getId();
					pl.cs2 = cs2.getId();
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