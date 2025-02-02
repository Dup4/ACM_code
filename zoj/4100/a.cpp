#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, q;
ll fee, se;
ll f(ll x) {
    return 1ll * x * (x - 1) / 2;
}

struct SEG {
    struct node {
        ll sze, sum[2];
        node() {
            sze = 0;
            sum[0] = sum[1] = 0;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sze = sze + other.sze;
            res.sum[0] = sum[0] + other.sum[0];
            res.sum[1] = sum[1] + other.sum[1];
            return res;
        }
    } t[N << 2];
    ll a, b, res, tot, used;
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int pos, int val) {
        if (l == r) {
            t[id].sze += val;
            t[id].sum[0] = 1ll * l * t[id].sze;
            t[id].sum[1] = 1ll * f(l) * t[id].sze;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, val);
        else
            update(id << 1 | 1, mid + 1, r, pos, val);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, ll need) {
        if (l == r) {
            int ql = 0, qr = t[id].sze, ans = 0;
            while (qr - ql >= 0) {
                int mid = (ql + qr) >> 1;
                tot = f(1ll * l * mid + a);
                used = f(l) * mid + b;
                if (need <= tot - used) {
                    qr = mid - 1;
                    ans = mid;
                } else {
                    ql = mid + 1;
                }
            }
            res += ans;
            return;
        }
        int mid = (l + r) >> 1;
        tot = f(t[id << 1 | 1].sum[0] + a);
        used = t[id << 1 | 1].sum[1] + b;
        if (need <= tot - used) {
            query(id << 1 | 1, mid + 1, r, need);
        } else {
            a += t[id << 1 | 1].sum[0];
            b += t[id << 1 | 1].sum[1];
            res += t[id << 1 | 1].sze;
            query(id << 1, l, mid, need);
        }
    }
} seg;

struct UF {
    int fa[N], p[N], e[N];
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
            p[i] = 1;
            e[i] = 0;
        }
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x != y) {
            seg.update(1, 1, n, p[x], -1);
            seg.update(1, 1, n, p[y], -1);
            fee -= f(p[x]) + f(p[y]) - e[x] - e[y];
            if (p[x] > p[y]) {
                swap(x, y);
            }
            fa[x] = y;
            p[y] += p[x];
            e[y] += e[x] + 1;
            seg.update(1, 1, n, p[y], 1);
            --se;
            fee += f(p[y]) - e[y];
        } else {
            ++e[x];
            --fee;
        }
    }
} uf;

void init() {
    seg.build(1, 1, n);
    uf.init(n);
    seg.update(1, 1, n, 1, n);
    se = n;
    fee = 0;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        init();
        int op, x, y;
        ll k;
        ll res[2];
        while (q--) {
            scanf("%d", &op);
            switch (op) {
                case 1:
                    scanf("%d%d", &x, &y);
                    uf.merge(x, y);
                    break;
                case 2:
                    scanf("%lld", &k);
                    res[0] = max(1ll, 1ll * se - k);
                    if (k - fee <= 0) {
                        res[1] = se;
                    } else {
                        seg.a = seg.b = seg.res = 0;
                        seg.query(1, 1, n, k - fee);
                        res[1] = se - seg.res + 1;
                    }
                    printf("%lld %lld\n", res[0], res[1]);
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
