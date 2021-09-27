#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int DFS(const vector<vector<int>>& graph, int start, vector<bool>& visited, vector<bool>& cache) {
	cache[start] = true;
	for (int neighbour : graph[start]) {
		if (visited[neighbour]) {
			return 0;
		}
		if (cache[neighbour]) {
			return 1;
		}
		return DFS(graph, neighbour, visited, cache);
	}
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n;
	fin >> n;

	vector<vector<int>> graph;
	graph.resize(n);
	for (int i = 0; i < n; i++) {
		int temp;
		fin >> temp;
		graph[i].push_back(temp - 1);
	}

	int result = 0;
	vector<bool> visited;
	visited.resize(n, false);
	vector<bool> cache;
	for (int i = 0; i < n; i++) {
		cache.clear();
		cache.resize(n, false);
		result += DFS(graph, i, visited, cache);
		for (int i = 0; i < cache.size(); i++) {
			if (cache[i]) {
				visited[i] = true;
			}
		}
	}

	fout << result;

	fin.close();
	fout.close();
}
