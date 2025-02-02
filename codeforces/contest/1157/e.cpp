#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        multiset<int> se;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            se.insert(x);
        }
        for (int i = 1; i <= n; ++i) {
            int up = n - a[i];
            auto pos = se.lower_bound(up);
            if (pos == se.end()) {
                pos = se.begin();
                (a[i] += *pos) %= n;
                se.erase(pos);
            } else {
                (a[i] += *pos) %= n;
                se.erase(pos);
            }
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", a[i], " \n"[i == n]);
        }
    }
    return 0;
}
