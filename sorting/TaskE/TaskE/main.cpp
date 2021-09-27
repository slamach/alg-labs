#include <iostream>
#include <fstream>

using namespace std;

bool isPlaced(int n, int array[], int minDist, int k) {
	int last = 0;
	int placed = 1;

	for (int i = 1; i < n; i++) {
		if (array[i] - array[last] >= minDist) {
			last = i;
			placed++;
			if (placed >= k) {
				break;
			}
		}
	}
	
	return placed >= k;
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, k;
	fin >> n >> k;

	int* array = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> array[i];
	}

	int l = 1;
	int r = array[n - 1] - array[0];
	while (l < r - 1) {
		int m = (l + r) / 2;
		if (isPlaced(n, array, m, k)) {
			l = m;
		} else {
			r = m;
		}
	}

	if (isPlaced(n, array, r, k)) {
		fout << r;
	} else {
		fout << l;
	}

	fin.close();
	fout.close();
}
