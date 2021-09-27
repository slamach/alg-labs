#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

bool BFS(const vector<vector<int>>& graph, int start, vector<bool>& visited, vector<int>& parts) {
	visited[start] = true;
	queue<int> visitQueue;
	visitQueue.push(start);
	if (parts[start] == 0) {
		parts[start] = 1;
	}

	while (!visitQueue.empty()) {
		int current = visitQueue.front();
		visitQueue.pop();

		for (int neighbour : graph[current]) {
			if (!visited[neighbour]) {
				visited[neighbour] = true;
				visitQueue.push(neighbour);
				if (parts[current] == 1) {
					parts[neighbour] = 2;
				} else {
					parts[neighbour] = 1;
				}
			} else {
				if (parts[current] == parts[neighbour]) {
					return false;
				}
			}
		}
	}
	return true;
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, m;
	fin >> n >> m;

	vector<vector<int>> graph(n);
	for (int i = 0; i < m; i++) {
		int first, second;
		fin >> first >> second;
		graph[first - 1].push_back(second - 1);
		graph[second - 1].push_back(first - 1);
	}

	vector<bool> visited(n, false);
	vector<int> parts(n, 0);
	bool state = true;
	for (int i = 0; i < n; i++) {
		state = BFS(graph, i, visited, parts);
		if (!state) {
			break;
		}
	}

	if (state) {
		fout << "YES";
	} else {
		fout << "NO";
	}

	fin.close();
	fout.close();
}
