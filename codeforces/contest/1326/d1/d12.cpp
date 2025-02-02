#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
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
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
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
constexpr int N = 1e6 + 10;
int n;
char s[N], t[N];

struct ExKMP {
    int Next[N];
    int extend[N];
    void get_Next(char *s) {
        int lens = strlen(s + 1), p = 1, pos;
        Next[1] = lens;
        while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
        Next[pos = 2] = p - 1;
        for (int i = 3; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            if (len + i < p + 1)
                Next[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
                p = i + (Next[pos = i] = j) - 1;
            }
        }
    }
    void work(char *s, char *t) {
        get_Next(t);
        int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
        while (p <= lent && s[p] == t[p]) ++p;
        p = extend[pos = 1] = p - 1;
        for (int i = 2; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            if (len + i < p + 1)
                extend[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= lens && j <= lent && t[j + 1] == s[i + j]) ++j;
                p = i + (extend[pos = i] = j) - 1;
            }
        }
    }
} exkmp;

struct Manacher {
    int len, l;
    char Ma[N << 1];
    int Mp[N << 1];
    void work(char *s) {
        len = strlen(s);
        l = 0;
        Ma[l++] = '$';
        Ma[l++] = '#';
        for (int i = 0; i < len; ++i) {
            Ma[l++] = s[i];
            Ma[l++] = '#';
        }
        Ma[l] = 0;
        int mx = 0, id = 0;
        for (int i = 0; i < l; ++i) {
            Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
            while (Ma[i + Mp[i]] == Ma[i - Mp[i]]) Mp[i]++;
            if (i + Mp[i] > mx) {
                mx = i + Mp[i];
                id = i;
            }
        }
    }
    bool check(int l, int r) {
        --l, --r;
        int il = (l + 1) * 2, ir = (r + 1) * 2;
        int mid = (il + ir) / 2;
        int len = (r - l + 2) / 2;
        return (Mp[mid] / 2) >= len;
    }
} man;

int ok[N], cnt;

void up(int i, int n, int opt) {
    int j = n - i + 1;
    if (t[i] != t[j])
        cnt += opt;
}

void print(int x) {
    memset(ok, 0, sizeof(ok[0]) * (n + 5));
    cnt = 0;
    int del = n - x;
    t[x + 1] = 0;
    for (int i = del + 1, j = 1; i <= n; ++i, ++j) {
        t[j] = s[i];
    }
    for (int i = 1; i <= x / 2; ++i) up(i, x, 1);
    if (!cnt) {
        cout << t + 1 << endl;
        return;
    }
    if (!del)
        return;
    for (int i = del, j = 1; i < n; ++i, ++j) {
        up(j, x, -1);
        t[j] = s[j];
        up(j, x, 1);
        if (!cnt) {
            cout << t + 1 << endl;
            return;
        }
    }
    assert(0);
}

void run() {
    cin >> (s + 1);
    n = strlen(s + 1);
    man.work(s + 1);
    for (int i = 1; i <= n; ++i) t[i] = s[n - i + 1];
    t[n + 1] = 0;
    int res = 0;
    exkmp.work(s, t);
    int pre = exkmp.extend[1];
    chmax(res, pre * 2);
    chmin(res, n);
    int add = 0;
    for (int i = pre + 1; i <= n - pre; ++i) {
        if (man.check(pre + 1, i)) {
            chmax(add, i - pre);
        }
        if (man.check(i, n - pre)) {
            chmax(add, n - pre - i + 1);
        }
    }
    //	pt(res + add);
    print(res + add);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
