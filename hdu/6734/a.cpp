#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        while (n % 2 == 0) n /= 2;
        while (n % 5 == 0) n /= 5;
        puts(n == 1 ? "No" : "Yes");
    }
    return 0;
}
