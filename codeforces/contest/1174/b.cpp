#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

bool same() {
    for (int i = 2; i <= n; ++i) {
        if ((a[i] & 1) != (a[i - 1] & 1)) {
            return false;
        }
    }
    return true;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        if (!same()) {
            sort(a + 1, a + 1 + n);
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", a[i], " \n"[i == n]);
        }
    }
    return 0;
}
