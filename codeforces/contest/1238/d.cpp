#include <bits/stdc++.h>
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << " ";
    pt(args...);
}
template <class T>
inline void pt(const T &s) {
    cout << s << "\n";
}
template <class T>
inline void pt(const vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
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
constexpr int N = 3e5 + 10;
int n;
char s[N];
vector<int> A, B;
void run() {
    cin >> (s + 1);
    A.clear();
    B.clear();
    for (int i = 1; i <= n; ++i) {
        if (s[i] == 'A')
            A.push_back(i);
        else
            B.push_back(i);
    }
    ll res = 0;
    for (int i = 1; i < n; ++i) {
        if (s[i] == 'A') {
            auto nx = upper_bound(B.begin(), B.end(), i);
            if (nx == B.end()) {
                res += (n - i);
            } else if (*nx == i + 1) {
                auto nnx = upper_bound(A.begin(), A.end(), *nx);
                if (nnx != A.end()) {
                    res += n - *nnx + 1;
                }
            } else {
                res += n - i - 1;
            }
        } else {
            auto nx = upper_bound(A.begin(), A.end(), i);
            if (nx == A.end()) {
                res += n - i;
            } else if (*nx == i + 1) {
                auto nnx = upper_bound(B.begin(), B.end(), *nx);
                if (nnx != B.end()) {
                    res += n - *nnx + 1;
                }
            } else {
                res += n - i - 1;
            }
        }
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
