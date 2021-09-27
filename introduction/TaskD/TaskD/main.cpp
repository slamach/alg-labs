#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("chaos.in");
	ofstream fout("chaos.out");

	int a, b, c, d, k;
	fin >> a >> b >> c >> d >> k;

	int temp;
	int lastResult = -1;
	for (int i = 0; i < k; i++) {
		temp = a * b - c;
		if (temp <= 0) {
			a = 0;
			break;
		}
		a = (temp > d) ? d : temp;
		if (a == lastResult) {
			break;
		}
		lastResult = a;
	}

	fout << a;

	fin.close();
	fout.close();
}
