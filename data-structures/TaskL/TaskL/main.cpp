#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, k;
	fin >> n >> k;

	int* nums = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> nums[i];
	}

	int minValue, minIndex = -1;
	for (int start = 0; start < n - k + 1; start++) {
		int end = start + k;
		if (minIndex < start) {
			minValue = nums[start];
			for (int i = start + 1; i < end; i++) {
				if (nums[i] <= minValue) {
					minValue = nums[i];
					minIndex = i;
				}
			}
		} else if (nums[end - 1] <= minValue) {
			minValue = nums[end - 1];
			minIndex = end - 1;
		}
		fout << minValue << " ";
	}

	fin.close();
	fout.close();
}
