#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
#define pll pair<ll, ll>
#define fi first
#define se second
int n;
ll l[N], r[N];
ll A, B;
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

multiset<pll> se;
void add(ll l, ll r) {
    if (l > 0) {
        se.insert(pll(l - 1, 0));
    }
    se.insert(pll(l, 1));
    se.insert(pll(r, 0));
    se.insert(pll(r + 1, -1));
}

int main() {
    while (scanf("%d%lld%lld", &n, &A, &B) != EOF) {
        se.clear();
        ll sum = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%lld%lld", l + i, r + i);
            sum += r[i] - l[i] + 1;
        }
        ll g = gcd(A, B + 1);
        if (1.0 * A * B / g > 1e18) {
            printf("%lld\n", sum);
            continue;
        }
        ll T = A / g * B;
        for (int i = 1; i <= n; ++i) {
            if (r[i] - l[i] + 1 >= T) {
                printf("%lld\n", T);
                return 0;
            }
            l[i] %= T;
            r[i] %= T;
            if (l[i] > r[i]) {
                add(l[i], T - 1);
                add(0, r[i]);
            } else {
                add(l[i], r[i]);
            }
        }
        ll base = 0, x = (*se.begin()).fi - 1, res = 0;
        auto it = se.begin();
        while (1) {
            if (it == se.end())
                break;
            ll now = (*it).fi;
            while (it != se.end() && (*it).fi == now) {
                base += (*it).se;
                ++it;
            }
            //	cout << x << " " << now << " " << base << endl;
            if (base > 0) {
                res += now - x;
            }
            x = now;
        }
        printf("%lld\n", res);
    }
    return 0;
}
