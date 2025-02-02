#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/extc++.h>
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;
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
constexpr int N = 2e5 + 10;
int n, pre[N];
char s[N];

inline ll calc(ll l, ll r, ll k) {
    if (l > r)
        return 0;
    return (r / k) - ((l - 1) / k);
}

void run() {
    n = strlen(s + 1);
    pre[0] = 0;
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + (s[i] == '1');
    }
    vector<int> one;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '1') {
            one.push_back(i);
        }
    }
    if (one.empty()) {
        return pt(0);
    }
    one.push_back(n + 1);
    ll res = 0;
    int S = 280;
    gp_hash_table<int, int> mp;
    for (int i = 1; i <= S; ++i) {
        mp.clear();
        mp[0] = 1;
        for (int j = 1; j <= n; ++j) {
            int val = j - i * pre[j];
            res += mp[val];
            ++mp[val];
        }
    }
    int sze = one.size() - 1;
    for (int i = 1; i <= n / S; ++i) {
        int nx = 0;
        for (int j = 1; j <= n; ++j) {
            while (nx < sze && pre[one[nx]] - pre[j - 1] < i) ++nx;
            if (nx == sze)
                break;
            int delta = one[nx + 1] - one[nx] - 1;
            int l = max(i * S + 1, one[nx] - j + 1);
            int r = one[nx] - j + 1 + delta;
            res += calc(l, r, i);
        }
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> (s + 1)) run();
    return 0;
}
