#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
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
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
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
constexpr int N = 3e3 + 10;
int n, m, K, a[N][N], S[N][N], up[2][10];
ll res;

inline int get(int x1, int x2, int y1, int y2) {
    if (x1 > x2 || y1 > y2)
        return 0;
    x1 = max(x1, 1);
    y1 = max(y1, 1);
    return S[x2][y2] - S[x1 - 1][y2] - S[x2][y1 - 1] + S[x1 - 1][y1 - 1];
}

void gao(int x1, int x2, int y1, int y2) {
    if (x1 > x2 || y1 > y2)
        return;
    if (x1 == x2 && y1 == y2) {
        res += a[x1][y1] == K;
        return;
    }
    if (x2 - x1 > y2 - y1) {
        int mid = (x1 + x2) >> 1;
        gao(x1, mid, y1, y2);
        gao(mid + 1, x2, y1, y2);
        for (int i = y1; i <= y2; ++i) {
            for (int k = 0; k <= K + 1; ++k) up[0][k] = mid, up[1][k] = mid + 1;
            for (int j = y2; j >= i; --j) {
                for (int k = 0; k <= K + 1; ++k) {
                    while (up[0][k] >= x1 && get(up[0][k], mid, i, j) < k) --up[0][k];
                    while (up[1][k] <= x2 && get(mid + 1, up[1][k], i, j) < k) ++up[1][k];
                }
                for (int k = 0; k <= K; ++k) {
                    if (get(up[0][k], mid, i, j) == k && get(mid + 1, up[1][K - k], i, j) == K - k) {
                        res += 1ll * (up[0][k] - up[0][k + 1]) * (up[1][K - k + 1] - up[1][K - k]);
                    }
                }
            }
        }
    } else {
        int mid = (y1 + y2) >> 1;
        gao(x1, x2, y1, mid);
        gao(x1, x2, mid + 1, y2);
        for (int i = x1; i <= x2; ++i) {
            for (int k = 0; k <= K + 1; ++k) up[0][k] = mid, up[1][k] = mid + 1;
            for (int j = x2; j >= i; --j) {
                for (int k = 0; k <= K + 1; ++k) {
                    while (up[0][k] >= y1 && get(i, j, up[0][k], mid) < k) --up[0][k];
                    while (up[1][k] <= y2 && get(i, j, mid + 1, up[1][k]) < k) ++up[1][k];
                }
                for (int k = 0; k <= K; ++k) {
                    if (get(i, j, up[0][k], mid) == k && get(i, j, mid + 1, up[1][K - k]) == K - k) {
                        res += 1ll * (up[0][k] - up[0][k + 1]) * (up[1][K - k + 1] - up[1][K - k]);
                    }
                }
            }
        }
    }
}

void run() {
    for (int i = 1; i <= n; ++i) {
        static string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            a[i][j + 1] = s[j] - '0';
            S[i][j + 1] = S[i - 1][j + 1] + S[i][j] - S[i - 1][j] + a[i][j + 1];
        }
    }
    res = 0;
    gao(1, n, 1, m);
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> K) run();
    return 0;
}
