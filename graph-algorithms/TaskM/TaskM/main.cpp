#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int INF = 100000000;

struct Dot {
	int ind;
	int x;
	int y;
	int path;
	bool used;

	Dot* lowerX;
	Dot* higherX;
	Dot* lowerY;
	Dot* higherY;

	Dot(int ind, int x, int y, int path, bool used) {
		this->ind = ind;
		this->x = x;
		this->y = y;
		this->path = path;
		this->used = used;
		this->lowerX = nullptr;
		this->higherX = nullptr;
		this->lowerY = nullptr;
		this->higherY = nullptr;
	}
};

bool dotComp(Dot* a, Dot* b) {
	if (!a->used && !b->used) {
		return a->path > b->path;
	}
	return a->used && !b->used;
}

int parent(int i) {
	return (i - 1) / 2;
}

int left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}

void siftdown(Dot** heap, int n, int i) {
	int j = i;
	if (left(i) < n && dotComp(heap[j], heap[left(i)])) {
		j = left(i);
	}
	if (right(i) < n && dotComp(heap[j], heap[right(i)])) {
		j = right(i);
	}
	if (i != j) {
		swap(heap[i]->ind, heap[j]->ind);
		swap(heap[i], heap[j]);
		siftdown(heap, n, j);
	}
}

void siftup(Dot** heap, int i) {
	while (i > 0 && dotComp(heap[parent(i)], heap[i])) {
		swap(heap[i]->ind, heap[parent(i)]->ind);
		swap(heap[i], heap[parent(i)]);
		i = parent(i);
	}
}

int getTime(char cell) {
	switch (cell) {
		case '.':
			return 1;
		case 'W':
			return 2;
		case '#':
			return -1;
	}
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int x, y, startX, startY, endX, endY;
	fin >> x >> y >> startX >> startY >> endX >> endY;
	startX--;
	startY--;
	endX--;
	endY--;

	Dot** dotHeap = new Dot*[1000000];
	int heapCounter = 0;

	vector<vector<char>> matrix;
	matrix.resize(x);
	for (int i = 0; i < x; i++) {
		matrix[i].resize(y);
		for (int j = 0; j < y; j++) {
			fin >> matrix[i][j];
		}
	}

	Dot* startDot = nullptr;
	Dot* endDot = nullptr;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			dotHeap[heapCounter] = new Dot(heapCounter, i, j, INF, false);
			if (getTime(matrix[i][j]) == -1) {
				dotHeap[heapCounter]->used = true;
			}
			if (i == startX && j == startY) {
				startDot = dotHeap[heapCounter];
			}
			if (i == endX && j == endY) {
				endDot = dotHeap[heapCounter];
			}
			if (j > 0) {
				dotHeap[heapCounter]->lowerY = dotHeap[heapCounter - 1];
				dotHeap[heapCounter - 1]->higherY = dotHeap[heapCounter];
			}
			if (i > 0) {
				dotHeap[heapCounter]->lowerX = dotHeap[heapCounter - y];
				dotHeap[heapCounter - y]->higherX = dotHeap[heapCounter];
			}
			heapCounter++;
		}
	}
	startDot->path = 0;
	siftup(dotHeap, startDot->ind);

	for (int i = heapCounter / 2 - 1; i >= 0; i--) {
		siftdown(dotHeap, heapCounter, i);
	}

	while (true) {
		Dot* minDot = dotHeap[0];
		if (minDot->used) {
			break;
		}
		minDot->used = true;
		siftdown(dotHeap, heapCounter, minDot->ind);

		if (minDot->x > 0 && !minDot->lowerX->used) {
			minDot->lowerX->path = min(minDot->lowerX->path, minDot->path + getTime(matrix[minDot->x - 1][minDot->y]));
			siftup(dotHeap, minDot->lowerX->ind);
		}
		if (minDot->x < x - 1 && !minDot->higherX->used) {
			minDot->higherX->path = min(minDot->higherX->path, minDot->path + getTime(matrix[minDot->x + 1][minDot->y]));
			siftup(dotHeap, minDot->higherX->ind);
		}
		if (minDot->y > 0 && !minDot->lowerY->used) {
			minDot->lowerY->path = min(minDot->lowerY->path, minDot->path + getTime(matrix[minDot->x][minDot->y - 1]));
			siftup(dotHeap, minDot->lowerY->ind);
		}
		if (minDot->y < y - 1 && !minDot->higherY->used) {
			minDot->higherY->path = min(minDot->higherY->path, minDot->path + getTime(matrix[minDot->x][minDot->y + 1]));
			siftup(dotHeap, minDot->higherY->ind);
		}
	}

	int result = endDot->path;
	if (result == INF) {
		result = -1;
	}
	fout << result << endl;

	if (result != -1) {
		vector<char> path;
		Dot* prevDot = endDot;

		while (prevDot->x != startX || prevDot->y != startY) {
			if (prevDot->lowerX && prevDot->path - getTime(matrix[prevDot->x][prevDot->y]) == prevDot->lowerX->path) {
				path.push_back('S');
				prevDot = prevDot->lowerX;
			} else if (prevDot->higherX && prevDot->path - getTime(matrix[prevDot->x][prevDot->y]) == prevDot->higherX->path) {
				path.push_back('N');
				prevDot = prevDot->higherX;
			} else if (prevDot->lowerY && prevDot->path - getTime(matrix[prevDot->x][prevDot->y]) == prevDot->lowerY->path) {
				path.push_back('E');
				prevDot = prevDot->lowerY;
			} else if (prevDot->higherY && prevDot->path - getTime(matrix[prevDot->x][prevDot->y]) == prevDot->higherY->path) {
				path.push_back('W');
				prevDot = prevDot->higherY;
			}
		}

		for (int i = path.size() - 1; i >= 0; i--) {
			fout << path[i];
		}
	}
	
	fin.close();
	fout.close();
}
