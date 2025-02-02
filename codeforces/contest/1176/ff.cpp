#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
#define pii pair<int, int>
#define fi first
#define se second
int n, m;
ll f[N][10];

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i) {
            vector<pii> vec[4], tmp;
            scanf("%d", &m);
            for (int j = 1, c, d; j <= m; ++j) {
                scanf("%d%d", &c, &d);
                vec[c].push_back(pii(d, j));
            }
            for (int j = 1; j <= 3; ++j) {
                sort(vec[j].begin(), vec[j].end());
            }
            // 一张
            if (vec[3].size() >= 1) {
                ll Max = vec[3].back().fi;
                for (int j = 1; j < 9; ++j) {
                    f[i][j] = max(f[i][j], f[i - 1][j - 1] + Max);
                }
                f[i][0] = max(f[i][0], f[i - 1][9] + 2ll * Max);
            }
            // 二张
            if (vec[1].size() >= 1 && vec[2].size() >= 1) {
                tmp.clear();
                tmp.push_back(vec[1].back());
                tmp.push_back(vec[2].back());
                sort(tmp.begin(), tmp.end(), [&](pii x, pii y) {
                    return x.fi > y.fi;
                });
                ll tot = tmp[0].fi + tmp[1].fi;
                for (int j = 0; j < 8; ++j) {
                    f[i][j + 2] = max(f[i][j + 2], f[i - 1][j] + tot);
                }
                if (tmp[0].se > tmp[1].se) {
                    swap(tmp[0], tmp[1]);
                }
                f[i][0] = max(f[i][0], f[i - 1][8] + tot + tmp[1].fi);
                f[i][1] = max(f[i][1], f[i - 1][9] + tot + tmp[0].fi);
            }
            //三张
            if (vec[1].size() >= 3) {
                tmp.clear();
                for (int j = 1; j <= 3; ++j) {
                    tmp.push_back(vec[1].end()[-j]);
                }
                sort(tmp.begin(), tmp.end(), [&](pii x, pii y) {
                    return x.se < y.se;
                });
                ll tot = 0;
                for (int j = 0; j < 3; ++j) {
                    tot += tmp[j].fi;
                }
                for (int j = 0; j < 7; ++j) {
                    f[i][j + 3] = max(f[i][j + 3], f[i - 1][j] + tot);
                }
                f[i][0] = max(f[i][0], f[i - 1][7] + tot + tmp[2].fi);
                f[i][1] = max(f[i][1], f[i - 1][8] + tot + tmp[1].fi);
                f[i][2] = max(f[i][2], f[i - 1][9] + tot + tmp[0].fi);
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 10; ++j) {
                printf("%d %d %lld\n", i, j, f[i][j]);
            }
        }
        ll res = 0;
        for (int i = 0; i < 10; ++i) {
            res = max(res, f[n][i]);
        }
        printf("%lld\n", res);
    }
    return 0;
}
