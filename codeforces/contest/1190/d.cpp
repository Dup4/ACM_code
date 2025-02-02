#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 400010
int n, m, b[N], c[N];
vector<vector<int>> vec;
struct node {
    int x, y;
    node() {}
    void scan() {
        scanf("%d%d", &x, &y);
        b[++b[0]] = x;
        c[++c[0]] = y;
    }
    bool operator<(const node &other) const {
        return x < other.x;
    }
} a[N];
void Hash() {
    sort(b + 1, b + 1 + b[0]);
    sort(c + 1, c + 1 + c[0]);
    b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
    c[0] = unique(c + 1, c + 1 + c[0]) - c - 1;
    for (int i = 1; i <= n; ++i) {
        a[i].x = lower_bound(b + 1, b + 1 + b[0], a[i].x) - b;
        a[i].y = lower_bound(c + 1, c + 1 + c[0], a[i].y) - c;
    }
}
struct SEG {
    int a[N << 2];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int id, int l, int r, int pos, int v) {
        if (l == r) {
            a[id] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        a[id] = a[id << 1] + a[id << 1 | 1];
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (ql > qr)
            return 0;
        if (l >= ql && r <= qr) {
            return a[id];
        }
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res += query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            res += query(id << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
} seg;

int main() {
    while (scanf("%d", &n) != EOF) {
        b[0] = 0;
        c[0] = 0;
        for (int i = 1; i <= n; ++i) {
            a[i].scan();
        }
        Hash();
        sort(a + 1, a + 1 + n);
        vec.clear();
        vec.resize(c[0] + 1);
        for (int i = 1; i <= n; ++i) {
            vec[a[i].y].push_back(a[i].x);
        }
        m = b[0];
        seg.init();
        ll res = 0;
        for (int i = c[0]; i >= 1; --i) {
            if (!vec[i].empty()) {
                for (int j = 0, sze = (int)vec[i].size(); j < sze; ++j) {
                    ll L = seg.query(1, 1, m, 1, vec[i][j] - 1);
                    ll R = seg.query(1, 1, m, vec[i][j] + 1, (j < sze - 1 ? vec[i][j + 1] - 1 : m));
                    res += (L + 1) * (R + 1);
                    seg.update(1, 1, m, vec[i][j], 1);
                }
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
