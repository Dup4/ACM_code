#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("%d\n", (n & 1) ? 1 : 2);
    }
    return 0;
}
