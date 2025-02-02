#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define fi first
#define se second
#define N 1010
int n, m, q, s;
char G[N][N];
pll a[27][N][N], base[N][N], num[N][N];

//每一块的贡献 = 原图的贡献 - 覆盖区域的原图的贡献 + 覆盖区域的贡献
void add(pll a[][N], int id, int x1, int y1, int x2, int y2, ll f) {
    a[x2 + 1][y2 + 1].fi += f;
    a[x2 + 1][y2 + 1].se += f * id;
    a[x1][y1].fi += f;
    a[x1][y1].se += f * id;
    a[x1][y2 + 1].fi -= f;
    a[x1][y2 + 1].se -= f * id;
    a[x2 + 1][y1].fi -= f;
    a[x2 + 1][y1].se -= f * id;
}

//前缀和
pll query(pll a[][N][N], int n, int x1, int y1, int x2, int y2) {
    pll res = pll(0, 0);
    for (int i = 1; i <= n; ++i) {
        res.fi += a[i][x2][y2].fi + a[i][x1 - 1][y1 - 1].fi - a[i][x1 - 1][y2].fi - a[i][x2][y1 - 1].fi;
        res.se += a[i][x2][y2].se + a[i][x1 - 1][y1 - 1].se - a[i][x1 - 1][y2].se - a[i][x2][y1 - 1].se;
    }
    return res;
}

//后缀和
pll query2(pll a[][N][N], int n, int x1, int y1, int x2, int y2) {
    pll res = pll(0, 0);
    for (int i = 26; i >= n; --i) {
        res.fi += a[i][x2][y2].fi + a[i][x1 - 1][y1 - 1].fi - a[i][x1 - 1][y2].fi - a[i][x2][y1 - 1].fi;
        res.se += a[i][x2][y2].se + a[i][x1 - 1][y1 - 1].se - a[i][x1 - 1][y2].se - a[i][x2][y1 - 1].se;
    }
    return res;
}

pll query3(pll a[][N], int x1, int y1, int x2, int y2) {
    pll res = pll(0, 0);
    res.fi = a[x2][y2].fi + a[x1 - 1][y1 - 1].fi - a[x1 - 1][y2].fi - a[x2][y1 - 1].fi;
    res.se = a[x2][y2].se + a[x1 - 1][y1 - 1].se - a[x1 - 1][y2].se - a[x2][y1 - 1].se;
    return res;
}

void addpre(pll a[][N], int x, int y) {
    a[x][y].fi += a[x - 1][y].fi + a[x][y - 1].fi - a[x - 1][y - 1].fi;
    a[x][y].se += a[x - 1][y].se + a[x][y - 1].se - a[x - 1][y - 1].se;
}

struct qnode {
    int x[2], y[2];
    char c[10];
    ll tot;
    qnode() {}
    void scan() {
        scanf("%d%d%d%d %s", x, y, x + 1, y + 1, c);
        add(a[c[0] - 'a' + 1], c[0] - 'a' + 1, x[0], y[0], x[1], y[1], 1);
        add(num, c[0] - 'a' + 1, x[0], y[0], x[1], y[1], 1);
        tot = 0;
    }
} qrr[300010];

void add(pll &x, pll &y) {
    x.fi += y.fi;
    x.se += y.se;
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &q, &s) != EOF) {
        memset(a, 0, sizeof a);
        memset(base, 0, sizeof base);
        memset(num, 0, sizeof num);
        for (int i = 1; i <= n; ++i) scanf("%s", G[i] + 1);
        for (int i = 1; i <= q; ++i) {
            qrr[i].scan();
        }
        for (int i = 1; i <= 26; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= m; ++k) {
                    addpre(a[i], j, k);
                }
            }
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= m; ++k) {
                    addpre(a[i], j, k);
                }
            }
        }
        ll tot = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int id = G[i][j] - 'a' + 1;
                pll l = query(a, id - 1, i, j, i, j);
                pll r = query2(a, id + 1, i, j, i, j);
                base[i][j].fi = 1ll * id * l.fi - l.se + r.se - 1ll * id * r.fi;
                tot += base[i][j].fi;
                addpre(base, i, j);
            }
        }
        for (int i = 1; i <= q; ++i) {
            int x[2] = {qrr[i].x[0], qrr[i].x[1]};
            int y[2] = {qrr[i].y[0], qrr[i].y[1]};
            int id = qrr[i].c[0] - 'a' + 1;
            ll &now = qrr[i].tot;
            now = tot - query3(base, x[0], y[0], x[1], y[1]).fi;
            pll l = query(a, id - 1, x[0], y[0], x[1], y[1]);
            pll r = query2(a, id + 1, x[0], y[0], x[1], y[1]);
            now += 1ll * id * l.fi - l.se - 1ll * id * r.fi + r.se;
        }

        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                addpre(num, i, j);
                int id = G[i][j] - 'a' + 1;
                a[id][i][j].fi += q - num[i][j].fi;
                a[id][i][j].se += 1ll * id * (q - num[i][j].fi);
            }
        }
        for (int i = 1; i <= 26; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= m; ++k) {
                    addpre(a[i], j, k);
                }
            }
        }

        ll Min = 1e18;
        int pos = -1;
        for (int i = 1; i <= q; ++i) {
            int x[2] = {qrr[i].x[0], qrr[i].x[1]};
            int y[2] = {qrr[i].y[0], qrr[i].y[1]};
            int id = qrr[i].c[0] - 'a' + 1;
            ll &now = qrr[i].tot;
            pll l = query(a, id - 1, x[0], y[0], x[1], y[1]);
            pll r = query2(a, id + 1, x[0], y[0], x[1], y[1]);
            now += 1ll * id * l.fi - l.se - 1ll * id * r.fi + r.se;
            if (now < Min) {
                Min = now;
                pos = i;
            }
        }

        printf("%lld %d\n", Min, pos);
    }
    return 0;
}
