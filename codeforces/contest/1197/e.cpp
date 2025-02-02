#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define N 400010
#define pii pair<ll, ll>
#define fi first
#define se second
const ll p = 1e9 + 7;
int n, tot;
pii a[N];
int b[N];
ll c[N], d[N];

struct SEG {
    struct node {
        ll Min, sum;
        node() {
            sum = 0;
            Min = INFLL;
        }
        node(ll Min, ll sum) : Min(Min), sum(sum) {}
        node operator+(const node &other) const {
            node res = node();
            if (Min == other.Min) {
                res.Min = Min;
                res.sum = (sum + other.sum) % p;
            } else if (Min < other.Min) {
                res.Min = Min;
                res.sum = sum;
            } else {
                res.Min = other.Min;
                res.sum = other.sum;
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int pos, node x) {
        if (l == r) {
            t[id] = t[id] + x;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, x);
        else
            update(id << 1 | 1, mid + 1, r, pos, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res + t[id];
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

int id(int x) {
    return lower_bound(b + 1, b + 1 + tot, x) - b;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        tot = 0;
        for (int i = 1; i <= n; ++i) scanf("%lld%lld", &a[i].fi, &a[i].se);
        for (int i = 1; i <= n; ++i) {
            b[++tot] = a[i].fi;
            b[++tot] = a[i].se;
        }
        sort(b + 1, b + 1 + tot);
        tot = unique(b + 1, b + 1 + tot) - b - 1;
        sort(a + 1, a + 1 + n, [](pii x, pii y) {
            if (x.se != y.se)
                return x.se < y.se;
            return x.fi > y.fi;
        });
        ll Min = INFLL;
        ll res = 0;
        seg.build(1, 1, tot);
        for (int i = 1; i <= n; ++i) {
            seg.res = SEG::node();
            seg.query(1, 1, tot, 1, id(a[i].se));
            if (seg.res.Min == INFLL) {
                seg.res = SEG::node(-a[i].fi + a[i].se, 1);
                seg.update(1, 1, tot, id(a[i].fi), seg.res);
                c[i] = a[i].se;
                d[i] = 1;
            } else {
                c[i] = a[i].se + seg.res.Min;
                d[i] = seg.res.sum;
                seg.res.Min += -a[i].fi + a[i].se;
                seg.update(1, 1, tot, id(a[i].fi), seg.res);
            }
            if (a[i].fi > a[n].se) {
                Min = min(Min, c[i]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (a[i].fi > a[n].se && c[i] == Min) {
                res = (res + d[i]) % p;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
