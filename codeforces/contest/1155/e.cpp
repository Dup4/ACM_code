#include <bits/stdc++.h>
using namespace std;

#define ll long long
int p = 1000003;
ll a[20];
ll fac[20];
ll inv[20], inv2[1000003];
ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < 20; ++i) {
        fac[i] = (fac[i - 1] * i) % p;
    }
    inv[19] = qmod(fac[19], p - 2);
    for (int i = 19; i >= 1; --i) {
        inv[i - 1] = (inv[i] * i) % p;
    }
    inv2[1] = 1;
    for (int i = 2; i < p; ++i) {
        inv2[i] = inv2[p % i] * (p - p / i) % p;
    }

    for (int i = 0; i <= 10; ++i) {
        printf("? %d\n", i);
        fflush(stdout);
        scanf("%lld", a + i);
        if (a[i] == 0) {
            printf("! %d\n", i);
            fflush(stdout);
            return 0;
        }
    }

    for (int i = 11; i < p; ++i) {
        ll t = 1;
        for (int j = 0; j <= 10; ++j) {
            t = (t * (i - j)) % p;
        }
        ll res = 0;
        for (int j = 0, k = 1; j <= 10; ++j, k *= -1) {
            res = (res + 1ll * k * a[j] * t % p * inv[j] % p * inv[10 - j] % p * inv2[i - j] % p + p) % p;
        }
        if (res == 0) {
            printf("! %d\n", i);
            fflush(stdout);
            return 0;
        }
    }
    printf("! -1\n");
    fflush(stdout);

    return 0;
}
