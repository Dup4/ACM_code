#include <bits/stdc++.h>
using namespace std;
namespace IO {
const int S = (1 << 20) + 5;
// Input Correlation
char buf[S], *H, *T;
inline char Get() {
    if (H == T)
        T = (H = buf) + fread(buf, 1, S, stdin);
    if (H == T)
        return -1;
    return *H++;
}
inline int read() {
    int x = 0, fg = 1;
    char c = Get();
    while (!isdigit(c) && c != '-') c = Get();
    if (c == '-')
        fg = -1, c = Get();
    while (isdigit(c)) x = x * 10 + c - '0', c = Get();
    return x * fg;
}
}  // namespace IO
using namespace IO;
const int N = 1e5 + 10;
const int M = 25;
int n, m, V[N];
struct Edge {
    int v, nx;
} e[N << 1];
int h[N];
inline void addedge(int u, int v) {
    e[++*h] = {v, h[u]};
    h[u] = *h;
}
struct LCA {
    int F[N << 1], P[N];
    struct RMQ {
        int Min[N << 1][M];
        int mm[N << 1], rmq[N << 1];
        void init(int n) {
            mm[0] = -1;
            for (int i = 1; i <= n; ++i) {
                mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
                Min[i][0] = i;
            }
            for (int j = 1; j <= mm[n]; ++j) {
                for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                    Min[i][j] = rmq[Min[i][j - 1]] < rmq[Min[i + (1 << (j - 1))][j - 1]]
                                        ? Min[i][j - 1]
                                        : Min[i + (1 << (j - 1))][j - 1];
                }
            }
        }
        int queryMin(int x, int y) {
            if (x > y)
                swap(x, y);
            int k = mm[y - x + 1];
            return rmq[Min[x][k]] <= rmq[Min[y - (1 << k) + 1][k]] ? Min[x][k] : Min[y - (1 << k) + 1][k];
        }
    } st;
    int dep[N];
    void DFS(int u, int pre) {
        F[++*F] = u;
        st.rmq[*F] = dep[u];
        P[u] = *F;
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].v;
            if (v == pre)
                continue;
            dep[v] = dep[u] + 1;
            DFS(v, u);
            F[++*F] = u;
            st.rmq[*F] = dep[u];
        }
    }
    void init(int root, int node_num) {
        *F = 0;
        dep[root] = 0;
        DFS(root, root);
        st.init(2 * node_num - 1);
    }
    inline int query(int u, int v) {
        return F[st.queryMin(P[u], P[v])];
    }
    inline int dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[query(u, v)];
    }
} lca;

struct SEG {
    struct node {
        int ls, rs, sum;
    } t[N << 6];
    int rt[N << 1], tot;
    inline void init() {
        tot = 0;
    }
    void update(int &now, int l, int r, int pos, int v) {
        if (!now)
            now = ++tot, t[now].sum = t[now].ls = t[now].rs = 0;
        t[now].sum += v;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, l, mid, pos, v);
        else
            update(t[now].rs, mid + 1, r, pos, v);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (!id)
            return 0;
        if (l >= ql && r <= qr)
            return t[id].sum;
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res += query(t[id].ls, l, mid, ql, qr);
        if (qr > mid)
            res += query(t[id].rs, mid + 1, r, ql, qr);
        return res;
    }
} seg;

namespace PD {
int rt, sum, fa[N], sze[N], f[N], vis[N];
void getrt(int u, int pre) {
    sze[u] = 1;
    f[u] = 0;
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
        if (vis[v] || v == pre)
            continue;
        getrt(v, u);
        sze[u] += sze[v];
        f[u] = max(f[u], sze[v]);
    }
    f[u] = max(f[u], sum - sze[u]);
    if (f[u] < f[rt])
        rt = u;
}
void build(int u, int ff) {
    vis[u] = 1;
    fa[u] = ff;
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].v;
        if (vis[v])
            continue;
        sum = f[0] = sze[v];
        rt = 0;
        getrt(v, u);
        build(rt, u);
    }
}
void init() {
    for (int i = 0; i <= n; ++i) vis[i] = 0;
    sum = f[0] = n;
    rt = 0;
    getrt(1, 0);
    build(rt, 0);
}
void modify(int x, int w) {
    seg.update(seg.rt[x], 0, n, 0, w);
    for (int i = x; fa[i]; i = fa[i]) {
        int dis = lca.dis(x, fa[i]);
        seg.update(seg.rt[fa[i]], 0, n, dis, w);
        seg.update(seg.rt[i + n], 0, n, dis, w);
    }
}
int query(int x, int K) {
    int ret = seg.query(seg.rt[x], 0, n, 0, K);
    for (int i = x; fa[i]; i = fa[i]) {
        int dis = lca.dis(x, fa[i]);
        if (dis > K)
            continue;
        ret += seg.query(seg.rt[fa[i]], 0, n, 0, K - dis);
        ret -= seg.query(seg.rt[i + n], 0, n, 0, K - dis);
    }
    return ret;
}
};  // namespace PD

int main() {
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i) V[i] = read();
    h[0] = 0;
    for (int i = 1; i < n; ++i) {
        int u = read(), v = read();
        addedge(u, v);
        addedge(v, u);
    }
    lca.init(1, n);
    seg.init();
    PD::init();
    for (int i = 1; i <= n; ++i) PD::modify(i, V[i]);
    int ans = 0;
    while (m--) {
        int opt = read(), x = read(), y = read();
        x ^= ans, y ^= ans;
        if (opt == 0)
            printf("%d\n", ans = PD::query(x, y));
        else
            PD::modify(x, y - V[x]), V[x] = y;
    }
    return 0;
}
