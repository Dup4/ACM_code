#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        sort(a + 1, a + 1 + n);
        n = unique(a + 1, a + 1 + n) - a - 1;
    }
    return 0;
}
