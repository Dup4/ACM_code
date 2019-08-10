#include <bits/stdc++.h>

using namespace std;

bool prime(int x) {
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	for (int i = 50000; ; ++i) {
		if (prime(i)) {
			cout << i << endl;
			return 0;
		}
	}
	return 0;
}
