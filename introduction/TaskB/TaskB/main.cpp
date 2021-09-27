#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	stack<char> mainStack;

	int animalCounter = 0;
	int trapCounter = -1;
	stack<int> animalStack;
	stack<int> trapStack;

	string data;
	fin >> data;
	const int N = data.size() / 2;
	int* scheme = new int[N];

	for (char letter : data) {
		if (islower(letter)) {
			animalStack.push(++animalCounter);
		} else {
			trapStack.push(++trapCounter);
		}

		if (mainStack.empty()) {
			mainStack.push(letter);
		} else {
			if ((isupper(mainStack.top()) && islower(letter) || islower(mainStack.top()) && isupper(letter))
				&& tolower(mainStack.top()) == tolower(letter)) {
				scheme[trapStack.top()] = animalStack.top();
				animalStack.pop();
				trapStack.pop();
				mainStack.pop();
			}= else {
				mainStack.push(letter);
			}
		}
	}

	if (mainStack.empty()) {
		fout << "Possible" << endl;
		for (int i = 0; i < N; i++) {
			fout << scheme[i] << " ";
		}
	} else {
		fout << "Impossible" << endl;
	}

	fin.close();
	fout.close();
}
