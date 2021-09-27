#include <iostream>
#include <fstream>
#include <map>

using namespace std;

void reversedInsertionSort(int mainArray[], char addArray[], int n) {
	int mainKey, addKey, j;
	for (int i = 1; i < n; i++) {
		mainKey = mainArray[i];
		addKey = addArray[i];
		j = i - 1;
		while (j >= 0 && mainArray[j] < mainKey) {
			mainArray[j + 1] = mainArray[j];
			addArray[j + 1] = addArray[j];
			j -= 1;
		}
		mainArray[j + 1] = mainKey;
		addArray[j + 1] = addKey;
	}
}

int main() {
	ifstream fin("aurora.in");
	ofstream fout("aurora.out");

	string str;
	fin >> str;

	const int N = 26;
	char alphabet[N] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
						 'i', 'j', 'k', 'l', 'm', 'n',
						 'o', 'p', 'q', 'r', 's', 't',
						 'u', 'v', 'w', 'x', 'y', 'z' };

	int weights[N];
	for (int i = 0; i < N; i++) {
		fin >> weights[i];
	}

	int counter[N];
	for (int i = 0; i < N; i++) {
		counter[i] = 0;
	}

	reversedInsertionSort(weights, alphabet, N);

	map<char, int> defMap;
	for (int i = 0; i < N; i++) {
		defMap[alphabet[i]] = i;
	}
	
	for (int i = 0; i < str.size(); i++) {
		counter[defMap[str[i]]]++;
	}

	for (int i = 0; i < N; i++) {
		if (counter[i] > 1) {
			fout << alphabet[i];
		}
	}

	for (int i = 0; i < N; i++) {
		if (counter[i] == 1) {
			fout << alphabet[i];
		} else if (counter[i] > 2) {
			for (int j = 0; j < counter[i] - 2; j++) {
				fout << alphabet[i];
			}
		}
		counter[i]--;
	}

	for (int i = N - 1; i >= 0; i--) {
		if (counter[i] > 0) {
			fout << alphabet[i];
		}
	}

	fin.close();
	fout.close();
}
