#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            if (a[i] >= 0) {
                a[i] = -a[i] - 1;
            }
        }
        if (n & 1) {
            int Min = *min_element(a + 1, a + 1 + n);
            for (int i = 1; i <= n; ++i) {
                if (a[i] == Min) {
                    a[i] = -a[i] - 1;
                    break;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", a[i], " \n"[i == n]);
        }
    }
    return 0;
}
