#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, M = 20, INF = 0x3f3f3f3f;
int n, q, rt;

struct Graph {
    struct E {
        int to, nx, w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 1; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

struct LCA {
    int fa[N][M], dis[N][M];
    int deep[N];
    void bfs(int rt) {
        queue<int> q;
        deep[rt] = 0;
        fa[rt][0] = rt;
        dis[rt][0] = 0;
        q.emplace(rt);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 1; i < M; ++i) {
                dis[u][i] = dis[u][i - 1] + dis[fa[u][i - 1]][i - 1];
                fa[u][i] = fa[fa[u][i - 1]][i - 1];
            }
            for (int i = G.h[u]; ~i; i = G.e[i].nx) {
                int v = G.e[i].to, w = G.e[i].w;
                if (v == fa[u][0])
                    continue;
                deep[v] = deep[u] + 1;
                fa[v][0] = u;
                dis[v][0] = w;
                q.emplace(v);
            }
        }
    }
    void init(int rt) {
        bfs(rt);
    }
    int querylca(int u, int v) {
        if (deep[u] > deep[v])
            swap(u, v);
        for (int det = deep[v] - deep[u], i = 0; det; det >>= 1, ++i) {
            if (det & 1)
                v = fa[v][i];
        }
        if (u == v)
            return u;
        for (int i = M - 1; i >= 0; --i) {
            if (fa[u][i] == fa[v][i])
                continue;
            u = fa[u][i];
            v = fa[v][i];
        }
        return fa[u][0];
    }
    int querydis(int u, int v) {
        if (deep[u] > deep[v])
            swap(u, v);
        int res = 0;
        for (int det = deep[v] - deep[u], i = 0; det; det >>= 1, ++i) {
            if (det & 1) {
                res += dis[v][i];
                v = fa[v][i];
            }
        }
        if (u == v)
            return res;
        for (int i = M - 1; i >= 0; --i) {
            if (fa[u][i] == fa[v][i])
                continue;
            res += dis[u][i] + dis[v][i];
            u = fa[u][i], v = fa[v][i];
        }
        return res + dis[u][0] + dis[v][0];
    }
} lca;

int main() {
    while (scanf("%d%d%d", &n, &q, &rt) != EOF) {
        G.init(n);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G.addedge(u, v);
            G.addedge(v, u);
        }
        lca.init(rt);
        for (int i = 1, u, v; i <= q; ++i) {
            scanf("%d%d", &u, &v);
            printf("%d\n", lca.querylca(u, v));
        }
    }
    return 0;
}
