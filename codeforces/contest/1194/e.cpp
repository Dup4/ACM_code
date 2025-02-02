#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 50100
#define pii pair<int, int>
#define fi first
#define se second
int n;
int x[N][2], y[N][2];
int b[N], c[N];
vector<vector<pii>> vec, add, del;

void Hash() {
    sort(b + 1, b + 1 + b[0]);
    sort(c + 1, c + 1 + c[0]);
    b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
    c[0] = unique(c + 1, c + 1 + c[0]) - c - 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 2; ++j) {
            x[i][j] = lower_bound(b + 1, b + 1 + b[0], x[i][j]) - b;
            y[i][j] = lower_bound(c + 1, c + 1 + c[0], y[i][j]) - c;
        }
    }
}

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) {
            a[x] += v;
        }
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            res += a[x];
        }
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;

ll C(int n) {
    return 1ll * n * (n - 1) / 2;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        b[0] = 0;
        c[0] = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d%d", x[i], y[i], x[i] + 1, y[i] + 1);
            b[++b[0]] = x[i][0];
            b[++b[0]] = x[i][1];
            c[++c[0]] = y[i][0];
            c[++c[0]] = y[i][1];
        }
        Hash();
        vec.clear();
        vec.resize(N);
        add.clear();
        add.resize(N);
        del.clear();
        del.resize(N);
        for (int i = 1; i <= n; ++i) {
            if (y[i][0] == y[i][1]) {
                if (x[i][0] > x[i][1])
                    swap(x[i][0], x[i][1]);
                vec[y[i][0]].push_back(pii(x[i][0], x[i][1]));
            } else {
                if (y[i][0] > y[i][1])
                    swap(y[i][0], y[i][1]);
                add[y[i][0]].push_back(pii(x[i][0], y[i][1] + 1));
            }
        }
        ll res = 0;
        bit.init();
        for (int i = 1; i <= c[0]; ++i) {
            for (auto it : del[i]) {
                bit.update(it.fi, -1);
            }
            for (auto it : add[i]) {
                bit.update(it.fi, 1);
                del[it.se].push_back(pii(it.fi, it.fi));
            }
            for (auto it : vec[i]) {
                for (int j = i + 1; j <= c[0]; ++j) {
                    for (auto it2 : del[j]) {
                        bit.update(it2.fi, -1);
                    }
                    for (auto it2 : vec[j]) {
                        int l = max(it.fi, it2.fi), r = min(it.se, it2.se);
                        res += C(bit.query(l, r));
                    }
                }
                for (int j = i + 1; j <= c[0]; ++j) {
                    for (auto it2 : del[j]) {
                        bit.update(it2.fi, 1);
                    }
                }
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
