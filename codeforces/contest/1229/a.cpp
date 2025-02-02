#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using ll = long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
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
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
template <class T>
inline void out(vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
}
inline ll gcd(ll a, ll b) {
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
constexpr int N = 1e4 + 10;
int n, vis[N];
pLL a[N];
void run() {
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; ++i) cin >> a[i].fi;
    for (int i = 1; i <= n; ++i) cin >> a[i].se;
    sort(a + 1, a + 1 + n, [&](pLL x, pLL y) {
        return x.fi < y.fi;
    });
    ll res = 0;
    for (int i = n, j; i >= 1;) {
        if (vis[i]) {
            --i;
            continue;
        }
        for (j = i - 1; j >= 1; --j) {
            if (a[j].fi != a[j + 1].fi)
                break;
        }
        ++j;
        if (i == j) {
            --i;
            continue;
        }
        for (int k = j; k <= i; ++k) vis[k] = 1;
        for (int k = j - 1; k >= 1; --k) {
            if ((a[k].fi & a[i].fi) == a[k].fi)
                vis[k] = 1;
        }
        i = j - 1;
    }
    for (int i = 1; i <= n; ++i) res += a[i].se * vis[i];
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
