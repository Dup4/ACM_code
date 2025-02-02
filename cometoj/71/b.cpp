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
constexpr int N = 2e6 + 10;
int n, m, r, c;
char s[N];
vector<vector<int>> A;
inline int id(int x, int y) {
    return x * m + y;
}
int fa[N], sze[N], v[N];
int find(int x) {
    return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        if (sze[fx] > sze[fy])
            swap(x, y);
        fa[fx] = fy;
        sze[fy] += sze[fx];
        v[fy] += v[fx];
    }
}
void run() {
    A.clear();
    A.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            fa[id(i, j)] = 0;
            sze[id(i, j)] = 1;
            v[id(i, j)] = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        A[i].clear();
        A[i].resize(m + 1);
        cin >> (s + 1);
        for (int j = 1; j <= m; ++j) {
            A[i][j] = (s[j] - '0');
        }
    }
    for (int i = 1; i <= n; ++i) {
        cin >> (s + 1);
        for (int j = 1; j <= m; ++j) {
            A[i][j] ^= (s[j] - '0');
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            v[id(i, j)] = A[i][j];
            if (j - c >= 1) {
                merge(id(i, j), id(i, j - c));
            }
            if (i - r >= 1) {
                merge(id(i, j), id(i - r, j));
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (fa[id(i, j)] == 0 && v[id(i, j)] & 1)
                return pt("No");
        }
    pt("Yes");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T;
    cin >> _T;
    while (cin >> n >> m >> r >> c) run();
    return 0;
}
