#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
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
#define pii pair<int, int>
#define fi first
#define se second
int n, r, a[N], b[N];
int f[N];
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    vector<pii> up, down;
    for (int i = 1; i <= n; ++i) {
        if (b[i] >= 0)
            up.push_back(pii(a[i], b[i]));
        else
            down.push_back(pii(a[i], b[i]));
    }
    sort(up.begin(), up.end(), [](pii x, pii y) {
        if (x.fi != y.fi)
            return x.fi < y.fi;
        return x.se > y.se;
    });
    int num = 0;
    for (auto it : up) {
        if (r >= it.fi) {
            r += it.se;
            ++num;
        }
    }
    sort(down.begin(), down.end(), [](pii x, pii y) {
        return x.fi + x.se > y.fi + y.se;
    });
    memset(f, -0x3f, sizeof f);
    f[r] = num;
    for (auto it : down) {
        for (int j = 0; j < N; ++j) {
            if ((j + it.se) >= 0 && j >= it.fi) {
                chmax(f[j + it.se], f[j] + 1);
            }
        }
    }
    cout << *max_element(&f[0], &f[N]) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n >> r) run();
    return 0;
}
