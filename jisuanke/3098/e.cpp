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
typedef long long ll;
const int N = 5e5 + 10;
const int M = 3e4 + 10;
int n, D, a[N], pri[M], check[M], mu[M], anc[N], deep[N], vis[N], md[N], hson[N];
ll res, F[N];
vector<vector<int>> G, dvec, fac;

void sieve() {
    fac.clear();
    fac.resize(M);
    for (int i = 1; i < M; ++i)
        for (int j = i; j < M; j += i) fac[j].push_back(i);
    *pri = 0;
    mu[1] = 1;
    for (int i = 2; i < M; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (i * pri[j] >= M)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
            else
                mu[i * pri[j]] = -mu[i];
        }
    }
}

void pre(int u) {
    for (auto &v : G[u])
        if (v != anc[u]) {
            deep[v] = deep[u] + 1;
            anc[v] = u;
            pre(v);
        }
    for (auto &it : fac[a[u]]) dvec[it].push_back(u);
}

int tmp[N << 2], *f[N], *id = tmp;
void getdeep(int u) {
    md[u] = deep[u];
    hson[u] = 0;
    for (auto &v : G[u]) {
        deep[v] = deep[u] + 1;
        getdeep(v);
        if (!hson[u] || md[v] > md[hson[u]])
            hson[u] = v;
    }
    md[u] = md[hson[u]] + 1;
}

void dfs(int u) {
    if (hson[u]) {
        int v = hson[u];
        f[v] = f[u] + 1;
        dfs(v);
    }
    f[u][0] = 1;
    if (md[u] > D) {
        res += f[u][D];
    }
    for (auto &v : G[u])
        if (v != hson[u]) {
            f[v] = id;
            id += md[v] + 1;
            dfs(v);
            for (int i = 0; i < md[v]; ++i) {
                if (md[u] > D - i - 1 && D - i - 1 >= 0) {
                    res += 1ll * f[u][D - i - 1] * f[v][i];
                }
            }
            for (int i = 0; i < md[v]; ++i) f[u][i + 1] += f[v][i];
        }
}

inline void gao(vector<int> &vec, int x) {
    res = 0;
    for (auto &u : vec) G[u].clear(), vis[u] = x;
    for (auto &u : vec) {
        if (vis[anc[u]] == x) {
            G[anc[u]].push_back(u);
        } else {
            deep[u] = 0;
            getdeep(u);
            id = tmp;
            f[u] = id;
            id += md[u] + 1;
            dfs(u);
        }
    }
}

int main() {
    sieve();
    int _T;
    _T = read();
    for (int kase = 1; kase <= _T; ++kase) {
        printf("Case #%d: ", kase);
        n = read();
        D = read();
        G.clear();
        G.resize(n + 1);
        dvec.clear();
        dvec.resize(M);
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n; ++i) a[i] = read();
        for (int i = 1, u, v; i < n; ++i) {
            u = read();
            v = read();
            G[u].push_back(v);
            G[v].push_back(u);
        }
        anc[1] = 0;
        deep[1] = 0;
        pre(1);
        for (int i = 1; i <= 30000; ++i)
            if (mu[i]) {
                gao(dvec[i], i);
                F[i] = res;
            }
        res = F[1];
        for (int i = 1; i <= 30000; ++i)
            if (mu[i])
                res -= 1ll * mu[i] * F[i];
        printf("%lld\n", res * 2);
    }
    return 0;
}
