#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("agro.in");
	ofstream fout("agro.out");

	int n;
	fin >> n;

	int* array = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> array[i];
	}

	int repeats = 1;
	int currentStart = 0;
	int currentEnd = 0;
	int maxStart = 0;
	int maxEnd = 0;

	for (int i = 1; i < n; i++) {
		if (array[i] == array[i - 1]) {
			repeats += 1;
			if (repeats == 3) {
				if ((currentEnd - currentStart) > (maxEnd - maxStart)) {
					maxStart = currentStart;
					maxEnd = currentEnd;
				}
				currentStart = i - 1;
				repeats = 2;
			}
		} else {
			repeats = 1;
		}
		currentEnd = i;
	}
	if ((currentEnd - currentStart) > (maxEnd - maxStart)) {
		maxStart = currentStart;
		maxEnd = currentEnd;
	}

	cout << (maxStart + 1) << " " << (maxEnd + 1);

	fin.close();
	fout.close();
}
