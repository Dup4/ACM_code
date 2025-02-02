#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1010
int n, m;
char s[N][N];
int pre[N][N], f[N][N], g[N][N];

int ok(int x, int y) {
    int fa = pre[x][y];
    int fa2 = pre[fa][y];
    int fa3 = pre[fa2][y];
    if (fa && fa2 && x - fa == fa - fa2 && x - fa <= fa2 - fa3) {
        return 3 * (x - fa);
    }
    return 0;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s[i] + 1);
        }
        for (int j = 1; j <= m; ++j) {
            pre[1][j] = 0;
            for (int i = 2; i <= n; ++i) {
                if (s[i][j] == s[i - 1][j]) {
                    pre[i][j] = pre[i - 1][j];
                } else {
                    pre[i][j] = i - 1;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 2; j <= m; ++j) {
                f[i][j] = (s[i][j] == s[i][j - 1]);
                f[i][j] += f[i - 1][j];
            }
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int len = ok(i, j);
                if (len) {
                    g[i][j] = 1;
                    if (f[i][j] - f[i - len][j] == len) {
                        g[i][j] = g[i][j - 1] + 1;
                    }
                } else {
                    g[i][j] = 0;
                }
                res += g[i][j];
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
