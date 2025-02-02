#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m, p, id, pos[N];
struct Edge {
    int v, nx, w;
} e[N * 8];
int h[N];
inline void addedge(int u, int v, int w) {
    e[++*h] = {v, h[u], w};
    h[u] = *h;
}
struct SEG {
    struct node {
        int ls, rs;
        node() {
            ls = rs = 0;
        }
    } t[N << 3];
    int rt_in, rt_out;
    inline void init() {
        rt_in = rt_out = 0;
    }
    inline int newnode() {
        ++id;
        t[id] = node();
        return id;
    }
    void build(int &rt, int l, int r, int op) {
        rt = newnode();
        if (l == r) {
            if (op == 1) {
                pos[l] = rt;
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(t[rt].ls, l, mid, op);
        build(t[rt].rs, mid + 1, r, op);
        // in_tree
        if (op == 1) {
            addedge(rt, t[rt].ls, 0);
            addedge(rt, t[rt].rs, 0);
        } else {  // out_tree
            addedge(t[rt].ls, rt, 0);
            addedge(t[rt].rs, rt, 0);
        }
    }
    void add(int id, int l, int r, int ql, int qr, int u, int w, int op) {
        if (l >= ql && r <= qr) {
            //连出去
            if (op == 1) {
                addedge(id, u, w);
            } else {
                addedge(u, id, w);
            }
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            add(t[id].ls, l, mid, ql, qr, u, w, op);
        if (qr > mid)
            add(t[id].rs, mid + 1, r, ql, qr, u, w, op);
    }
    void addleaf(int rt_in, int rt_out, int l, int r) {
        if (l == r) {
            addedge(rt_in, rt_out, 0);
            addedge(rt_out, rt_in, 0);
            return;
        }
        int mid = (l + r) >> 1;
        addleaf(t[rt_in].ls, t[rt_out].ls, l, mid);
        addleaf(t[rt_in].rs, t[rt_out].rs, mid + 1, r);
    }
} seg;

void add(int a, int b, int c, int d) {
    int p1 = ++id, p2 = ++id;
    seg.add(seg.rt_out, 1, n, a, b, p1, 0, 1);
    addedge(p1, p2, 1);
    seg.add(seg.rt_in, 1, n, c, d, p2, 0, 0);
}

struct Dijkstra {
    struct node {
        int u, w;
        node() {}
        node(int u, int w) : u(u), w(w) {}
        bool operator<(const node &other) const {
            return w > other.w;
        }
    };
    int dis[N];
    bool used[N];
    void gao() {
        for (int i = 1; i <= id; ++i) {
            dis[i] = INF;
            used[i] = 0;
        }
        dis[pos[p]] = 0;
        priority_queue<node> pq;
        pq.push(node(pos[p], 0));
        while (!pq.empty()) {
            int u = pq.top().u;
            pq.pop();
            if (used[u])
                continue;
            used[u] = 1;
            for (int i = h[u]; i; i = e[i].nx) {
                int v = e[i].v, w = e[i].w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    pq.push(node(v, dis[v]));
                }
            }
        }
        for (int i = 1; i <= n; ++i) printf("%d\n", dis[pos[i]]);
    }
} dij;

int main() {
    while (scanf("%d%d%d", &n, &m, &p) != EOF) {
        memset(h, 0, sizeof h);
        seg.init();
        seg.build(seg.rt_in, 1, n, 1);
        seg.build(seg.rt_out, 1, n, 0);
        seg.addleaf(seg.rt_in, seg.rt_out, 1, n);
        for (int i = 1, a, b, c, d; i <= m; ++i) {
            scanf("%d%d%d%d", &a, &b, &c, &d);
            add(a, b, c, d);
            add(c, d, a, b);
        }
        dij.gao();
    }
    return 0;
}
