#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool compareStrs(string str1, string str2) {
	return str2 + str1 < str1 + str2;
}

int main() {
	ifstream fin("number.in");
	ofstream fout("number.out");

	vector<string> answer;

	while (true) {
		string current;
		fin >> current;
		if (fin.eof()) {
			break;
		}

		if (answer.size() == 0) {
			answer.push_back(current);
			continue;
		}

		for (int i = answer.size() - 1; i >= 0; i--) {
			if (compareStrs(answer[i], current)) {
				answer.insert(answer.begin() + i + 1, current);
				break;
			}
			if (i == 0) {
				answer.insert(answer.begin(), current);
			}
		}
	}

	for (int i = 0; i < answer.size(); i++) {
		fout << answer[i];
	}

	fin.close();
	fout.close();
}
