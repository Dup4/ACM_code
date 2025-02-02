#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n;
ll h[N][2], f[N][2];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &h[i][0]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &h[i][1]);
        }
        memset(f, 0, sizeof f);
        f[1][0] = h[1][0];
        f[1][1] = h[1][1];
        ll res = 0;
        for (int i = 2; i <= n; ++i) {
            f[i][0] = h[i][0] + f[i - 1][1];
            f[i][1] = h[i][1] + f[i - 1][0];
            if (i > 2) {
                f[i][0] = max(f[i][0], h[i][0] + max(f[i - 2][0], f[i - 2][1]));
                f[i][1] = max(f[i][1], h[i][1] + max(f[i - 2][0], f[i - 2][1]));
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 2; ++j) {
                res = max(res, f[i][j]);
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
