#include <bits/stdc++.h>
using namespace std;
 
#define N 1000010
#define ll long long
ll x[2], a, b;
char s[N];
ll mod;
int len;
 
ll eular(ll n) {
    ll ans = n;
    for (int i = 2; 1ll * i * i <= n; ++i) {
        if (n % i == 0) {
            ans -= ans / i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) ans -= ans / n;
    return ans;
}
 
struct node {
    ll a[2][2];
    node() {
        memset(a, 0, sizeof a);
    }
    node operator * (const node &other) const {
        node res = node();
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j] % mod) % mod;
        return res;
    }
}base;
 
node qmod(node base, ll n) {
    node res = node();
    res.a[0][0] = x[1], res.a[0][1] = x[0];
    while (n) {
        if (n & 1) res = res * base;
        base = base * base;
        n >>= 1; 
    }
    return res;
}
 
int gcd() {
    ll x = 0;
    for (int i = 1; i <= len; ++i) {
        x = x * 10 + s[i] - '0';
        x %= mod;
    }
    for (int i = 2; 1ll * i * i <= mod; ++i) {
        if (mod % i == 0 && x % i == 0) {
            return 0;
        }
    }
    return 1;
}
 
int main() {
    while (scanf("%lld%lld%lld%lld", x, x + 1, &a, &b) != EOF) {
        scanf("%s%lld", s + 1, &mod);
        len = strlen(s + 1);
        base = node();
        base.a[0][0] = a;
        base.a[1][0] = b;
        base.a[0][1] = 1;
        if (len <= 10) {
            ll n = 0;
            for (int i = 1; i <= len; ++i) {
                n = n * 10 + s[i] - '0';
            }
			--n;
            printf("%lld\n", qmod(base, n).a[0][0]);
        } else {
            ll n = 0;
            ll Phi = eular(mod);
            for (int i = 1; i <= len; ++i) {
                n = n * 10 + s[i] - '0';
                n %= Phi;
            }
            n = (n + Phi - 1) % Phi;
			cout << n << endl;
			printf("%lld\n", qmod(base, n).a[0][0]);
        }
    }
    return 0;
}

