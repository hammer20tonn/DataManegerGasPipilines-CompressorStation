#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stack>
#include "Pipeline.h"

#include "Compressedstation.h"


struct Connection {
	const Compressedstation& cs1;
	const Pipeline& pl;
	const Compressedstation& cs2;

	Connection(const Compressedstation& s1, const Pipeline& p, const Compressedstation& s2)
		: cs1(s1), pl(p), cs2(s2) {
	}
};


class gtn
{
private:
	void topologicalSortDFS(int u, std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::stack<int>& st);
	std::vector<int> topologicalSort(int V, std::vector<std::vector<int>>&adj);
public:
	int id;
	static int MaxID;
	std::vector<Connection> Connections;
	std::set<Pipeline>& Pipelines;
	std::set<Compressedstation>& Compressedstations;
	bool operator<(const gtn& other) const {
		return id < other.id;
	}
	void getTopologicalSort();
	friend std::ostream& operator << (std::ostream& out, const gtn& s);
	friend std::istream& operator >> (std::istream& in, gtn& s);
	gtn() = delete;
	gtn(std::set<Pipeline>& pl, std::set<Compressedstation>& cs);
};

