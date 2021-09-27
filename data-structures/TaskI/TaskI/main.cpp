#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

queue<int>* places;
int* place_on_table;

bool cars_comp(int const& a, int const& b) {
	if (!places[a].empty() && !places[b].empty()) {
		return places[a].front() < places[b].front();
	} else {
		return !places[a].empty() && places[b].empty();
	}
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

void siftdown(int* heap, int n, int i) {
	int j = i;
	if (left(i) < n && cars_comp(heap[j], heap[left(i)])) {
		j = left(i);
	}
	if (right(i) < n && cars_comp(heap[j], heap[right(i)])) {
		j = right(i);
	}
	if (i != j) {
		swap(place_on_table[heap[i]], place_on_table[heap[j]]);
		swap(heap[i], heap[j]);
		siftdown(heap, n, j);
	}
}

void siftup(int* heap, int i) {
	while (i > 0 && cars_comp(heap[parent(i)], heap[i])) {
		swap(place_on_table[heap[i]], place_on_table[heap[parent(i)]]);
		swap(heap[i], heap[parent(i)]);
		i = parent(i);
	}
}

void heap_pop(int* heap, int n) {
	place_on_table[heap[n - 1]] = 1;
	heap[0] = heap[n-- - 1];
	siftdown(heap, n, 0);
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, k, p;
	fin >> n >> k >> p;

	places = new queue<int>[n];
	place_on_table = new int[n];

	int* cars = new int[p];
	for (int i = 0; i < p; i++) {
		int temp;
		fin >> temp;;
		cars[i] = temp - 1;
		places[cars[i]].push(i);
	}

	int* on_table = new int[k];
	int count_table = 0;
	int result = 0;
	for (int i = 0; i < p; i++) {
		if (place_on_table[cars[i]] != 0) {
			places[cars[i]].pop();
			siftup(on_table, place_on_table[cars[i]] - 1);
			continue;
		}
		if (count_table < k) {
			on_table[count_table++] = cars[i];
			places[cars[i]].pop();
			place_on_table[cars[i]] = count_table;
			siftup(on_table, count_table - 1);
		} else {
			int max_car = on_table[0];
			place_on_table[max_car] = 0;
			heap_pop(on_table, count_table);

			on_table[k - 1] = cars[i];
			places[cars[i]].pop();
			place_on_table[cars[i]] = k;
			siftup(on_table, count_table - 1);
		}
		result++;
	}

	fout << result;

	fin.close();
	fout.close();
}
