#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n;
	fin >> n;

	deque<string> firstQ;
	deque<string> secondQ;

	for (int i = 0; i < n; i++) {
		char operation;
		fin >> operation;

		if (operation == '-') {
			fout << firstQ.front() << endl;
			firstQ.pop_front();
		} else {
			string num;
			fin >> num;
			if (operation == '+') {
				secondQ.push_back(num);
			} else {
				secondQ.push_front(num);
			}
		}

		int sizeDiff = firstQ.size() - secondQ.size();
		if (sizeDiff == 2) {
			secondQ.push_front(firstQ.back());
			firstQ.pop_back();
		} else if (sizeDiff == -1) {
			firstQ.push_back(secondQ.front());
			secondQ.pop_front();
		}
	}

	fin.close();
	fout.close();
}
