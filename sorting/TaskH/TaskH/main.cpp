#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("shop.in");
	ofstream fout("shop.out");

	int n, k;
	fin >> n >> k;

	int* array = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> array[i];
	}
	sort(array, array + n);

	int sum = 0;
	int count = 1;
	for (int i = n - 1; i >= 0; i--) {
		if (count % k != 0) {
			sum += array[i];
		}
		count++;
	}

	fout << sum;

	fin.close();
	fout.close();
}
