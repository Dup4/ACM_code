#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
inline int rd() {
    int x;
    cin >> x;
    return x;
}
template <class T>
inline void rd(T &x) {
    cin >> x;
}
template <class T>
inline void rd(vector<T> &vec) {
    for (auto &it : vec) cin >> it;
}
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    pt(args...);
}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    pt(args...);
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
// head
constexpr int N = 3e2 + 10;
int n, m, a[N][N], vis[N][N];
char s[N];
int Move[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m || a[x][y] != 1 || vis[x][y])
        return false;
    return true;
}
void dfs(int x, int y) {
    vis[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + Move[i][0];
        int ny = y + Move[i][1];
        if (ok(nx, ny)) {
            dfs(nx, ny);
        }
    }
}
void run() {
    memset(a, 0, sizeof a);
    for (int i = 1; i <= n; ++i) {
        cin >> (s + 1);
        for (int j = 1; j <= m; ++j) {
            a[i][j] = s[j] - '0';
        }
    }
    int q = rd();
    while (q--) {
        int x[2], y[2];
        cin >> x[0] >> y[0] >> x[1] >> y[1];
        for (int i = x[0]; i <= x[1]; ++i)
            for (int j = y[0]; j <= y[1]; ++j) a[i][j] = 1;
        memset(vis, 0, sizeof vis);
        int res = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (a[i][j] == 1 && vis[i][j] == 0) {
                    ++res;
                    dfs(i, j);
                }
        pt(res);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
